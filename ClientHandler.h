//
// Created by yehonatan on 20/01/2020.
//

#ifndef EX4_CLIENTHANDLER_H
#define EX4_CLIENTHANDLER_H
/**
* interface of client handler
*/
using namespace std;
class ClientHandler {
public:
    virtual void handleClient(int& client_socket) = 0;
};
#endif //EX4_CLIENTHANDLER_H
