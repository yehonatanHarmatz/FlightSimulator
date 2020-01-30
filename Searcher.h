//
// Created by yehonatan on 28/01/2020.
//

#ifndef EX4_SEARCHER_H
#define EX4_SEARCHER_H

#include "Searchable.h"
#include "vector"

using namespace std;

template <typename T>
class Searcher {
public:
    ///get searchable object and return the path of the solution
    virtual vector<State<T>*> search(const Searchable<T>* searchable) = 0;
};

#endif //EX4_SEARCHER_H
