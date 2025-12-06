#include "bst.h"

BST::BST() = default;
BST::~BST() { clear(root_); }

void BST::clear(Node* n) {
    if (!n) return;
    clear(n->left);
    clear(n->right);
    delete n;
}

// insert helper (ignore duplicate by same name+category)
BST::Node* BST::insertNode(Node* n, const ItemHandle& v, bool& added) {
    if (!n) {
        added = true;
        return new Node(v);
    }

    if (v == n->val) {
        // Duplicate (same name+category) → ignore
        added = false;
        return n;
    }

    if (v < n->val) {
        n->left = insertNode(n->left, v, added);
    }
    else {
        // v > n->val (since we already handled equality)
        n->right = insertNode(n->right, v, added);
    }
    return n;
}

void BST::insert(const ItemHandle& v) {
    bool added = false;
    root_ = insertNode(root_, v, added);
    if (added) ++size_;
}

// contains helper
bool BST::containsNode(Node* n, const ItemHandle& v) {
    if (!n) return false;
    if (v == n->val) return true;

    if (v < n->val) {
        return containsNode(n->left, v);
    }
    else {
        return containsNode(n->right, v);
    }
}

bool BST::contains(const ItemHandle& v) const { return containsNode(root_, v); }

// helper for inorder traversal
void BST::inorderWalk(Node* n, std::vector<ItemHandle>& out) {
    if (!n) return;
    inorderWalk(n->left, out);
    out.push_back(n->val);
    inorderWalk(n->right, out);
}

void BST::inorder(std::vector<ItemHandle>& out) const {
    out.clear();
    inorderWalk(root_, out);
}

// strict validit check
bool BST::isValid(Node* n, const ItemHandle* lo, const ItemHandle* hi) {
    if (!n) return true;

    // All keys must satisfy: lo < n->val < hi (strict)
    if (lo && !(*lo < n->val)) return false;
    if (hi && !(n->val < *hi)) return false;

    return isValid(n->left, lo, &n->val) &&
        isValid(n->right, &n->val, hi);
}

bool BST::isValidBST() const { return isValid(root_, nullptr, nullptr); }

// detachMin: remove smallest node from subtree rooted at n
// - minNode receives pointer to removed node
// - returns new root of this subtree (after removal)
BST::Node* BST::detachMin(Node* n, Node*& minNode) {
    if (!n) {
        minNode = nullptr;
        return nullptr;
    }

    if (!n->left) {
        // n is the minimum
        minNode = n;
        Node* rightSub = n->right;
        n->left = n->right = nullptr;   // detach fully
        return rightSub;                // new root of this subtree
    }

    n->left = detachMin(n->left, minNode);
    return n;
}

// erase helper (leaf / one child / two children via successor)
BST::Node* BST::eraseNode(Node* n, const ItemHandle& v, bool& erased) {
    if (!n) {
        erased = false;
        return nullptr;
    }

    if (v < n->val) {
        n->left = eraseNode(n->left, v, erased);
        return n;
    }
    else if (n->val < v) {
        n->right = eraseNode(n->right, v, erased);
        return n;
    }
    else {
        // Found node to erase
        erased = true;

        // Case 1: leaf
        if (!n->left && !n->right) {
            delete n;
            return nullptr;
        }

        // Case 2: one child
        if (!n->left) {
            Node* r = n->right;
            delete n;
            return r;
        }
        if (!n->right) {
            Node* l = n->left;
            delete n;
            return l;
        }

        // Case 3: two children → replace with in-order successor (min of right subtree)
        Node* succ = nullptr;
        n->right = detachMin(n->right, succ); // succ removed from right subtree
        // succ now becomes the new root of this subtree
        succ->left = n->left;
        succ->right = n->right;
        delete n;
        return succ;
    }
}

bool BST::erase(const ItemHandle& v) {
    bool erased = false;
    root_ = eraseNode(root_, v, erased);
    if (erased) --size_;
    return erased;
}
