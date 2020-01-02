//
// Created by yehonatan on 10/11/2019.
//

#ifndef EX1_BINARYOPERATOR_H
#define EX1_BINARYOPERATOR_H


#include "Expression.h"

class BinaryOperator : public Expression {
protected:
    Expression* left;
    Expression* right;
public:
    BinaryOperator(Expression* left, Expression* right);

    virtual ~BinaryOperator();
};


#endif //EX1_BINARYOPERATOR_H
