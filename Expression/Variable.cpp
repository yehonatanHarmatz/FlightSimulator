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
}
///increase by 1
Variable &Variable::operator++() {
    this->st->update(name, value+1);
    this->value++;
    return *this;
}
///decrease by 1
Variable &Variable::operator--() {
    this->st->update(name, value-1);
    this->value--;
    return *this;
}
///increase by k
Variable &Variable::operator+=(double increase) {
    this->st->update(name, value+increase);
    this->value += increase;
    return *this;
}
///decrease by k
Variable &Variable::operator-=(double decrease) {
    this->st->update(name, value-decrease);
    this->value -= decrease;
    return *this;
}
///increase by 1
Variable &Variable::operator++(int num) {
    this->st->update(name, value+1);
    this->value++;
    return *this;
}
///decrease by 1
Variable &Variable::operator--(int num) {
    this->st->update(name, value-1);
    this->value--;
    return *this;
}
///return the value from the Symbol Table object
double Variable::calculate() {
    this->value = this->st->getValue(name);
    return this->value;
}


