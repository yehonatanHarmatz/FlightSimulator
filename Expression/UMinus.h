//
// Created by yehonatan on 09/11/2019.
//

#ifndef EX1_UMINUS_H
#define EX1_UMINUS_H


#include "UnaryOperator.h"
/**
 * unary minus class
 */
class UMinus : public UnaryOperator {
public:

    UMinus(Expression *exp) : UnaryOperator(exp) {

    }

    double calculate() override {
        return -1 * this->exp->calculate();
    }

    virtual ~UMinus() {
//        delete this->exp;
    }

};


#endif //EX1_UMINUS_H
