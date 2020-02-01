//
// Created by yehonatan on 21/01/2020.
//

#ifndef EX4_FILECACHEMANAGER2_H
#define EX4_FILECACHEMANAGER2_H
#include <list>
#include <string>
#include <unordered_map>
#include <iterator>
#include <iostream>
#include <fstream>
#include <functional>
#include "CacheManager.h"
#include "mutex"

using namespace std;
class FileCacheManager2 : public CacheManager<string, string> {
    list<string> lru;
    mutex mtx;
    int capacity;
    unordered_map<string, pair<string, typename list<string>::iterator>> objects;
public:
    FileCacheManager2(int capacity);
    void insert(string key, string obj);
    string get(string key);
    void foreach(const std::function<void(string&)> func);
    bool isExist(string key) {
        mtx.lock();
        if (FILE *file = fopen(key.c_str(), "r")) {
            fclose(file);
            mtx.unlock();
            return true;
        } else {
            mtx.unlock();
            return false;
        }
    }
};
using namespace std;
FileCacheManager2::FileCacheManager2(int capacity) {
    lru = list<string>();
    this->capacity = capacity;
    this->objects = unordered_map<string, pair<string, typename list<string>::iterator>>();
}

string FileCacheManager2::get(string key) {
    mtx.lock();
    ifstream f;
    if (this->objects.find(key) != objects.end()) {
        lru.erase(this->objects[key].second);
        lru.push_front(key);
        this->objects[key] = pair<string, list<string>::iterator>(this->objects[key].first, lru.begin());
        mtx.unlock();
        return this->objects[key].first;
    } else {
        f.open(key);
        if (f.bad() || f.eof() || f.peek() == ifstream::traits_type::eof()) {
            mtx.unlock();
            throw "error";
        }
        string obj((std::istreambuf_iterator<char>(f)),
                   std::istreambuf_iterator<char>());
        mtx.unlock();
        insert(key, obj);
        return obj;
    }
}
void FileCacheManager2::foreach(const std::function<void(string&)> func) {
    for (auto obj: lru) {
        func(this->objects[obj].first);
    }
}

void FileCacheManager2::insert(string key, string obj) {
    mtx.lock();
    ofstream file;
    file.open(key, ios::out | ios::trunc);
    if (file.bad()) {
        mtx.unlock();
        throw "error";
    }
    file << obj;
    file.close();
    if (this->objects.size()<this->capacity) {
        if (this->objects.find(key) != this->objects.end())
            lru.erase(this->objects[key].second);
        lru.push_front(key);
        this->objects[key] = pair<string,list<string>::iterator>(obj, lru.begin());
    } else {
        list<string>::iterator l1 = --lru.end();
        string toErase = *l1;
        this->objects.erase(toErase);
        lru.erase(l1);
        if (this->objects.find(key) != this->objects.end())
            lru.erase(this->objects[key].second);
        lru.push_front(key);
        this->objects[key] = pair<string,list<string>::iterator>(obj, lru.begin());
    }
    mtx.unlock();
}
#endif //EX4_FILECACHEMANAGER2_H
