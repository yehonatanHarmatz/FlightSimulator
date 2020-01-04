//
// Created by yehonatan on 09/11/2019.
//

#ifndef EX1_VARIABLE_H
#define EX1_VARIABLE_H

#include <string>
#include "Expression.h"
#include "../SymbolTable.h"

using namespace std;
/**
 * class of variable
 */
class Variable : public Expression {
    string name;
    double value;
    SymbolTable* st;
public:
    Variable(string name, double value, SymbolTable* st);

    virtual ~Variable();

    Variable &operator++();

    Variable &operator--();

    Variable &operator+=(double increase);

    Variable &operator-=(double decrease);

    Variable &operator++(int num);

    Variable &operator--(int num);

    double calculate() override;

};


#endif //EX1_VARIABLE_H
