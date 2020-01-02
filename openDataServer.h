//
// Created by yehonatan on 02/01/2020.
//

#ifndef AIRPLANEPROJECT_OPENDATASERVER_H
#define AIRPLANEPROJECT_OPENDATASERVER_H

#include <string>
#include <vector>
#include <mutex>
#include "Observer.h"

using namespace std;
class openDataServer: Observer {
    vector<string> params;
    bool keep_running = true;
    mutex mtx;
public:
    openDataServer(vector<string> params) {
        this->params = params;
    }

    void openServer(int port);

    int execute(int index);
    void stopRun() {
        mtx.lock();
        keep_running = false;
        mtx.unlock();
    }

};


#endif //AIRPLANEPROJECT_OPENDATASERVER_H
