//
// Created by oren on 04/01/2020.
//

#ifndef AIRPLANEPROJECT_PRINTCOMMAND_H
#define AIRPLANEPROJECT_PRINTCOMMAND_H

#include <iostream>
#include "command.h"
#include "../Expression/Interpreter.h"

using namespace std;
/**
 * The class is used to print a message to the screen.
 */
class PrintCommand : public command {
    SymbolTable *st;
public:
    /**
     * contructor.
     * @param lex_ptr - the lexer's index.
     */
    PrintCommand(vector<string>* lex_ptr, SymbolTable* st) : command(lex_ptr){
        this->params = 2;
        this->st = st;
    }
    /**
     * The function executes a print command to the screen.
     * @param index the index of the command in the string from the lexer.
     * @return  the offset of the next command.
     */
    int execute(int index) {
        string s = getStringInVector(index);
        if (s[0] == '\"') {
            s = s.substr(1, s.length() - 2);
        } else {
            Interpreter i = Interpreter(st);
            s = to_string(i.interpret(s)->calculate());
        }
        cout << s << endl;
        return 2;
    }
};
#endif //AIRPLANEPROJECT_PRINTCOMMAND_H
