#ifndef __PROBING_HASH_H
#define __PROBING_HASH_H

#include <vector>
#include <stdexcept>

#include "Hash.h"

using std::vector;
using std::pair;

// Can be used for tracking lazy deletion for each element in your table
enum EntryState {
    EMPTY = 0,
    VALID = 1,
    DELETED = 2
};

template<typename K, typename V>
class ProbingHash : public Hash<K,V> { // derived from Hash
private:
    // Needs a table and a size.
    // Table should be a vector of std::pairs for lazy deletion
    vector<pair<K, V>> table;
    int size;


public:
    ProbingHash(int n = 11) {
        size = n;
        int newSize = findNextPrime(n);
        table.resize(newSize);
    }

    ~ProbingHash() {
        // Needs to actually free all table contents
        table.clear();
    }

    bool empty() {
        return this->table.empty();
    }

    int size() {
        int count = 0;
        for (auto entry : this->table) {
            if (entry.first!= EMPTY && entry.first != DELETED) {
                count++;
            }
        }
        return count;
    }

    V& at(const K& key) {
        int index = hash(key);
        int start = index;

        do {
            if (table[index].first == key && table[index].second != DELETED) {
                return table[index].second;
            }
            index = (index + 1) % table.size();
        } while (index != start);
        throw std::out_of_range("Key not in hash");
    }

    V& operator[](const K& key) {
        int index = hash(key);
        int start = index;
        do {
            if (table[index].first == key && table[index].second != DELETED) {
                return table[index].second;
            }
            if (table[index].second == EMPTY || table[index].second == DELETED) {
                table[index].first = key;
                table[index].second = V();
                ++count;
                if (load_factor() > 0.75) {
                    rehash(table.size() * 2);
                    index = hash(key);
                }
                return table[index].second;
            }
            index = (index + 1) % table.size();
        } while (index != start);
        throw std::out_of_range("Key not in hash");
    }

    int count(const K& key) {
        int index = hash(key);
        int count = 0;
        for (int i = 0; i < size; i++) {
            if (table_[index].first == key && table_[index].second != DELETED) {
                count++;
            }
            index = (index + i) % size;
        }
        return count;
    }

    void emplace(K key, V value) {
        pair<K, V> pair(key, value);
        insert(pair);
    }

    void insert(const std::pair<K, V>& pair) {
        int index = hash(pair.first);
        for (int i = 0; i < size; i++) {
            if (table_[index].first == pair.first && table_[index].second != DELETED) {
                return;
            }
            if (table_[index].second == EMPTY || table_[index].second == DELETED) {
                table_[index] = std::make_pair(pair.first, pair.second);
                ++element_count_;
                if (load_factor() > max_load_factor_) {
                    rehash();
                }
                return;
            }
            index = (index + i) % size;
        }
    }

    void erase(const K& key) {
        int index = hash(key);
        int start = index;
        while (table[index].first != key && table[index].second != EMPTY) {
            index = (index + 1) % size;
            if (index == start) return;
        }
        if (table[index].first == key) {
            table[index].second = DELETED;
            size--;
        }
    }

    void clear() {
        size = 0;
        for (auto& entry : table) {
            entry.second = EMPTY;
        }
    }

    int bucket_count() {
        return table.size();
    }

    int bucket_size(int n) {
        if (n >= bucket_count()) {
            throw std::out_of_range("Bucket index out of range");
        }
        int count = 0;
        for (auto& entry : table[n]) {
            if (entry.second != DELETED) {
                count++;
            }
        }
        return count;
    }

    int bucket(const K& key) {
        int index = hash(key) % bucket_count();
        for (int i = 0; i < bucket_count(); i++) {
            int j = (index + i) % bucket_count();
            auto& entry = table[j];
            if (entry.first == key && entry.second == VALID) {
                return j;
            } else if (entry.second == EMPTY){
                throw std::out_of_range("Key not in hash");
            }
        }
        throw std::out_of_range("Key not in hash");
    }

    float load_factor() {
        return static_cast<float>(size()) / bucket_count();
    }

    void rehash() {
        rehash(findNextPrime(bucket_count() * 2));
    }

    void rehash(int n) {
        if (n < 11) n = 11;
        vector<pair<K, V>> table2 = table;
        int table2_size = size();
        table = vector<pair<K, V>>(n, make_pair(K(), V()));
        size = 0;

        for (int i = 0; i < tabl2.size(); i++) {
            if (table2[i].first != K() && table2[i].second != V()) {
                insert(table2[i]);
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
        return 0;       
    }
    
};

#endif //__PROBING_HASH_H
