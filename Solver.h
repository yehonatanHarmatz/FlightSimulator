//
// Created by yehonatan on 20/01/2020.
//

#ifndef EX4_SOLVER_H
#define EX4_SOLVER_H
/**
 * interface of slover
 */
template<typename Problem, typename Solution> class Solver {
public:
    virtual Solution& solve(const Problem& p) = 0;
};
#endif //EX4_SOLVER_H
