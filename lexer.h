//
// Created by yehonatan on 13/12/2019.
//

#ifndef AIRPLANEPROJECT_LEXER_H
#define AIRPLANEPROJECT_LEXER_H

#include <string>
#include <vector>
#include <list>
using namespace std;
/**
 * the lexer class
 */
class lexer {
public:
    vector<string> laxe(const char *file_name);
    string getWord(string s, bool flag);

};
list<string>* split(string str, string token);

#endif //AIRPLANEPROJECT_LEXER_H
