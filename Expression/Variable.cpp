//
// Created by yehonatan on 09/11/2019.
//

#include "Variable.h"

Variable::Variable(string name, double value, SymbolTable* st) {
    this->name = name;
    this->value = value;
    this->st = st;
}

Variable::~Variable() {
    delete st;
}

Variable &Variable::operator++() {
    this->st->update(name, value+1);
    this->value++;
    return *this;
}

Variable &Variable::operator--() {
    this->st->update(name, value-1);
    this->value--;
    return *this;
}

Variable &Variable::operator+=(double increase) {
    this->st->update(name, value+increase);
    this->value += increase;
    return *this;
}

Variable &Variable::operator-=(double decrease) {
    this->st->update(name, value-decrease);
    this->value -= decrease;
    return *this;
}

Variable &Variable::operator++(int num) {
    this->st->update(name, value+1);
    this->value++;
    return *this;
}

Variable &Variable::operator--(int num) {
    this->st->update(name, value-1);
    this->value--;
    return *this;
}

double Variable::calculate() {
    this->st->getValue(name);
    return this->value;
}


