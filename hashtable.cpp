#include "hashtable.h"

HashTable::HashTable(size_t bucketCount) : buckets_(bucketCount ? bucketCount : 1) {}

// TODO: Implement separate chaining insert/update
bool HashTable::insert(const std::string& key, const ItemHandle& value) {
    // STUB: does nothing; return false to signal "updated" (forces tests to fail until implemented)
    (void)key; (void)value;
    return false;
}

// TODO: Implement find (non-const)
ItemHandle* HashTable::find(const std::string& key) {
    (void)key;
    return nullptr; // STUB
}

// TODO: Implement find (const)
const ItemHandle* HashTable::find(const std::string& key) const {
    (void)key;
    return nullptr; // STUB
}

// TODO: Implement erase
bool HashTable::erase(const std::string& key) {
    (void)key;
    return false; // STUB
}
