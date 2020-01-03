//
// Created by oren on 13/12/2019.
//

#ifndef AIRPLANEPROJECT_COMMAND_H
#define AIRPLANEPROJECT_COMMAND_H

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
    virtual ~command() {
        delete lexer_vector_ptr;
    }
    string getStringInVector(int i) {
        return lexer_vector_ptr->at(i);
    }
};

#endif //AIRPLANEPROJECT_COMMAND_H