//
// Created by yehonatan on 10/11/2019.
//

#ifndef EX1_INTERPRETER_H
#define EX1_INTERPRETER_H


#include <string>
#include <list>
#include <map>
#include "Expression.h"

class Interpreter {
    map<string, double> *vars;
public:
    Interpreter();

    virtual ~Interpreter();

    Expression *interpret(string exp);

    void setVariables(string vars);

    list<string> *split(string str, string token);

    static bool isSmaller(char o1, char &i);
    static bool isVar(string var);
    static bool isVal(string val);
};


#endif //EX1_INTERPRETER_H
