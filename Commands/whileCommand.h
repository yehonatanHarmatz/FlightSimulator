//
// Created by yehonatan on 04/01/2020.
//

#ifndef AIRPLANEPROJECT_WHILECOMMAND_H
#define AIRPLANEPROJECT_WHILECOMMAND_H
#include "conditionParser.h"

class whileCommand : public conditionParser {
public:
    whileCommand(vector<string> *lexerParams, SymbolTable *st1, Parser *p1) : conditionParser(lexerParams, st1, p1) {}
    int execute(int index) {
        this->getCommands(index);
        while (checkCondition()) {
            this->runCommands(index + 4);
        }
        return this->params;
    }
};
#endif //AIRPLANEPROJECT_WHILECOMMAND_H
