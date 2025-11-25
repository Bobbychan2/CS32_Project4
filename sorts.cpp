#include "sorts.h"
#include <algorithm>

// TODO: Implement stable insertion sort on vector<ItemHandle>
void insertionSortItems(std::vector<ItemHandle>& a, bool ascending) {
    (void)a; (void)ascending; // STUB: no-op
}

// TODO: Implement stable merge sort on vector<ItemHandle>
void mergeSortItems(std::vector<ItemHandle>& a, bool ascending) {
    (void)a; (void)ascending; // STUB: no-op
}

void sortItems(std::vector<ItemHandle>& a, SortAlgo algo, bool ascending) {
    switch (algo) {
        case SortAlgo::Insertion: insertionSortItems(a, ascending); break;
        case SortAlgo::Merge:     mergeSortItems(a,     ascending); break;
    }
}
