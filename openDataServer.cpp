//
// Created by yehonatan on 02/01/2020.
//

#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <cstring>
#include "openDataServer.h"
#include "laxer.h"
#include "Expression/Interpreter.h"
#include <thread>

void openDataServer::openServer(int port) {
    int sockfd = socket(AF_INET,SOCK_STREAM, 0);
    if (sockfd == -1) {
        throw "cant create a socket";
    }
    sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);
    if (bind(sockfd, (struct sockaddr *) &address, sizeof(address)) == -1) {
        throw "cant bind";
    }
    if (listen(sockfd, 5) == -1) {
        throw "Error during listening";
    }
    int client_socket = accept(sockfd, (struct sockaddr *) &address, (socklen_t*)&address);
    if (client_socket == -1) {
        throw "cant accept the simulator as client";
    }
    //size of 36 float values with ',' and \n for reading each values message separately
    const int size = 36* sizeof(float) + 36 * sizeof(char);
    char buffer[size] = {0};
    list<string>* data;
    string s = "";
    mtx.lock();
    while (keep_running) {
        mtx.unlock();
        s = "";
        read(client_socket, buffer,size);
        for (int i = 0; i <size - 1; ++i) {
            s += buffer[i];
        }
        data = split(s, ",");
        for (int i =0; i < (*data).size(); ++i) {
            notify(i, stod(data->front()));
            data->pop_front();
        }
        free(data);
        memset(buffer, 0, size * sizeof(buffer[0]));
        mtx.lock();
    }
    close(client_socket);
}
int openDataServer::execute(int index) {
    Interpreter i1 = Interpreter();
    int port = i1.interpret(params.at(index))->calculate();
    thread ServerLoop(&openDataServer::openServer, this ,port);
    ServerLoop.detach();
    return 2;
}
