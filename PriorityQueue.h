//
// Created by oren on 31/01/2020.
//

#ifndef EX4_PRIORITYQUEUE_H
#define EX4_PRIORITYQUEUE_H

#include <queue>

template <class T>
class PriorityQueue {
private:
    std::vector<T> pq;
public:
    PriorityQueue() {
        pq = new std::vector<T>();
    }

    void push(T element) {
        pq.push_back(element);
        std::push_heap(pq.begin(), pq.end());
    }

    T& top() {
        return pq.front();
    }

    void pop() {
        std::pop_heap(pq.begin(), pq.end());
        pq.pop_back();
    }

    void update_value(T& element, double key) {
        for (T& temp : pq) {
            if (temp == element) {
                // TODO check the function
                temp.setCost(key);
            }
        }
        std::make_heap(pq.begin(), pq.end());
    }

    bool isContained(T& element) {
        for (T& temp : pq) {
            if (temp == element)
                return true;
        }
        return false;
    }
};

#endif //EX4_PRIORITYQUEUE_H
