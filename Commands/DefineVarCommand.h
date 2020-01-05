//
// Created by oren on 03/01/2020.
//

#ifndef AIRPLANEPROJECT_DEFINEVARCOMMAND_H
#define AIRPLANEPROJECT_DEFINEVARCOMMAND_H

#include "command.h"
#include "../SymbolTable.h"
#include "../Expression/Interpreter.h"

/**
 * the class is used to execute a command which defines a variable and adds it to the symbol table.
 */
class DefineVarCommand : public command {
private:
    SymbolTable* ptr;
public:
    DefineVarCommand(vector<string>* lex_ptr, SymbolTable* st_ptr) : command(lex_ptr) {
        this->ptr = st_ptr;
        this->params = 0;
    }
    /**
     * Defines a new variable and inserts it to the symbol table according to the sign.
     * "<-" will create a new variable which is set to 0 and binds it to the sim variable.
     * "->" will just bind to an already existing simulator variable.
     * @param index - the index of the lexer string which the command starts from.
     * @return the function returns 5 (the offset for the next command).
     * @throws exception if the string is corrupted.
     */
    int execute(int index) {
        // initialize data to 0
        // false for "->", true for "<-"
        bool dir;
        VarData* data;
        string sim = "";
        if (getStringInVector(index + 1) == "->") {
            // TODO release memory
            sim = getStringInVector(index + 3).substr(1, getStringInVector(index + 3).length()-2);
            data = new VarData(0, sim, 1);
        } else if (getStringInVector(index + 1) == "<-") {
            // simulator controls
            sim = getStringInVector(index + 3).substr(1, getStringInVector(index + 3).length()-2);
            data = ptr->searchSim(sim);
        } else if (getStringInVector(index + 1) == "=") {
            Interpreter i = Interpreter(this->ptr);
            float val = i.interpret(getStringInVector(index + 2))->calculate();
            data = new VarData(val, "", 1);
        } else {
            throw "error DefineVarCommand/execute";
        }

        ptr->addProgramVar(getStringInVector(index), data);
        int a = this->getParams(index);
        this->params = 0;
        return a;
    }
    int getParams(int i) {
        if (getStringInVector(i + 1) == "=") {
            this->params = 4; // for example: [var, warp, =, value]
        } else {
            this->params = 5; // for example: [var, warp, ->, sim, "name.."]
        }
        return this->params;
    }
};
#endif //AIRPLANEPROJECT_DEFINEVARCOMMAND_H
