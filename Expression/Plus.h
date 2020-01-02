//
// Created by yehonatan on 10/11/2019.
//

#ifndef EX1_PLUS_H
#define EX1_PLUS_H


#include "BinaryOperator.h"

class Plus : public BinaryOperator {
public:
    Plus(Expression *left, Expression *right);

    virtual ~Plus();

    double calculate() override;
};


#endif //EX1_PLUS_H
