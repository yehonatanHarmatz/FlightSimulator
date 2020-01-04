//
// Created by oren on 04/01/2020.
//

#include <iostream>
#include "command.h"
#include <thread>

using namespace std;
/**
 * The class is used to print a message to the screen.
 */
class SleepCommand : command {
public:
    /**
     * constructor.
     * @param lex_ptr - the lexer's vector of strings
     */
    SleepCommand(vector<string>* lex_ptr) : command(lex_ptr) {
        this->params = 2;
    }
    /**
     * The function puts the thread for sleep.
     * @param index the index of the command in the string from the lexer.
     * @return  the offset of the next command.
     */
    int execute(int index) {
        std::chrono::milliseconds pause(stoi(getStringInVector(index)));
        std::this_thread::sleep_for(pause);
        return 2;
    }

};
