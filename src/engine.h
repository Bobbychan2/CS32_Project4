#pragma once
#include "item.h"
#include "bst.h"
#include "hashtable.h"
#include "sorts.h"
#include <string>
#include <vector>

class Engine {
public:
    explicit Engine(size_t hashBuckets = 256);

    void loadCSV(const std::string& path);           // prints summary internally
    bool add(const ItemHandle& item);                // no duplicates by (name, category)
    bool eraseByName(const std::string& name);       // removes first match by name
    const ItemHandle* findByName(const std::string& name) const;

    void listInOrder(std::vector<ItemHandle>& out) const;
    void sortSnapshot(std::vector<ItemHandle>& out, SortAlgo algo, bool ascending) const;

private:
    HashTable byName_;  // key: item name
    BST       ordered_; // ordered by operator<
};
