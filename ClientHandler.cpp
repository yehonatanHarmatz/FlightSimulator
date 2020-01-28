//
// Created by yehonatan on 28/01/2020.
//
#include "ClientHandler.h"
#include "string"
list <string> *split(string str, string token) {
    list<string> *list = new std::list<string>();
    size_t pos = 0;
    while ((pos = str.find(token)) != std::string::npos) {
        list->push_back(str.substr(0, pos));
        str.erase(0, pos + token.length());
    }
    list->push_back(str);
    return list;
}