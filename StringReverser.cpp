//
// Created by yehonatan on 21/01/2020.
//

#include "StringReverser.h"

string &StringReverser::solve(const string &p) {
    string* reverse = new string();
    *reverse = "";
    for (int i = p.length() - 1; i >= 0; --i) {
        *reverse += p[i];
    }
    return *reverse;
}
