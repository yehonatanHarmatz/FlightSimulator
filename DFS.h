//
// Created by oren on 30/01/2020.
//

#ifndef EX4_DFS_H
#define EX4_DFS_H

#include "Searcher.h"
#include <list>

template <class T>
/*
 * returns the shortest path from initial state to goal state.
 * list of nullptr if such path does not exist.
 */
class DFS : public Searcher<T> {
public:
    virtual vector<State<T>*> search(const Searchable<T>* searchable) {
        list<State<T>*> stack_list; // our stack (DFS algorithm uses stack)
        list<State<T>*> black_list; // the close list (black nodes)
        State<T>* curr;

        // insert the initial state
        State<T> init_state = new State<T>(searchable->getInitialState());
        stack_list.push_back(&init_state); // send by address

        while (!stack_list.empty()) {
            // get the element from the top of the stack
            curr = stack_list.back();
            stack_list.pop_back();
            black_list.insert(curr);

            // if we reached the goal
            if (*curr == searchable->getGoalState()) {
                vector<State<T> *> res = new vector<State<T> *>();
                // insert all the path
                while (curr != nullptr) {
                    res.insert(curr);
                    curr = curr->getParent();
                }
                return res;
            }

            list<State<T>> expand_list = searchable->getAllPossibleStates(*curr);
            expand_list.reverse();
            for (State<T>& node : expand_list) {
                State<T>* node_ptr = &node;

                // only iterate on nodes that are neighbors and the ones who are not in the black list (or just entered)
                if (black_list.find(node_ptr) == black_list.end() &&
                stack_list.find(stack_list.begin(), stack_list.end(), node_ptr) ) {
                    node.setParent(*curr);
                    stack_list.push_back(new State<T>(node)); // returns a pointer to the state
                }
            }
        }
        // the path doesn't exist
        return new vector<State<T>*>(nullptr);
    }
};


#endif //EX4_DFS_H
