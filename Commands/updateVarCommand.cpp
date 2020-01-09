//
// Created by yehonatan on 04/01/2020.
//

#include "updateVarCommand.h"
#include "../Expression/Interpreter.h"
/**
 * The function updates the variable.
 * @param index - the position in the lexer's vector.
 * @return - the number of params.
 */
int updateVarCommand::execute(int index) {
    Interpreter i1 = Interpreter(this->st);
    float newVal = i1.interpret(getStringInVector(index + 1))->calculate();
    this->st->update(this->name, newVal);
    return params;
}
