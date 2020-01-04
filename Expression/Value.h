//
// Created by yehonatan on 09/11/2019.
//

#ifndef EX1_VALUE_H
#define EX1_VALUE_H


#include "Expression.h"
/**
 * class of value
 */
class Value : public Expression {
    double val;

public:
    Value(double val);

    virtual ~Value();

    double calculate() override;
};


#endif //EX1_VALUE_H
