//
// Created by yehonatan on 10/11/2019.
//

#include "Mul.h"

Mul::Mul(Expression *left, Expression *right) : BinaryOperator(left, right) {}

Mul::~Mul() {
//    delete this->left;
//    delete this->right;
}

double Mul::calculate() {
    return this->left->calculate() * this->right->calculate();
};