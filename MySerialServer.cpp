//
// Created by yehonatan on 20/01/2020.
//


#include <unistd.h>
#include <thread>
#include <cstring>
#include <iostream>
#include "MySerialServer.h"
using namespace std;
void MySerialServer::loop(int port, ClientHandler* c) {
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
    struct timeval tv;
    tv.tv_sec = 60 * 2;
    setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, (const char *) &tv, sizeof tv);
    stopMtx.lock();
    while (!shouldStop) {
        stopMtx.unlock();
        try {
            int client_socket = accept(sockfd, (struct sockaddr *) &address, (socklen_t *) &address);
            if (client_socket == -1) {
                throw "cant accept the client";
            }
            c->handleClient(client_socket);
            close(client_socket);
        } catch (...) {
            this->stop();
        }
        stopMtx.lock();
    }
    close(sockfd);
}

void MySerialServer::open(int port, ClientHandler* c) {
    thread loop(&MySerialServer::loop, this, port, c);
    loop.join();
}
void MySerialServer::stop() {
    stopMtx.lock();
    this->shouldStop = true;
    stopMtx.unlock();
}
