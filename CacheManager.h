//
// Created by yehonatan on 20/01/2020.
//

#ifndef EX4_CACHEMANAGER_H
#define EX4_CACHEMANAGER_H

using namespace std;
template <typename K, typename T> class CacheManager{

public:
    virtual void insert(K key, T object) = 0;
    virtual T get(K key) = 0;
    virtual bool isExist(K key) = 0;
};
#endif //EX4_CACHEMANAGER_H
