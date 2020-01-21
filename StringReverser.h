//
// Created by yehonatan on 21/01/2020.
//

#ifndef EX4_STRINGREVERSER_H
#define EX4_STRINGREVERSER_H


#include "Solver.h"
#include "string"

using namespace std;
class StringReverser : public Solver<string, string> {

public:
    virtual string& solve(const string& p);
};


#endif //EX4_STRINGREVERSER_H
