//
// Created by yehonatan on 03/01/2020.
//

#ifndef AIRPLANEPROJECT_CONNECTCLIENTCOMMAND_H
#define AIRPLANEPROJECT_CONNECTCLIENTCOMMAND_H


#include <mutex>
#include "command.h"
#include "queue"
#include "../ChangeValueListener.h"
#include "../SymbolTable.h"

class connectClientCommand : public command, ChangeValueListener{
    queue<string> messages;
    SymbolTable* st;
    bool keep_running = true;
    mutex mtx;
    mutex mesMtx;
public:
    connectClientCommand(vector<string>* params, SymbolTable* st): command(params) {
        this->messages = queue<string>();
        this->st = st;
        this->st->addListener(this);
    }
    int execute(int index);
    void sendMessageLoop(int client_socket);
    virtual void update(string var, float newVal);
    virtual void update(int index, float newVal) {}
    void stopRunning() {
        mtx.lock();
        keep_running = false;
        mtx.unlock();
    }

};


#endif //AIRPLANEPROJECT_CONNECTCLIENTCOMMAND_H
