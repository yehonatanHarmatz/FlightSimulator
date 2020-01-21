//
// Created by yehonatan on 20/01/2020.
//

#ifndef EX4_SERVER_SIDE_H
#define EX4_SERVER_SIDE_H

/**
 * name space of server side
 */
#include <mutex>
#include "ClientHandler.h"

namespace server_side
{
    /**
    * interface of server
    */
    class Server {
    public:
        virtual void open(int port, ClientHandler* c) = 0;
        virtual void stop() = 0;
    };
}
#endif //EX4_SERVER_SIDE_H
