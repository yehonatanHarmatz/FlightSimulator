//
// Created by yehonatan on 21/01/2020.
//

#ifndef EX4_BOOT_H
#define EX4_BOOT_H
#include <iostream>
#include "server_side.h"
#include "MySerialServer.h"
#include "MyParallelServer.h"
#include "Solver.h"
#include "StringReverser.h"
#include "CacheManager.h"
#include "FileCacheManager2.h"
#include "MyClientHandler.h"
#include "Searcher.h"
#include "SearchableTable.h"
#include "SearcherSolver.h"
#include "DFS.h"
#include "BFS.h"
#include "Astar.h"
#include "BestFirstSearch.h"
#include "ManhattanDistance.h"
namespace boot {
    class Main {
    public:
        int main(int i) {
            Solver<SearchableTable, string>* solver = new SearcherSolver(new Astar<pInt>(new ManhattanDistance()));
            server_side::Server* server = new MyParallelServer();
            //Solver<string, string>* solver = new StringReverser();
            CacheManager<string, string>* cm = new FileCacheManager2(5);
            ClientHandler* ch = new MyClientHandler(solver, cm);
            server->open(i, ch);
            return 0;
        }
    };
}
#endif //EX4_BOOT_H
