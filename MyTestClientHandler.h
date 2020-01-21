//
// Created by yehonatan on 20/01/2020.
//

#ifndef EX4_MYTESTCLIENTHANDLER_H
#define EX4_MYTESTCLIENTHANDLER_H


#include "string"
#include "ClientHandler.h"
#include "Solver.h"
#include "CacheManager.h"

class MyTestClientHandler: public ClientHandler {
    Solver<string, string>* solver;
    CacheManager<string, string>* cm;
public:
    MyTestClientHandler(Solver<string, string>* sol, CacheManager<string, string>* cm) {
        this->solver = sol;
        this->cm = cm;
    }
    virtual void handleClient(int& client_socket);

    bool hasPacket(string s);
};


#endif //EX4_MYTESTCLIENTHANDLER_H
