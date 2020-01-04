//
// Created by yehonatan on 09/11/2019.
//

#ifndef EX1_UPLUS_H
#define EX1_UPLUS_H


#include "UnaryOperator.h"
/**
 * Unary plus class
 */
class UPlus : public UnaryOperator {
public:
    UPlus(Expression *exp) : UnaryOperator(exp) {

    }

    double calculate() override {
        return this->exp->calculate();
    }

    virtual ~UPlus() {
//        delete this->exp;
    }
};


#endif //EX1_UPLUS_H
