//
// Created by yehonatan on 09/11/2019.
//

#include "Variable.h"

Variable::Variable(string name, double value) {
    this->name = name;
    this->value = value;
}

Variable::~Variable() {}

Variable &Variable::operator++() {
    this->value++;
    return *this;
}

Variable &Variable::operator--() {
    this->value--;
    return *this;
}

Variable &Variable::operator+=(double increase) {
    this->value += increase;
    return *this;
}

Variable &Variable::operator-=(double decrease) {
    this->value -= decrease;
    return *this;
}

Variable &Variable::operator++(int num) {
    this->value++;
    return *this;
}

Variable &Variable::operator--(int num) {
    this->value--;
    return *this;
}

double Variable::calculate() {
    return this->value;
}


