//
// Created by yehonatan on 04/01/2020.
//

#ifndef AIRPLANEPROJECT_CONDITIONPARSER_H
#define AIRPLANEPROJECT_CONDITIONPARSER_H

#include "command.h"
#include "../SymbolTable.h"
#include "../Expression/Interpreter.h"
#include "../Parser.h"

class conditionParser : public command {
    list<command*> commands;
    Parser* p;
    string right;
    string left;
    string condition;
protected:
    SymbolTable* st;
public:
    conditionParser(vector<string>* lexer_params, SymbolTable* st, Parser* p): command(lexer_params) {
        this->st = st;
        this->p = p;
        this->params = 0;
    }
    void getCommands(int index) {
        this->commands = list<command*>();
        int a = index - 1; //on while/if word
        left = getStringInVector(index);
        ++index;
        condition = getStringInVector(index);
        ++index;
        right = getStringInVector(index);
        ++index; // now on {
        ++index;
        while (getStringInVector(index) != "}") {
            command * c = p->getCommand(index);
            if (c!= nullptr) {
                this->commands.push_back(c);
                index += c->getParams(index);
            }
        }
        //now the index on }
        this->params = index - a + 1;
    };
    virtual int execute(int index) = 0;
    bool checkCondition() {
        Interpreter i = Interpreter(this->st);
        float lVal = i.interpret(left)->calculate();
        float rVal = i.interpret(right)->calculate();
        if (condition == "==") {
            return lVal == rVal;
        } else if (condition == "<=") {
            return lVal <= rVal;
        } else if (condition == ">=") {
            return lVal >= rVal;
        } else if (condition == "!=") {
            return lVal != rVal;
        } else if (condition == "<") {
            return lVal < rVal;
        } else if (condition == ">") {
            return lVal > rVal;
        } else {
            throw "illegal condition";
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
        return this->params;
    }
};
#endif //AIRPLANEPROJECT_CONDITIONPARSER_H
