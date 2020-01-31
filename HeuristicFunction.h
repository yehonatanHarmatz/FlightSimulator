//
// Created by oren on 30/01/2020.
//

#ifndef EX4_HEURISTICFUNCTION_H
#define EX4_HEURISTICFUNCTION_H

#include "Searcher.h"
#include <list>

template <class T>
class HeuristicFunction {
protected:
    State<T> goal;
public:
    HeuristicFunction() {}

    double operator()(const State<T>& current) = 0;
    virtual void setGoal(const State<T>& g) {
        this->goal = g;
    }
};

#endif //EX4_HEURISTICFUNCTION_H