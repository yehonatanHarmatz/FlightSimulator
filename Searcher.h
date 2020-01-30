//
// Created by yehonatan on 28/01/2020.
//

#ifndef EX4_SEARCHER_H
#define EX4_SEARCHER_H

#include "searchable.h"
#include "vector"
#include "Cloneable.h"
using namespace std;
template <typename T>
class Searcher : public Cloneable {
public:
    ///get searchable object and return the path of the solution
    virtual vector<State<T>*> search(const Searchable<T>* searchable) = 0;
    virtual Searcher<T>* clone() = 0;

};
#endif //EX4_SEARCHER_H
