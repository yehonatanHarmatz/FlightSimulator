//
// Created by yehonatan on 02/01/2020.
//

#ifndef AIRPLANEPROJECT_OBSERVER_H
#define AIRPLANEPROJECT_OBSERVER_H

#include "ChangeValueListener.h"
#include <list>

using namespace std;
/**
 * observer interface
 */
class Observer {
protected:
    list<ChangeValueListener*> listeners;
public:
    Observer() {
        listeners = list<ChangeValueListener*>();
    }
    ///notify with var and val
    virtual void notify(string var, float newVal) {
        for (ChangeValueListener* l : listeners) {
            l->update(var, newVal);
        }
    }
    ///notify with index and value
    virtual void notify(int index, float newVal) {
        for (ChangeValueListener* l : listeners) {
            l->update(index, newVal);
        }
    }
    virtual void addListener(ChangeValueListener* l) {
        listeners.push_back(l);
    }
    virtual void removeListener(ChangeValueListener* l) {
        listeners.remove(l);
    }


};
#endif //AIRPLANEPROJECT_OBSERVER_H
