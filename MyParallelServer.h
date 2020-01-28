//
// Created by yehonatan on 28/01/2020.
//

#ifndef EX4_MYPARALLELSERVER_H
#define EX4_MYPARALLELSERVER_H


#include "server_side.h"
#include <sys/socket.h>
#include <netinet/in.h>



class MyParallelServer : public server_side::Server {
    mutex stopMtx;
    mutex clientsMtx;
    bool shouldStop;
    int num_of_clients = 0;
public:
    void loop(int port, ClientHandler* c);
    virtual void open(int port, ClientHandler* c);
    virtual void stop();
    void handleClient(int client_socket, ClientHandler* c);
};


#endif //EX4_MYPARALLELSERVER_H
