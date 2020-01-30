//
// Created by yehonatan on 20/01/2020.
//

#ifndef EX4_CLIENTHANDLER_H
#define EX4_CLIENTHANDLER_H
/**
* interface of client handler
*/
#include "list"
#include "string"
#include "Cloneable.h"
using namespace std;
class ClientHandler : public Cloneable {
public:
    virtual void handleClient(int& client_socket) = 0;
    virtual ClientHandler* clone() = 0;
};
/**
 * split function
 * @param str
 * @param token
 * @return
 */
list<string>* split(string str, string token);



#endif //EX4_CLIENTHANDLER_H
