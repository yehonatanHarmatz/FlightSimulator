//
// Created by yehonatan on 20/01/2020.
//

#ifndef EX4_CLIENTHANDLER_H
#define EX4_CLIENTHANDLER_H
/**
* interface of client handler
*/
#include "list"
using namespace std;
class ClientHandler {
public:
    virtual void handleClient(int& client_socket) = 0;
};
/**
 * split function
 * @param str
 * @param token
 * @return
 */
list<string>* split(string str, string token) {
    list<string> *list = new std::list<string>();
    size_t pos = 0;
    while ((pos = str.find(token)) != std::string::npos) {
        list->push_back(str.substr(0, pos));
        str.erase(0, pos + token.length());
    }
    list->push_back(str);
    return list;
}
#endif //EX4_CLIENTHANDLER_H
