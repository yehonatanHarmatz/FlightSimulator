//
// Created by oren on 13/12/2019.
//

#ifndef EX3_COMMAND_H
#define EX3_COMMAND_H

#include "laxer.h"
using namespace std;

/*
 * class command is an abstract class used for the command pattern.
 * it has only 1 function (apart from the constructor) which is to execute the command.
 */
class command {
private:
    vector<string> *lexer_vector_ptr;
public:
    command(vector<string> *ptr) : lexer_vector_ptr(ptr){};
    virtual int execute(int index) = 0;
};

#endif //EX3_COMMAND_H
