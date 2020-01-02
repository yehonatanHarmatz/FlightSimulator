//
// Created by yehonatan on 02/01/2020.
//

#ifndef AIRPLANEPROJECT_CHANGEVALUELISTENER_H
#define AIRPLANEPROJECT_CHANGEVALUELISTENER_H

#include <string>
using namespace std;
class ChangeValueListener {
public:
    virtual void update(string var, float newVal) = 0;
};
#endif //AIRPLANEPROJECT_CHANGEVALUELISTENER_H
