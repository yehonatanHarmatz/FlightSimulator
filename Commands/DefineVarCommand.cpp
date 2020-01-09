//
// Created by oren on 03/01/2020.
//
#include "command.h"
#include "../SymbolTable.h"

/**
 * the class is used to execute a command which defines a variable and adds it to the symbol table.
 */
class DefineVarCommand : command {
private:
    SymbolTable* ptr;
public:
    DefineVarCommand(vector<string>* lex_ptr, SymbolTable* st_ptr) : command(lex_ptr) {
        this->ptr = st_ptr;
        this->params = 5; // for example: [var, warp, ->, sim, "name.."]
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
        if (getStringInVector(index + 2) == "<-") {
            // TODO release memory
            data = new VarData(0, getStringInVector(index + 4), 1);
        } else if (getStringInVector(index + 2) == "->") {
            // simulator controls
            data = ptr->searchSim(getStringInVector(index + 3));
        } else {
            throw "error DefineVarCommand/execute";
        }

        ptr->addProgramVar(getStringInVector(index + 1), data);
        return 5;
    }
};
