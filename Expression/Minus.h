//
// Created by yehonatan on 10/11/2019.
//

#ifndef EX1_MINUS_H
#define EX1_MINUS_H


#include "BinaryOperator.h"

class Minus : public BinaryOperator {
public:
    Minus(Expression *left, Expression *right);

    virtual ~Minus();

    double calculate() override;
};


#endif //EX1_MINUS_H
