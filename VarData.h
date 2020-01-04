//
// Created by yehonatan on 01/01/2020.
//

#ifndef AIRPLANEPROJECT_VARDATA_H
#define AIRPLANEPROJECT_VARDATA_H

#include <string>

using namespace std;
/**
 * object of unit of data
 */
class VarData {
    float Value;
    string sim;
    ///false for "->", true for "<-"
    bool direction;
public:
    VarData(float val, string sim, bool dir) {
        this->Value = val;
        this->sim = sim;
        this->direction = dir;
    }
    void changeVal(float newVal) {
        this->Value = newVal;
    }
    void changeDirection(bool newDir) {
        this->direction = newDir;
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
