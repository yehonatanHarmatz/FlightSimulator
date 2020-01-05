//
// Created by oren on 04/01/2020.
//

#ifndef AIRPLANEPROJECT_SLEEPCOMMAND_H
#define AIRPLANEPROJECT_SLEEPCOMMAND_H


#include <iostream>
#include "command.h"
#include "../Expression/Interpreter.h"
#include <thread>

using namespace std;
/**
 * The class is used to print a message to the screen.
 */
class SleepCommand : public command {
    SymbolTable* st;
public:
    /**
     * constructor.
     * @param lex_ptr - the lexer's vector of strings
     */
    SleepCommand(vector<string>* lex_ptr, SymbolTable* st) : command(lex_ptr) {
        this->params = 2;
        this->st = st;
    }
    /**
     * The function puts the thread for sleep.
     * @param index the index of the command in the string from the lexer.
     * @return  the offset of the next command.
     */
    int execute(int index) {
        Interpreter i = Interpreter(st);
        long ms = (long)i.interpret(getStringInVector(index))->calculate();
        std::chrono::milliseconds pause(ms);
        std::this_thread::sleep_for(pause);
        return 2;
    }

};
#endif //AIRPLANEPROJECT_SLEEPCOMMAND_H
