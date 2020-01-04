//
// Created by oren on 04/01/2020.
//
#include <iostream>
#include "command.h"

using namespace std;
/**
 * The class is used to print a message to the screen.
 */
class PrintCommand : command {
public:
    /**
     * contructor.
     * @param lex_ptr - the lexer's index.
     */
    PrintCommand(vector<string>* lex_ptr) : command(lex_ptr){
        this->params = 2;
    }
    /**
     * The function executes a print command to the screen.
     * @param index the index of the command in the string from the lexer.
     * @return  the offset of the next command.
     */
    int execute(int index) {
        cout << getStringInVector(index + 1) << endl;
        return 2;
    }

};
