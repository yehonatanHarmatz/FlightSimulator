//
// Created by yehonatan on 06/01/2020.
//

#ifndef AIRPLANEPROJECT_FUNCTIONCOMMAND_H
#define AIRPLANEPROJECT_FUNCTIONCOMMAND_H

#include "command.h"
#include "../Parser.h"
#include "../Expression/Interpreter.h"

class functionCommand : public command {
    list<command*> commands;
    Parser* p;
    SymbolTable* st;
    string var;
    bool isDefinition = true;
    int normalyParam;
    int startIndex;
public:
    functionCommand(vector<string>* lexer_params, SymbolTable* st, Parser* p): command(lexer_params) {
        this->st = st;
        this->p = p;
        this->params = 0;
        this->normalyParam = 2;
    }
    void getCommands(int index) {
        this->commands = list<command*>();
        int a = index - 1; //on function name
        this->var = getStringInVector(index).substr(3);
        ++index; // now on {
        ++index;
        while (getStringInVector(index) != "}") {
            command * c = p->getCommand(index);
            if (c!= nullptr) {
                this->commands.push_back(c);
                index += c->getParams(index + 1);
            }
        }
        //now the index on }
        this->params = index - a + 1;
    };
    int execute(int index) {
        Interpreter i1 = Interpreter(st);
     if (this->isDefinition) {
         this->isDefinition = false;
         getCommands(index);
         this->startIndex = index;
         return this->params;
     } else {
         this->st->addProgramVar(this->var, new VarData(i1.interpret(getStringInVector(index))->calculate(), "", true));
         runCommands(startIndex+2);
         ///TO-DO delete var
         return this->normalyParam;
     }
    }
    void runCommands(int index) {
        for (auto c : this->commands) {
            c->execute(index + 1);
            index += c->getParams(index + 1);
        }
    }
    int getParams(int i) {
        if (this->params == 0) {
            this->getCommands(i);
        }
        if (isDefinition) {
            return this->params;
        } else {
            return normalyParam;
        }
    }
};
#endif //AIRPLANEPROJECT_FUNCTIONCOMMAND_H
