//
// Created by yehonatan on 28/01/2020.
//

#ifndef EX4_MYCLIENTHANDLER_H
#define EX4_MYCLIENTHANDLER_H
#include "string"
#include "ClientHandler.h"
#include "Solver.h"
#include "CacheManager.h"
#include "searchable_table.h"

class MyClientHandler: public ClientHandler {
    Solver<SearchableTable, string>* solver;
    CacheManager<string, string>* cm;
public:
    MyClientHandler(Solver<SearchableTable, string>* sol, CacheManager<string, string>* cm) {
        this->solver = sol;
        this->cm = cm;
    }
    virtual void handleClient(int& client_socket);

    bool hasPacket(string s);

    virtual ClientHandler* clone();
};


#endif //EX4_MYCLIENTHANDLER_H
