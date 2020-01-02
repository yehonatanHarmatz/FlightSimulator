//
// Created by yehonatan on 10/11/2019.
//

#ifndef EX1_DIV_H
#define EX1_DIV_H


#include "BinaryOperator.h"

class Div : public BinaryOperator {
public:
    Div(Expression *left, Expression *right);

    virtual ~Div();

    double calculate() override;
};


#endif //EX1_DIV_H
