//
// Created by oren on 30/01/2020.
//

#ifndef EX4_SEARCHABLE_H
#define EX4_SEARCHABLE_H

#include <list>
#include <functional>
#include <string>
#include "State.h"

/**
 * represent a problem of search
 * @tparam T the type of the state
 */
template <class T>
class Searchable {
public:
    virtual State<T> getInitialState() const = 0;
    virtual State<T> getGoalState() const = 0;

    /**
     * get all the develop states from the state (s)
     * @param s the state to develop
     * @return all possible states
     */
    virtual std::list<State<T>> getAllPossibleStates(const State<T>& s) const = 0;
    virtual ~Searchable() {};
    virtual bool operator==(const Searchable<T>&) const = 0;
    virtual size_t hash() const = 0;
    virtual std::string toString() const = 0;
};

#endif //EX4_SEARCHABLE_H