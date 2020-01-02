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
    if (!this->SimulatorVars.at(var)->getDirection()) {
        return;
    }
    write.lock();
    read.lock();
    this->SimulatorVars.at(var)->changeVal(val);
    read.unlock();
    write.unlock();
}
void SymbolTable::ChangeValByProgram(string var, float val) {
    write.lock();
    read.lock();
    this->ProgramVars.at(var)->changeVal(val);
    read.unlock();
    write.unlock();
    this->notify(var, val);
}
float SymbolTable::getValue(string var) {
    float val;
    if (this->SimulatorVars.find(var) != this->SimulatorVars.end()) {
        write.lock();
        val = this->SimulatorVars.at(var)->getVal();
        write.unlock();
    } else {
        write.lock();
        val = this->ProgramVars.at(var)->getVal();
        write.unlock();
    }
    return val;
}
string SymbolTable::getSim(string var) {
    string sim;
    if (this->SimulatorVars.find(var) != this->SimulatorVars.end()) {
        write.lock();
        sim = this->SimulatorVars.at(var)->getSim();
        write.unlock();
    } else {
        write.lock();
        sim = this->ProgramVars.at(var)->getSim();
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

void SymbolTable::initialize() {
    this->indexToVar = {"airspeed-indicator_indicated-speed-kt","time_warp", "switches_magnetos", "heading-indicator_offset-deg",
                             "altimeter_indicated-altitude-ft", "altimeter_pressure-alt-ft", "attitude-indicator_indicated-pitch-deg",
                             "attitude-indicator_indicated-roll-deg", "attitude-indicator_internal-pitch-deg", "attitude-indicator_internal-roll-deg",
                             "encoder_indicated-altitude-ft", "encoder_pressure-alt-ft", "gps_indicated-altitude-ft", "gps_indicated-ground-speed-kt",
                             "gps_indicated-vertical-speed", "indicated-heading-deg", "magnetic-compass_indicated-heading-deg", "slip-skid-ball_indicated-slip-skid",
                             "turn-indicator_indicated-turn-rate", "vertical-speed-indicator_indicated-speed-fpm", "flight_aileron", "flight_elevator",
                             "flight_rudder", "flight_flaps", "engine_throttle", "current-engine_throttle", "switches_master-avionics",
                             "switches_starter", "active-engine_auto-start", "flight_speedbrake", "c172p_brake-parking", "engine_primer",
                             "current-engine_mixture", "switches_master-bat", "switches_master-alt", "engine_rpm"};

}
