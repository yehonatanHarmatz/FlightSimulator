//
// Created by yehonatan on 02/01/2020.
//

#ifndef AIRPLANEPROJECT_OPENDATASERVER_H
#define AIRPLANEPROJECT_OPENDATASERVER_H

#include <string>
#include <vector>
#include <mutex>
#include "../Observer.h"
#include "command.h"
#include "../SymbolTable.h"

using namespace std;
class openDataServer: command {
    bool keep_running = true;
    mutex mtx;
    SymbolTable* st;
public:
    openDataServer(vector<string>* params, SymbolTable* st) : command(params) {
        this->st = st;
    }

    void openServer(int port);

    int execute(int index);
    void stopRun() {
        mtx.lock();
        keep_running = false;
        mtx.unlock();
    }

    void serverRound(int client_socket);

    void serverLoop(int client_socket);

    ~openDataServer() {
        delete st;
    }
};


#endif //AIRPLANEPROJECT_OPENDATASERVER_H