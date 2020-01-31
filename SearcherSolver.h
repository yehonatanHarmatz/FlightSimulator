//
// Created by yehonatan on 28/01/2020.
//

#ifndef EX4_SEARCHERSOLVER_H
#define EX4_SEARCHERSOLVER_H
#include <string>
#include "Solver.h"
#include "Searcher.h"
#include "SearchableTable.h"

using namespace std;

class SearcherSolver : public Solver<SearchableTable, string> {
private:
    Searcher<pInt> *searcher;
public:
    explicit SearcherSolver(Searcher<pInt> *s) : searcher(s) {}

    string& solve(const SearchableTable& problem) {
        vector<State<pInt>*> vec = searcher->search(&problem);
        return castPathToString(vec);
    }

    string& castPathToString(vector<State<pInt>*> vec) {
        string s = "";
        for (int i = 0; i < vec.size() - 1; ++i) {
            int x = vec.at(i)->getValue().first - vec.at(i+1)->getValue().first;
            int y = vec.at(i)->getValue().second - vec.at(i+1)->getValue().second;
            int c = x + 2*y;
            switch (c) {
                case -1:
                    s += "Down (" + ::to_string((int)vec.at(i+1)->getCost()) + ") , ";
                    break;
                case -2:
                    s += "Right (" + ::to_string((int)vec.at(i+1)->getCost()) + ") , ";
                    break;
                case 1:
                    s += "Up (" + ::to_string((int)vec.at(i+1)->getCost()) + ") , ";
                    break;
                case 2:
                    s += "Left (" + ::to_string((int)vec.at(i+1)->getCost()) + ") , ";
                    break;
                default:
                    throw "error";
            }
        }
        s = s.substr(0, s.length() - 2);
        return *(new string(s));
    }
    SearcherSolver* clone() override {
        return new SearcherSolver(searcher->clone());
    }
    string to_string() {
        return searcher->to_string();
    }
};

#endif //EX4_SEARCHERSOLVER_H
