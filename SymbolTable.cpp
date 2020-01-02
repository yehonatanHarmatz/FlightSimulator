//
// Created by yehonatan on 01/01/2020.
//

#include "SymbolTable.h"
#include <mutex>
using namespace std;
mutex write;
mutex read;
void SymbolTable::ChangeValBySimulator(string var, float val) {
    //check direction
    if (!this->SimulatorVars.at(var).getDirection()) {
        return;
    }
    write.lock();
    read.lock();
    this->SimulatorVars.at(var).changeVal(val);
    read.unlock();
    write.unlock();
}
void SymbolTable::ChangeValByProgram(string var, float val) {
    write.lock();
    read.lock();
    this->ProgramVars.at(var).changeVal(val);
    read.unlock();
    write.unlock();
    this->notify(var, val);
}
float SymbolTable::getValue(string var) {
    float val;
    if (this->SimulatorVars.find(var) != this->SimulatorVars.end()) {
        write.lock();
        val = this->SimulatorVars.at(var).getVal();
        write.unlock();
    } else {
        write.lock();
        val = this->ProgramVars.at(var).getVal();
        write.unlock();
    }
    return val;
}
string SymbolTable::getSim(string var) {
    string sim;
    if (this->SimulatorVars.find(var) != this->SimulatorVars.end()) {
        write.lock();
        sim = this->SimulatorVars.at(var).getSim();
        write.unlock();
    } else {
        write.lock();
        sim = this->ProgramVars.at(var).getSim();
        write.unlock();
    }
    return sim;
}
string SymbolTable::getVarByIndex(int index) {
    return this->indexToVar[index];
}
void SymbolTable::update(string var, float newVal) {
    if (this->SimulatorVars.find(var) != this->SimulatorVars.end()) {
        this->ChangeValBySimulator(var, newVal);
    } else {
        this->ChangeValByProgram(var, newVal);
    }
}