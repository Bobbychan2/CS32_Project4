# Project 4 — MiniHub (No Templates) — **Autotest-Only **Skeleton** (You must implement the TODOs)**

This starter is set up so that **`src/main.cpp` runs automated tests** (PASS/FAIL)
instead of an interactive CLI. When you build and run, you will see a small
test suite exercise your `ItemHandle`, `HashTable`, `BST`, sorting functions,
and `Engine` (CSV load/find/erase/list).

If a test fails, read the message and fix the corresponding code in `src/`,
rebuild, and run again until all tests PASS.

---

## Build & Run (no make)

### macOS / Linux
```bash
# Build the test runner
g++ -std=gnu++17 -O2 src/*.cpp -o minihub

# Run it
./minihub
```

### Windows (MinGW)
```bat
REM Build
g++ -std=gnu++17 -O2 src\*.cpp -o minihub.exe

REM Run
minihub.exe
```

> If you use an IDE (VS Code, CLion, Xcode, Visual Studio), create a Console
> project and add all `.cpp` files under `src/`. Set the working directory to
> the project root so `data/sample_small.csv` is found during tests.

---

## What to Implement / Fix

You will edit the following files in `src/`:

- `item.h` / `item.cpp` — `Item` and `ItemHandle` (with the guided **`explicit ItemHandle(std::string)`** ctor), printing, and comparisons.
- `hashtable.h` / `hashtable.cpp` — Chained hash table: `insert`, `find`, `erase`.
- `bst.h` / `bst.cpp` — BST with correct deletion (leaf / one child / **two children via successor**).
- `sorts.h` / `sorts.cpp` — `insertionSortItems`, `mergeSortItems`, `sortItems`.
- `engine.h` / `engine.cpp` — Glue of hash + BST; `loadCSV`, `add`, `eraseByName`, `findByName`, `listInOrder`, `sortSnapshot`.

The automated tests cover:
- Item & printing (exact format: `Category: <Cat> | Name: <Name> | Price : <Price>`)
- Hash table ops (insert/update/find/erase, even with heavy collisions)
- BST insert/contains/inorder and all **three** delete cases; `isValidBST()` checks
- Insertion and Merge sorts (ascending/descending; stability on ties)
- Engine + CSV load/find/erase/list

When you run the program, you’ll see blocks like:
```
== ItemHandle & Printing ==
  [PASS] name getter
  [PASS] category getter
  ...
== HashTable basic ops ==
  [PASS] insert new X
  [PASS] update existing Y
  ...
==== SUMMARY ====  Passed: 27  Failed: 0
```

---

## Data & Golden Example

- `data/sample_small.csv` — Example input used by the tests.
- `golden/session1.txt` — Example CLI transcript (for reference only; this starter does not include the CLI).

---

## Submission Checklist
- All source files under `src/` present and compile.
- Autotest run finishes with **`Failed: 0`**.
- Include a short `report.md` (≤ 1 page) describing:
  - Big-O summary (hash, BST, Insertion, Merge; best/avg/worst; stability).
  - Your two-child delete strategy (successor).
  - One guardrail you added (e.g., duplicate policy).

Good luck! Fix one failing area at a time, rebuild, and re-run until everything passes.


**Important:** This package contains *stubs* in `src/bst.cpp`, `src/hashtable.cpp`, `src/sorts.cpp`, and `src/engine.cpp`.
These compile but intentionally do very little so tests FAIL at first. Your job is to replace the TODO stubs with real implementations until all tests PASS.
