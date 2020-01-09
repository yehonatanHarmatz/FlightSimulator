//
// Created by yehonatan on 04/01/2020.
//

#ifndef AIRPLANEPROJECT_WHILECOMMAND_H
#define AIRPLANEPROJECT_WHILECOMMAND_H
#include "conditionParser.h"

class whileCommand : public conditionParser {
public:
    /**
     * Constructor.
     * @param lexerParams - the output vector of the lexer.
     * @param st1 - a pointer the the symbol table.
     * @param p1 - a pointer to the parser.
     */
    whileCommand(vector<string> *lexerParams, SymbolTable *st1, Parser *p1) : conditionParser(lexerParams, st1, p1) {}
    int execute(int index) {
        this->getCommands(index);
        while (checkCondition()) {
            this->runCommands(index + 4);
        }
        int a = this->params;
        this->params = 0;
        return a;
    }
};
#endif //AIRPLANEPROJECT_WHILECOMMAND_H
