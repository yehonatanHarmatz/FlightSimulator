//
// Created by yehonatan on 09/11/2019.
//

#include "UnaryOperator.h"

UnaryOperator::UnaryOperator(Expression *exp) {
    this->exp = exp;
}

UnaryOperator::~UnaryOperator() {
    delete this->exp;
}