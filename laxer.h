//
// Created by yehonatan on 13/12/2019.
//

#ifndef AIRPLANEPROJECT_LAXER_H
#define AIRPLANEPROJECT_LAXER_H

#include <string>
#include <vector>
#include <list>
using namespace std;
/**
 * the lexer class
 */
class laxer {
public:
    vector<string> laxe(const char *file_name);
    string getWord(string s, bool flag);

};
list<string>* split(string str, string token);

#endif //AIRPLANEPROJECT_LAXER_H
