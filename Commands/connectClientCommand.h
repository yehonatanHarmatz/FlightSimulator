//
// Created by yehonatan on 03/01/2020.
//

#ifndef AIRPLANEPROJECT_CONNECTCLIENTCOMMAND_H
#define AIRPLANEPROJECT_CONNECTCLIENTCOMMAND_H


#include "command.h"

class connectClientCommand : command{
public:
    connectClientCommand(vector<string>* params): command(params) {}

};


#endif //AIRPLANEPROJECT_CONNECTCLIENTCOMMAND_H
