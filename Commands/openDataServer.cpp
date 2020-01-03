//
// Created by yehonatan on 02/01/2020.
//

#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <cstring>
#include "openDataServer.h"
#include "../laxer.h"
#include "../Expression/Interpreter.h"
#include <thread>

void openDataServer::serverRound(int client_socket) {
    //size of 36 float values with ',' and \n for reading each values message separately
    const int size = 36* sizeof(float) + 36 * sizeof(char);
    char buffer[size] = {0};
    list<string>* data;
    string s = "";
    read(client_socket, buffer,size);
    for (int i = 0; i <size - 1; ++i) {
        s += buffer[i];
    }
    data = split(s, ",");
    for (int i =0; i < (*data).size(); ++i) {
        st->update(i, stod(data->front()));
        data->pop_front();
    }
    free(data);
}
void openDataServer::serverLoop(int client_socket) {
    mtx.lock();
    while (keep_running) {
        mtx.unlock();
        serverRound(client_socket);
        mtx.lock();
    }
    close(client_socket);
}
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
    serverRound(client_socket);
    thread ServerLoop(&openDataServer::serverLoop, this ,client_socket);
    ServerLoop.detach();
}
int openDataServer::execute(int index) {
    Interpreter i1 = Interpreter(st);
    int port = i1.interpret(getStringInVector(index))->calculate();
    openServer(port);
    return 2;
}
