//
// Created by yehonatan on 21/01/2020.
//

#ifndef EX4_BOOT_H
#define EX4_BOOT_H
#include <iostream>
#include "server_side.h"
#include "MySerialServer.h"
#include "Solver.h"
#include "StringReverser.h"
#include "CacheManager.h"
#include "FileCacheManager2.h"
#include "MyTestClientHandler.h"

namespace boot {
    class Main {
    public:
        int main() {
            server_side::Server* server = new MySerialServer();
            Solver<string, string>* solver = new StringReverser();
            CacheManager<string, string>* cm = new FileCacheManager2(5);
            ClientHandler* ch = new MyTestClientHandler(solver, cm);
            server->open(5656, ch);
            return 0;
        }
    };
}
#endif //EX4_BOOT_H
