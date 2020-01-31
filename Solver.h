//
// Created by yehonatan on 20/01/2020.
//

#ifndef EX4_SOLVER_H
#define EX4_SOLVER_H

#include "Cloneable.h"
#include "string"
/**
 * interface of slover
 */
template<typename Problem, typename Solution> class Solver : public Cloneable {
public:
    virtual Solution& solve(const Problem& p) = 0;
    virtual Solver* clone() = 0;

    virtual std::string to_string() = 0;
};
#endif //EX4_SOLVER_H
