//
// Created by yehonatan on 04/01/2020.
//

#ifndef AIRPLANEPROJECT_UPDATEVARCOMMAND_H
#define AIRPLANEPROJECT_UPDATEVARCOMMAND_H


#include "command.h"
#include "../SymbolTable.h"

class updateVarCommand : public command {
    string name;
    SymbolTable* st;
public:
    updateVarCommand(vector<string> *ptr, string name, SymbolTable *st) : command(ptr) {
        this->name = name;
        this->st = st;
        this->params = 3;
    }
    int execute(int index);
};


#endif //AIRPLANEPROJECT_UPDATEVARCOMMAND_H
