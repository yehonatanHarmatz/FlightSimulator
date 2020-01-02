//
// Created by yehonatan on 09/11/2019.
//

#include "Value.h"

Value::Value(double val) {
    this->val = val;
}

Value::~Value() {}

double Value::calculate() {
    return this->val;
}
