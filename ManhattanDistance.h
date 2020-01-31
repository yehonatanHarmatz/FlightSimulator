//
// Created by oren on 31/01/2020.
//

#ifndef EX4_MANHATTANDISTANCE_H
#define EX4_MANHATTANDISTANCE_H

#include "HeuristicFunction.h"
typedef pair<int, int> pInt;

class ManhattanDistance : public HeuristicFunction<pInt> {
public:
    ManhattanDistance() : HeuristicFunction() {}

    double operator()(const State<pInt>& curr) const override {
        return abs(curr.getValue().first - goal.getValue().first) + abs(curr.getValue().second - goal.getValue().second);
    }
};

#endif //EX4_MANHATTANDISTANCE_H
