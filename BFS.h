//
// Created by yehonatan on 31/01/2020.
//

#ifndef EX4_BFS_H
#define EX4_BFS_H
#include "Searcher.h"
#include "list"
#include <algorithm>

using namespace std;
template <class T>
/*
 * returns the shortest path from initial state to goal state.
 * list of nullptr if such path does not exist.
 */
class BFS : public Searcher<T> {
public:
    virtual vector<State<T>*> search(const Searchable<T>* searchable) {
        list<State<T>*> queue_list; // our stack (BFS algorithm uses queue)
        list<State<T>*> black_list; // the close list (black nodes)
        State<T>* curr;

        // insert the initial state
        State<T>* init_state = new State<T>(searchable->getInitialState());
        queue_list.push_front(init_state); // send by address

        while (!queue_list.empty()) {
            // get the element from the top of the stack
            curr = queue_list.front();
            queue_list.pop_front();
            black_list.push_back(curr);

            // if we reached the goal
            if (*curr == searchable->getGoalState()) {
                vector<State<T>*>* res = new vector<State<T> *>();
                // insert all the path
                while (curr != nullptr) {
                    res->insert(res->begin(),curr);
                    curr = curr->getParent();
                }
                return *res;
            }

            list<State<T>> expand_list = searchable->getAllPossibleStates(*curr);
            expand_list.reverse();
            for (State<T>& node : expand_list) {
                State<T>* node_ptr = &node;
                auto f = [=](const State<T>* node2)->bool { return *node2 == *node_ptr; };
                // only iterate on nodes that are neighbors and the ones who are not in the black list (or just entered)
                if ((std::find_if(black_list.begin(),black_list.end(), f) == black_list.end()) &&
                    (std::find_if(queue_list.begin(), queue_list.end(), f) == queue_list.end())) {
                    node.setParent(curr);
                    queue_list.push_back(new State<T>(node)); // returns a pointer to the state
                }
            }
        }
        // the path doesn't exist
        vector<State<T>*>* temp = new vector<State<T>*>();
        temp->push_back(nullptr);
        return *temp;
    }
    BFS<T>* clone() {
        return new BFS<T>();
    }
    string to_string() {
        return "BFS";
    }
};

#endif //EX4_BFS_H
