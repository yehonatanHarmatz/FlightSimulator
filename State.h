//
// Created by oren on 30/01/2020.
//

#ifndef EX4_STATE_H
#define EX4_STATE_H

/**
 * a state represents a situation
 * @tparam T the type of the state
 */
template <class T>
class State {
protected:
    T state;  // the state we represent
    double cost;  // the cost to reach that state
    State<T>* cameFrom;  // the State we came from (setter)

public:
    // constructor
    explicit State(T state) {
        this->state = state;
        this->cameFrom = nullptr;
    }

    State() {
        this->cameFrom = nullptr;
    }

    ~State() { }

    bool operator==(const State<T>& s) const { return this->state == s.state; }
    bool operator<(const State<T>& s) const { return this->state < s.state; }
    void setParent (State<T>* parent) { this->cameFrom = parent; }
    void setCost (double cost) { this->cost = cost; }
    double getCost () const { return this->cost; }
    State<T>* getParent () const { return this->cameFrom; }
    T getValue () const { return this->state; }
};

#endif //EX4_STATE_H
