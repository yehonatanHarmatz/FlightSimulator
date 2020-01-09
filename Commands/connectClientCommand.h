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
/**
 * client class
 */
class connectClientCommand : public command, ChangeValueListener{
    queue<string> messages;
    SymbolTable* st;
    bool keep_running = true;
    mutex mtx;
    mutex mesMtx;
public:
    /**
     * constructor
     * @param lexer the lexer vector
     * @param st the vars
     */
    connectClientCommand(vector<string>* lexer, SymbolTable* st): command(lexer) {
        this->messages = queue<string>();
        this->st = st;
        this->st->addListener(this);
        this->params = 3;
    }
    /**
     * connect as client to the simulator
     * @param index
     * @return params
     */
    int execute(int index);
    /**
     * send message from the queue top to the simulator
     * @param client_socket
     */
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
