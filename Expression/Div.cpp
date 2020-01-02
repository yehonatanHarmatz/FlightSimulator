//
// Created by yehonatan on 10/11/2019.
//

#include "Div.h"

Div::Div(Expression *left, Expression *right) : BinaryOperator(left, right) {}

Div::~Div() {
//    delete this->left;
//    delete this->right;
}

double Div::calculate() {
    if (this->right->calculate() == 0) {
        throw "bad input";
    }
    return this->left->calculate() / this->right->calculate();
};