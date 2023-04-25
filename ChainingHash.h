/*
 *  Separate chaining hashtable
 */

#ifndef __CHAINING_HASH_H
#define __CHAINING_HASH_H

// Standard library includes
#include <iostream>
#include <vector>
#include <list>
#include <stdexcept>

// Custom project includes
#include "Hash.h"

// Namespaces to include
using std::vector;
using std::list;
using std::pair;

using std::cout;
using std::endl;

//
// Separate chaining based hash table - derived from Hash
//
template<typename K, typename V>
class ChainingHash : public Hash<K,V> {
private:
    vector<list<pair<K, V>>> table;
    int num_elements;
    int table_size;

public:
    ChainingHash(int n = 11) {
        table_size = n;
        table.resize(n);
        num_elements = 0;
    }

    ~ChainingHash() {
        this->clear();
    }

    bool empty() {
        return size() == 0;
    }

    int size() {
        return num_elements;
    }

    V& at(const K& key) {
        int index = hash(key);
        auto itr = find_if(table[index].begin(), table[index].end(), [&key](const auto& element) { return element.first == key && !element.second.deleted;});
        if (itr == table[index].end()) {
            throw std::out_of_range("Key not in hash");
        }
        return itr->second.value;
    }

    V& operator[](const K& key) {
        int index = hash(key);
        auto itr = find_if(table[index].begin(), table[index].end(), [&key](const auto& element) { return element.first == key && !element.second.deleted;});
        if (itr == table[index].end()) {
            table[index].emplace_back(key, V());
            it = prev(table[index].end());
        }
        return itr->second.value;
    }

    int count(const K& key) {
        int count = 0;
        int index = hash(key);
        for (auto& pair : this->table[index]) {
            if (pair.first == key) {
                count++;
            }
        }
        return count;
    }

    void emplace(K key, V value) {
        int index = hash(key);
        for (auto& pair : this->table[index]) {
            fi (pair.first == key) {
                pair.second = value;
                return;
            }
        }
        this->table[index].emplace_back(key, value);
        num_elements++;

        if (load_factor() > 0.75) {
            rehash();
        }
    }

    void insert(const std::pair<K, V>& pair) {
        auto& entry = table[hash(pair.first)];
        entry.push_back(pair);
        ++num_elements;
        if (load_factor() > 0.75) {
            rehash();
        }
    }

    void erase(const K& key) {
        size_t index = hash(key) % num_elements;
        auto& bucket = table[index];
        auto itr = bucket.begin();
        while (itr != bucket.end()) {
            if(itr->first == key) {
                bucket.erase(itr);
                --num_elements;
            } else {
                ++itr;
            }
        }
    }

    void clear() {
        currSize = 0;
        for (auto& list : table) {
            table.clear();
        }
    }

    int bucket_count() {
        return table.size();
    }

    int bucket_size(int n) {
        return table[n].size();
    }

    int bucket(const K& key) {
        return hash[key];
    }

    float load_factor() {
        return static_cast<float>(size_) / static_cast<float>(bucket_count_);
    }

    void rehash() {
        int new_size = findNextPrime(table_size * 2);
        rehash(new_size);
    }

    void rehash(int n) {
        vector<list<pair<K, V>>> table2 = this->table;
        table.resize(n);
        table_size = n;

        for (auto & list : table) {
            list.clear();
        } 
        
        num_elements = 0;
        for (auto & list : table2) {
            for (auto & x : list) {
                insert(std::move(x));
            }
        }
    }


private:
    int findNextPrime(int n)
    {
        while (!isPrime(n))
        {
            n++;
        }
        return n;
    }

    int isPrime(int n)
    {
        for (int i = 2; i <= sqrt(n); i++)
        {
            if (n % i == 0)
            {
                return false;
            }
        }

        return true;
    }

    int hash(const K& key) {
        int hashValue = 0;

        for (const char& c : std::to_string(key)) {
            hashValue = (hashValue * 31 + c) % this->currentSize;
        }

        return hashValue;       
    }

};

#endif //__CHAINING_HASH_H
