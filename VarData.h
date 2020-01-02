//
// Created by yehonatan on 01/01/2020.
//

#ifndef AIRPLANEPROJECT_VARDATA_H
#define AIRPLANEPROJECT_VARDATA_H

#include <string>

using namespace std;
class VarData {
    float Value;
    string sim;
    string ProgramName;
    string SimulatorName;
    //false for "->", true for "<-"
    bool direction;
public:
    VarData(float val, string sim, bool dir, string ProgName, string SimulatorName) {
        this->Value = val;
        this->sim = sim;
        this->direction = dir;
        this->ProgramName = ProgName;
        this->SimulatorName = SimulatorName;
    }
    void changeVal(float newVal) {
        this->Value = Value;
    }
    bool getDirection() {
        return direction;
    }
    string getSim() {
        return sim;
    }
    float getVal() {
        return Value;
    }
};


#endif //AIRPLANEPROJECT_VARDATA_H
