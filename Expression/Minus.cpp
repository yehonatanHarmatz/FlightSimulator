//
// Created by yehonatan on 10/11/2019.
//

#include "Minus.h"
Minus::Minus(Expression* left, Expression* right) : BinaryOperator(left, right) {}
Minus::~Minus() {
//    delete this->left;
//    delete this->right;
}
double Minus::calculate() {
    return this->left->calculate() - this->right->calculate();
};