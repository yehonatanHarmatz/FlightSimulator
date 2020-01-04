//
// Created by yehonatan on 04/01/2020.
//

#ifndef AIRPLANEPROJECT_PARSER_H
#define AIRPLANEPROJECT_PARSER_H

#include "SymbolTable.h"
#include "Commands/command.h"
using namespace std;
/**
 * the parser class
 */
class Parser {
    map<string, command*> commands;
    vector<string>* lexer_strings;
    SymbolTable* st;
public:
    Parser(vector<string>* ptr) {
        this->lexer_strings = ptr;
    }
    void initialize();
    void parse();

    command *getCommand(int i);
};


#endif //AIRPLANEPROJECT_PARSER_H
