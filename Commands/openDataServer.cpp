//
// Created by yehonatan on 02/01/2020.
//

#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include "openDataServer.h"
#include "../lexer.h"
#include "../Expression/Interpreter.h"
#include <thread>
#include <cstring>
#include <iostream>
/**
 * function for one round of getting information from the simulator
 * @param client_socket
 */
void openDataServer::serverRound(int client_socket) {
    //size of 36 float values with ',' and \n for reading each values message separately
    const int size = 36* sizeof(float) + 37 * sizeof(char);
    char buffer[size] = {0};
    list<string>* data;
    bool flag = true;
    string s = left;
    left = "";
    /**
     * recive packets from the client till we arrived \n
     */
    while (flag) {
        if (!hasPacket(s)) {
            recv(client_socket, buffer, size, 0);
        } else {
            list<string>* l = split(s, "\n");
            s = l->front();
            left = l->back();
            flag = false;
            delete l;
        }
        for (int i = 0; i < size; ++i) {
            if (buffer[i] != '\0' && buffer[i] != '\n' && buffer[i] != '\r' && flag) {
                s += buffer[i];
            } else if (buffer[i] == '\n' && flag) {
                flag = false;
            } else if (!flag && buffer[i] != '\0' && buffer[i] != '\r') {
                left += buffer[i];
            }
        }
        memset(buffer,0,size);
    }
    data = split(s, ",");
    for (int i =0; !data->empty(); ++i) {
        st->update(i, stod(data->front()));
        data->pop_front();
    }
    free(data);
}
/**
 * server loop - call the server round
 * @param client_socket
 */
void openDataServer::serverLoop(int client_socket) {
    mtx.lock();
    while (keep_running) {
        mtx.unlock();
        serverRound(client_socket);
        mtx.lock();
    }
    close(client_socket);
}
/**
 * open server
 * @param port
 */
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
/**
 * execute the code
 * @param index
 * @return
 */
int openDataServer::execute(int index) {
    Interpreter i1 = Interpreter(st);
    int port = i1.interpret(getStringInVector(index))->calculate();
    openServer(port);
    return params;
}
/**
 * search for \n in s
 */
bool openDataServer::hasPacket(string s) {
    for (int i =0; i< s.length(); ++i) {
        if (s[i] == '\n') {
            return true;
        }
    }
    return false;
}
