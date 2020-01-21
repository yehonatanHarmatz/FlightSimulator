//
// Created by yehonatan on 20/01/2020.
//

#ifndef EX4_MYSERIALSERVER_H
#define EX4_MYSERIALSERVER_H


#include "server_side.h"
#include <sys/socket.h>
#include <netinet/in.h>

class MySerialServer : public server_side::Server {
    mutex stopMtx;
    bool shouldStop;
public:
    void loop(int port, ClientHandler* c);
    virtual void open(int port, ClientHandler* c);
    virtual void stop();
};


#endif //EX4_MYSERIALSERVER_H
