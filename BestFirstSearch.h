//
// Created by oren on 31/01/2020.
//

#ifndef EX4_BESTFIRSTSEARCH_H
#define EX4_BESTFIRSTSEARCH_H

#include "HeuristicSearcher.h"
#include <queue>
#include <list>
#include <algorithm>

template <class T>
class BestFirstSearch : public HeuristicSearcher<T> {
public:
    BestFirstSearch(HeuristicFunction<T>& h) : HeuristicSearcher<T>(h) {}

    virtual vector<State<T>*> search(const Searchable<T>* searchable) {
        // get the heuristic function.
        HeuristicFunction<T>& func = this->getHeuristicFunction();

        // set the goal to the goal of the given searchable.
        func.setGoal(searchable.getGoalState());

        // comparator
        auto comparator = [&func](const State<T>*& node1, const State<T>*& node2) {
            return func(*node1) > func(*node2);
        };

        // create the priority queue
        priority_queue<State<T>*, vector<State<T>*>, decltype(comparator)> pq(comparator);

        // black list
        list<State<T>*> black_list;
        State<T>* curr;
        int counter = 0;

        // insert the initial state
        State<T>* init_state = new State<T>(searchable.getInitialState());
        pq.push(init_state);

        // loop until the priority queue is empty
        while (!pq.empty()) {
            curr = pq.top();
            pq.pop();
            black_list.push_back(curr);
            ++counter;

            // goal state
            if (*curr == searchable->getGoalState()) {
                vector<State<T>*> res = new vector<State<T>*>();

                // insert the whole path
                while (curr != nullptr) {
                    res.push_back(curr);
                    curr = curr->getParent();
                }
                return res;
            }

            for (State<T>& node : searchable->getAllPossibleStates(*curr)) {
                State<T>* node_ptr = &node;

                // inspired by @Yehonatan Harmatz
                auto f = [=](const State<T>* node2)->bool { return *node2 == *node_ptr; };
                if (std::find_if(black_list.begin(), black_list.end(), f) == black_list.end()) {
                    // this is the node whose currents parent.
                    node.setParent(*curr);
                    pq.push(new State<T>(node));
                }
            }
        }
        // path does not exist
        vector<State<T>*>* temp = new vector<State<T>*>();
        temp->push_back(nullptr);
        return temp;
    }
};
#endif //EX4_BESTFIRSTSEARCH_H
