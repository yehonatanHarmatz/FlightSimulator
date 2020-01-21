//
// Created by yehonatan on 20/01/2020.
//

#ifndef EX4_FILECACHEMANAGER_H
#define EX4_FILECACHEMANAGER_H
#include <list>
#include <string>
#include <unordered_map>
#include <iterator>
#include <iostream>
#include <fstream>
#include <functional>
#include "CacheManager.h"

using namespace std;
template <typename T> class FileCacheManager : public CacheManager<string, T> {
    list<string> lru;
    int capacity;
    unordered_map<string, pair<T, typename list<string>::iterator>> objects;
public:
    FileCacheManager(int capacity);
    void insert(string key, T obj);
    T get(string key);
    void foreach(const std::function<void(T&)> func);
    bool isExist(string key) {
        if (FILE *file = fopen((typeid(T).name() + key).c_str(), "r")) {
            fclose(file);
            return true;
        } else {
            return false;
        }
    }
};
using namespace std;
template <typename T>
FileCacheManager<T>::FileCacheManager(int capacity) {
    lru = list<string>();
    this->capacity = capacity;
    this->objects = unordered_map<string, pair<T, typename list<string>::iterator>>();
}
template <typename T>
T FileCacheManager<T>::get(string key) {
    ifstream f;
    if (this->objects.find(key) != objects.end()) {
        lru.erase(this->objects[key].second);
        lru.push_front(key);
        this->objects[key] = pair<T, list<string>::iterator>(this->objects[key].first, lru.begin());
        return this->objects[key].first;
    } else {
        f.open(typeid(T).name() + key, std::ios::binary);
        if (f.bad() || f.eof() || f.peek() == ifstream::traits_type::eof()) {
            throw "error";
        }
        T obj;
        f.read((char*)&obj, sizeof(obj));
        insert(key, obj);
        return obj;
    }
}
template <typename T>
void FileCacheManager<T>::foreach(const std::function<void(T&)> func) {
    for (auto obj: lru) {
        func(this->objects[obj].first);
    }
}
template <typename T>
void FileCacheManager<T>::insert(string key, T obj) {
    ofstream file;
    file.open(typeid(T).name() + key, ios::out | ios::binary | ios::trunc);
    if (file.bad()) {
        throw "error";
    }
    file.write((char*)&obj, sizeof(obj));
    file.close();
    if (this->objects.size()<this->capacity) {
        if (this->objects.find(key) != this->objects.end())
            lru.erase(this->objects[key].second);
        lru.push_front(key);
        this->objects[key] = pair<T,list<string>::iterator>(obj, lru.begin());
    } else {
        list<string>::iterator l1 = --lru.end();
        string toErase = *l1;
        this->objects.erase(toErase);
        lru.erase(l1);
        if (this->objects.find(key) != this->objects.end())
            lru.erase(this->objects[key].second);
        lru.push_front(key);
        this->objects[key] = pair<T,list<string>::iterator>(obj, lru.begin());
    }
}

#endif //EX4_FILECACHEMANAGER_H
