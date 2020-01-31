//
// Created by oren on 31/01/2020.
//

#ifndef EX4_HEURISTICSEARCHER_H
#define EX4_HEURISTICSEARCHER_H

#include "HeuristicFunction.h"

template <class T>

class HeuristicSearcher : public Searcher<T> {
private:
    const HeuristicFunction<T>& h;
public:
    HeuristicSearcher(const HeuristicFunction<T>& func) : h(func) {}
    virtual vector<State<T>*> search(const Searchable<T>* searchable) = 0;
    HeuristicFunction<T>& getHeuristicFunction() {
        return this->h;
    }
};

#endif //EX4_HEURISTICSEARCHER_H
