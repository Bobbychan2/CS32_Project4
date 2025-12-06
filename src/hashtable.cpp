#include "hashtable.h"

HashTable::HashTable(size_t bucketCount) : buckets_(bucketCount ? bucketCount : 1) {}

// separate chaining insert/update
bool HashTable::insert(const std::string& key, const ItemHandle& value) {
    size_t idx = indexFor(key);
    auto& bucket = buckets_[idx];

    // Look for existing key
    for (auto& node : bucket) {
        if (node.first == key) {
            // Update existing value, do NOT change size_
            node.second = value;
            return false;    // updated existing
        }
    }

    // Not found, so insert new node
    bucket.emplace_back(key, value);
    ++size_;
    return true; // inserted new
}

// find (non-const)
ItemHandle* HashTable::find(const std::string& key) {
    size_t idx = indexFor(key);
    auto& bucket = buckets_[idx];

    for (auto& node : bucket) {
        if (node.first == key) {
            return &node.second;
        }
    }
    return nullptr;
}

// find (const)
const ItemHandle* HashTable::find(const std::string& key) const {
    size_t idx = indexFor(key);
    const auto& bucket = buckets_[idx];

    for (const auto& node : bucket) {
        if (node.first == key) {
            return &node.second;
        }
    }
    return nullptr;
}

// erase
bool HashTable::erase(const std::string& key) {
    size_t idx = indexFor(key);
    auto& bucket = buckets_[idx];

    for (auto it = bucket.begin(); it != bucket.end(); ++it) {
        if (it->first == key) {
            bucket.erase(it);
            --size_;
            return true;
        }
    }
    return false;  // not found
}

