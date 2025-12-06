#include "sorts.h"
#include <algorithm>

// helper for comparator
static bool itemLess(const ItemHandle& lhs,
    const ItemHandle& rhs,
    bool ascending) {
    if (ascending) {
        return lhs < rhs;
    }
    else {
        return rhs < lhs;  // invert to descending
    }
}

// Stable insertion sort
void insertionSortItems(std::vector<ItemHandle>& a, bool ascending) {
    const std::size_t n = a.size();
    for (std::size_t i = 1; i < n; ++i) {
        ItemHandle key = a[i];
        std::size_t j = i;

        // move strictly-greater elements; ties stay in original order (stable)
        while (j > 0 && itemLess(key, a[j - 1], ascending)) {
            a[j] = a[j - 1];
            --j;
        }
        a[j] = key;
    }
}

//Stable merge sort (no default ctor needed)

// merge [left, mid) and [mid, right) into sorted [left, right)
static void mergeRanges(std::vector<ItemHandle>& a,
    std::size_t left,
    std::size_t mid,
    std::size_t right,
    bool ascending,
    std::vector<ItemHandle>& temp)
{
    std::size_t i = left;
    std::size_t j = mid;

    temp.clear();
    temp.reserve(right - left);   // reserve capacity only; no ItemHandle() calls

    // build temp via push_back (copy/move only)
    while (i < mid && j < right) {
        if (itemLess(a[j], a[i], ascending)) {
            temp.push_back(a[j++]);
        }
        else {
            temp.push_back(a[i++]);  // stable: left side wins on ties
        }
    }
    while (i < mid)  temp.push_back(a[i++]);
    while (j < right) temp.push_back(a[j++]);

    // copy back
    for (std::size_t k = 0; k < temp.size(); ++k) {
        a[left + k] = temp[k];
    }
}

static void mergeSortRec(std::vector<ItemHandle>& a,
    std::size_t left,
    std::size_t right,
    bool ascending,
    std::vector<ItemHandle>& temp)
{
    if (right - left <= 1) return;

    std::size_t mid = left + (right - left) / 2;
    mergeSortRec(a, left, mid, ascending, temp);
    mergeSortRec(a, mid, right, ascending, temp);
    mergeRanges(a, left, mid, right, ascending, temp);
}

void mergeSortItems(std::vector<ItemHandle>& a, bool ascending) {
    if (a.size() <= 1) return;

    std::vector<ItemHandle> temp;
    temp.reserve(a.size());   // still no default ctor used
    mergeSortRec(a, 0, a.size(), ascending, temp);
}

void sortItems(std::vector<ItemHandle>& a, SortAlgo algo, bool ascending) {
    switch (algo) {
    case SortAlgo::Insertion: insertionSortItems(a, ascending); break;
    case SortAlgo::Merge:     mergeSortItems(a, ascending); break;
    }
}