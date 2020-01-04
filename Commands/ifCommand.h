//
// Created by yehonatan on 04/01/2020.
//

#ifndef AIRPLANEPROJECT_IFCOMMAND_H
#define AIRPLANEPROJECT_IFCOMMAND_H

#include "conditionParser.h"

class ifCommand : public conditionParser {
public:
    ifCommand(vector<string> *lexerParams, SymbolTable *st1, Parser *p1) : conditionParser(lexerParams, st1, p1) {}
    int execute(int index) {
        this->getCommands(index);
        if (checkCondition()) {
            this->runCommands(index + 4);
        }
        return this->params;
    }
};
#endif //AIRPLANEPROJECT_IFCOMMAND_H
