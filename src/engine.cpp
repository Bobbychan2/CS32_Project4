#include "engine.h"
#include "provided.h"
#include <iostream>

Engine::Engine(size_t hashBuckets) : byName_(hashBuckets) {}

void Engine::loadCSV(const std::string& path) {
    using provided::now; using provided::ms_between;
    auto t0 = now();
    std::vector<ItemHandle> items;
    size_t skipped = 0;
    if (!provided::readCSV(path, items, skipped)) {
        std::cout << "ERROR: cannot open " << path << "\n";
        return;
    }
    size_t loaded = 0;
    for (const auto& h : items) {
        if (add(h)) ++loaded;
    }
    auto t1 = now();
    std::cout << "LOADED " << loaded << " (skipped " << skipped << ") in "
        << ms_between(t0, t1) << " ms\n";
}

bool Engine::add(const ItemHandle& item) {
    // 1) Duplicate policy: no duplicates by (name, category)
    if (ordered_.contains(item)) {
        return false;   // duplicate, do nothing
    }

    const std::string& key = item.name();

    // 2) If name already exists in hash, we treat it as a duplicate for safety,
    //    to avoid inconsistencies (hash can only store one value per name).
    if (byName_.find(key) != nullptr) {
        return false;   // already have some item with this name
    }

    // 3) Insert into hash and BST atomically
    bool insertedHash = byName_.insert(key, item);
    if (!insertedHash) {
        // Shouldn't happen with the check above, but be defensive: treat as duplicate
        return false;
    }

    // Insert into BST
    ordered_.insert(item);
    return true;
}

bool Engine::eraseByName(const std::string& name) {
    // Find in hash table first
    ItemHandle* p = byName_.find(name);
    if (!p) return false;

    // Copy the handle so we can erase it from BST
    ItemHandle toErase = *p;

    bool erasedHash = byName_.erase(name);
    bool erasedBST = ordered_.erase(toErase);

    // Under normal operation, both should be true.
    return erasedHash && erasedBST;
}

const ItemHandle* Engine::findByName(const std::string& name) const {
    return byName_.find(name);
}

void Engine::listInOrder(std::vector<ItemHandle>& out) const {
    ordered_.inorder(out);
}

void Engine::sortSnapshot(std::vector<ItemHandle>& out, SortAlgo algo, bool ascending) const {
    ordered_.inorder(out);
    sortItems(out, algo, ascending);
}



/*
#include "engine.h"
#include "provided.h"
#include <iostream>

Engine::Engine(size_t hashBuckets) : byName_(hashBuckets) {}

void Engine::loadCSV(const std::string& path) {
    using provided::now; using provided::ms_between;
    auto t0 = now();
    std::vector<ItemHandle> items;
    size_t skipped = 0;
    if (!provided::readCSV(path, items, skipped)) {
        std::cout << "ERROR: cannot open " << path << "\n";
        return;
    }
    size_t loaded = 0;
    for (const auto& h : items) {
        if (add(h)) ++loaded; // With stubs, this will likely be 0
    }
    auto t1 = now();
    std::cout << "LOADED " << loaded << " (skipped " << skipped << ") in "
              << ms_between(t0, t1) << " ms\n";
}

bool Engine::add(const ItemHandle& item) {
    // TODO: Implement: check BST duplicate, insert into hash and BST atomically
    (void)item;
    return false; // STUB forces tests to fail until implemented
}

bool Engine::eraseByName(const std::string& name) {
    // TODO: Implement: find by name in hash, remove from both structures
    (void)name;
    return false; // STUB
}

const ItemHandle* Engine::findByName(const std::string& name) const {
    return byName_.find(name);
}

void Engine::listInOrder(std::vector<ItemHandle>& out) const {
    ordered_.inorder(out);
}

void Engine::sortSnapshot(std::vector<ItemHandle>& out, SortAlgo algo, bool ascending) const {
    ordered_.inorder(out);
    sortItems(out, algo, ascending);
}
*/
