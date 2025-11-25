#include "bst.h"

BST::BST() = default;
BST::~BST() { clear(root_); }

void BST::clear(Node* n) {
    if (!n) return;
    clear(n->left);
    clear(n->right);
    delete n;
}

// TODO: Implement insert (ignore duplicate)
BST::Node* BST::insertNode(Node* n, const ItemHandle& v, bool& added) {
    (void)n; (void)v; added = false;
    return n; // STUB
}

void BST::insert(const ItemHandle& v) {
    bool added = false;
    root_ = insertNode(root_, v, added);
    if (added) ++size_;
}

// TODO: Implement contains
bool BST::containsNode(Node* n, const ItemHandle& v) {
    (void)n; (void)v;
    return false; // STUB
}
bool BST::contains(const ItemHandle& v) const { return containsNode(root_, v); }

// TODO: Implement inorder traversal
void BST::inorderWalk(Node* n, std::vector<ItemHandle>& out) {
    (void)n; (void)out;
}
void BST::inorder(std::vector<ItemHandle>& out) const { out.clear(); inorderWalk(root_, out); }

// TODO: Implement validity check (strict BST)
bool BST::isValid(Node* n, const ItemHandle* lo, const ItemHandle* hi) {
    (void)n; (void)lo; (void)hi;
    return true; // STUB (kept true so tests progress past basic check)
}
bool BST::isValidBST() const { return isValid(root_, nullptr, nullptr); }

// Helper for two-child delete (successor)
BST::Node* BST::detachMin(Node* n, Node*& minNode) {
    // STUB for now
    minNode = nullptr;
    return n;
}

// TODO: Implement erase (leaf / one child / two children via successor)
BST::Node* BST::eraseNode(Node* n, const ItemHandle& v, bool& erased) {
    (void)n; (void)v; erased = false;
    return n; // STUB
}

bool BST::erase(const ItemHandle& v) {
    bool erased = false;
    root_ = eraseNode(root_, v, erased);
    if (erased) --size_;
    return erased;
}
