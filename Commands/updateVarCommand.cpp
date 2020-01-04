//
// Created by yehonatan on 04/01/2020.
//

#include "updateVarCommand.h"
#include "../Expression/Interpreter.h"

int updateVarCommand::execute(int index) {
    Interpreter i1 = Interpreter(this->st);
    float newVal = i1.interpret(getStringInVector(index + 1))->calculate();
    this->st->update(this->name, newVal);
    return 3;
}
