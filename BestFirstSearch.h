//
// Created by oren on 31/01/2020.
//

#ifndef EX4_BESTFIRSTSEARCH_H
#define EX4_BESTFIRSTSEARCH_H

#include "Searcher.h"
#include <queue>
#include <list>
#include <algorithm>

template <class T>
class BestFirstSearch : public Searcher<pInt> {
public:
    virtual vector<State<T>*> search(const Searchable<T>* searchable) {

        // comparator
        auto comparator = [](State<T>*& node1, State<T>*& node2) {
            return (node2)->getCost() < (node1)->getCost();
        };

        // create the priority queue
        priority_queue<State<T>*, vector<State<T>*>, decltype(comparator)> pq(comparator);

        // black list
        list<State<T>*> black_list;
        list<State<T>*> open_list; ///temp
        State<T>* curr;
        int counter = 0;

        // insert the initial state
        State<T>* init_state = new State<T>(searchable->getInitialState());
        pq.push(init_state);
        open_list.push_front(init_state);
        // loop until the priority queue is empty
        while (!pq.empty()) {
            curr = pq.top();
            pq.pop();
            open_list.remove(curr);
            black_list.push_back(curr);
            ++counter;

            // goal state
            if (*curr == searchable->getGoalState()) {
                vector<State<T>*>* res = new vector<State<T>*>();

                // insert the whole path
                while (curr != nullptr) {
                    res->insert(res->begin(), curr);
                    curr = curr->getParent();
                }
                return *res;
            }

            for (State<T>& node : searchable->getAllPossibleStates(*curr)) {
                State<T>* node_ptr = &node;

                // inspired by @Yehonatan Harmatz
                auto f = [=](const State<T>* node2)->bool { return *node2 == *node_ptr; };
                if (std::find_if(black_list.begin(), black_list.end(), f) == black_list.end()) {
                    if ((std::find_if(open_list.begin(), open_list.end(), f) == open_list.end())) {//if (!pq.isContain(node_ptr) {
                    // this is the node whose currents parent.
                    node.setParent(curr);
                    pq.push(new State<T>(node));
                    open_list.push_front(new State<T>(node));
                    } else if (node_ptr->getLocalCost() + curr->getCost() < node_ptr->getCost()) {
                        list<State<pInt> *> temp;
                        while (!pq.empty()) {
                            temp.push_back(pq.top());
                            pq.pop();
                        }
                        temp.remove(node_ptr);
                        node.setParent(curr);
                        node.setCost(node_ptr->getLocalCost() + curr->getCost());
                        temp.push_back(node_ptr);
                        while (!temp.empty()) {
                            pq.push(temp.front());
                            temp.pop_front();
                        }
                    }
                    //} else if (node_pte->getLocalCost() + curr->getCost() < node_pte->getCost()) {
                    //pq.updateKey(node_ptr, node_pte->getLocalCost() + curr->getCost())
                    //node.setParent(curr);
                    //node.setCost(node_pte->getLocalCost() + curr->getCost());
                    //}
                }
            }
        }
        // path does not exist
        vector<State<T>*>* temp = new vector<State<T>*>();
        temp->push_back(nullptr);
        return *temp;
    }
    BestFirstSearch<T>* clone() {
        return new BestFirstSearch<T>();
    }
    string to_string() {
        return "BestFS";
    }
};
#endif //EX4_BESTFIRSTSEARCH_H
