//
// Created by yehonatan on 28/01/2020.
//

#include "MyParallelServer.h"
#include <unistd.h>
#include <thread>
#include <cstring>
#include <iostream>
using namespace std;
void MyParallelServer::loop(int port, ClientHandler* c) {
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
    if (listen(sockfd, 10) == -1) {
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
                cout << "cant accept the client";
                throw "cant accept the client";
            }
            thread handle(&MyParallelServer::handleClient, this, client_socket, c);
            handle.detach();
        } catch(const char* e) {
            cout << e;
            this->stop();
        } /*catch (...) {
            cout << "errrrrrrrrroooooooooorrrrrrrrrrrrr";
            this->stop();
        }*/
        stopMtx.lock();
    }
    stopMtx.unlock();
    clientsMtx.lock();
    while (num_of_clients) {
        clientsMtx.unlock();
        clientsMtx.lock();
    }
    clientsMtx.unlock();
    close(sockfd);
}

void MyParallelServer::open(int port, ClientHandler* c) {
    thread tloop(&MyParallelServer::loop, this, port, c);
    tloop.join();
}
void MyParallelServer::stop() {
    stopMtx.lock();
    this->shouldStop = true;
    stopMtx.unlock();
}

void MyParallelServer::handleClient(int client_socket, ClientHandler *c) {
    clientsMtx.lock();
    num_of_clients++;
    clientsMtx.unlock();
    (c->clone())->handleClient(client_socket);
    close(client_socket);
    clientsMtx.lock();
    num_of_clients--;
    clientsMtx.unlock();
}
