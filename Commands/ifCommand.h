//
// Created by yehonatan on 04/01/2020.
//

#ifndef AIRPLANEPROJECT_IFCOMMAND_H
#define AIRPLANEPROJECT_IFCOMMAND_H

#include "conditionParser.h"

class ifCommand : public conditionParser {
public:
    /**
     * Constructor.
     * @param lexer_params - the output vector of the lexer.
     * @param st1 - a pointer the the symbol table.
     * @param p1 - a pointer to the parser.
     */
    ifCommand(vector<string> *lexerParams, SymbolTable *st1, Parser *p1) : conditionParser(lexerParams, st1, p1) {}
    /**
     * The function executes the if.
     * @param index - the index of the if in the lexer's vector.
     * @return the number of params.
     */
    int execute(int index) {
        this->getCommands(index);
        if (checkCondition()) {
            this->runCommands(index + 4);
        }
        int a = this->params;
        this->params = 0;
        return a;    }
};
#endif //AIRPLANEPROJECT_IFCOMMAND_H
