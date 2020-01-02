//
// Created by yehonatan on 10/11/2019.
//

#include "Plus.h"

Plus::Plus(Expression *left, Expression *right) : BinaryOperator(left, right) {}

Plus::~Plus() {
//    delete this->left;
//    delete this->right;
}

double Plus::calculate() {
    return this->left->calculate() + this->right->calculate();
};