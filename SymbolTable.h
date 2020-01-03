//
// Created by yehonatan on 01/01/2020.
//

#ifndef AIRPLANEPROJECT_SYMBOLTABLE_H
#define AIRPLANEPROJECT_SYMBOLTABLE_H

#include <map>
#include "VarData.h"
#include "Observer.h"

class SymbolTable: public Observer, public ChangeValueListener {
    map<string,VarData*> ProgramVars = map<string,VarData*>();
    map<string,VarData*> SimulatorVars = map<string,VarData*>();
    array<string, 36> indexToVar;
    void ChangeValBySimulator(string var, float val);
    void ChangeValByProgram(string var, float val);
public:
    SymbolTable() {
        initialize();
    }
    float getValue(string var);
    string getSim(string var);
    string getVarByIndex(int index);
    void update(string var, float newVal);
    void update(int index, float newVal);

    void addProgramVar(string var, VarData* data) {
        this->ProgramVars.insert(pair<string,VarData*>(var, data));
    }
    void addSimulatorVar(string var, VarData* data) {
        this->SimulatorVars.insert(pair<string,VarData*>(var, data));
    }
    void initialize();
    VarData* searchSim(string sim);

    void changeDirection(string var, bool newDirection);
};


#endif //AIRPLANEPROJECT_SYMBOLTABLE_H
