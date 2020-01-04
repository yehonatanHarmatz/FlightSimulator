//
// Created by yehonatan on 03/01/2020.
//

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <thread>
#include <unistd.h>
#include "connectClientCommand.h"
#include "../Expression/Interpreter.h"

void connectClientCommand::update(string var, float newVal) {
    string message = "set " + this->st->getSim(var) + " " + to_string(newVal) + "\r\n";
    mesMtx.lock();
    this->messages.push(message);
    mesMtx.unlock();
}

void connectClientCommand::sendMessageLoop(int client_socket) {
    mtx.lock();
    while (keep_running) {
        mtx.unlock();
        mesMtx.lock();
        if (!messages.empty()) {
            send(client_socket, messages.front().c_str(), messages.front().length(), 0);
            messages.pop();
        }
        mesMtx.unlock();
        mtx.lock();
    }
    close(client_socket);
}

int connectClientCommand::execute(int index) {
    Interpreter i1 = Interpreter(st);
    const string ip = getStringInVector(index).substr(1, getStringInVector(index).length()-2);
    int port = i1.interpret(getStringInVector(index + 1))->calculate();
    int client_socket = socket(AF_INET,SOCK_STREAM, 0);
    if (client_socket == -1) {
        throw "cant create a socket";
    }
    sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr(ip.c_str());
    address.sin_port = htons(port);
    if (connect(client_socket, (struct sockaddr *) &address, sizeof(address)) == -1) {
        throw "cant connect to the simulator as client";
    }
    thread ClientLoop(&connectClientCommand::sendMessageLoop, this, client_socket);
    ClientLoop.detach();
    return params;
}

