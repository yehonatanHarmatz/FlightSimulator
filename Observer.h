//
// Created by yehonatan on 02/01/2020.
//

#ifndef AIRPLANEPROJECT_OBSERVER_H
#define AIRPLANEPROJECT_OBSERVER_H

#include "ChangeValueListener.h"
#include <list>

using namespace std;
class Observer {
    list<ChangeValueListener*> listeners;
public:
    Observer() {
        listeners = list<ChangeValueListener*>();
    }
    virtual void notify(string var, float newVal) {
        for (ChangeValueListener* l : listeners) {
            l->update(var, newVal);
        }
    }
    virtual void addListener(ChangeValueListener* l) {
        listeners.push_back(l);
    }
    virtual void removeListener(ChangeValueListener* l) {
        listeners.remove(l);
    }
    virtual ~Observer() {
        for (ChangeValueListener* l : listeners) {
            delete l;
        }
    }

};
#endif //AIRPLANEPROJECT_OBSERVER_H
