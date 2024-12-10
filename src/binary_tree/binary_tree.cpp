#include "binary_tree.h"
#include <stdexcept>

// Constructor
BinaryTree::BinaryTree() : root(nullptr) {}

// Destructor
BinaryTree::~BinaryTree() {
    clear(root);
}

// Helper to clear the tree - recursively delete all nodes in the tree
void BinaryTree::clear(Node* node) {
    if (node) {
        clear(node->left);  // Clear the left subtree
        clear(node->right); // Clear the right subtree
        delete node;        // Delete the current node
    }
}

// Add a value to the BST
void BinaryTree::Add(int value) {
    root = addHelper(root, value);
}

// Helper function for Add - recursively finds the correct location and inserts the new node
Node* BinaryTree::addHelper(Node* node, int value) {
    if (!node) {
        return new Node(value);
    }

    if (value < node->data) {
        node->left = addHelper(node->left, value);   // Search left subtree
    } else if (value > node->data) {
        node->right = addHelper(node->right, value); // Search right subtree
    }
    return node;
}

// Remove a value from the BST
void BinaryTree::Remove(int value) {
    root = removeHelper(root, value);
}

// Helper function for Remove - recursively finds the node to delete and rebalances the tree
Node* BinaryTree::removeHelper(Node* node, int value) {
    if (!node) return nullptr; // Value not found

    if (value < node->data) {
        node->left = removeHelper(node->left, value);   // Search left subtree
    } else if (value > node->data) {
        node->right = removeHelper(node->right, value); // Search right subtree
    } else {
        // Node found
        if (!node->left) { // Case: No left child
            Node* temp = node->right;
            delete node;
            return temp;
        } else if (!node->right) { // Case: No right child
            Node* temp = node->left;
            delete node;
            return temp;
        }

        // Case: Two children
        // Replace with the inorder successor (smallest in the right subtree)
        if (node->left && node->right) {
            Node* temp = findMin(node->right); // Find the inorder successor
            node->data = temp->data;          // Replace current node's value
            node->right = removeHelper(node->right, temp->data); // Remove the successor
        }
    }

    return node; // Return the updated node
}

// Find the minimum value node
Node* BinaryTree::findMin(Node* node) {
    if (!node) return nullptr; // Safety check
    while (node && node->left) {  // Traverse to the leftmost node
        node = node->left;
    }
    return node;
}

// Find a value in the BST
bool BinaryTree::Find(int value) const {
    return findHelper(root, value) != nullptr;  // Returns true if the node exists
}

// Helper function for Find - recursively searches for the node with the given value
Node* BinaryTree::findHelper(Node* node, int value) const {
    if (!node || node->data == value) return node; // Node found or end of tree

    if (value < node->data) {
        return findHelper(node->left, value); // Search in left subtree
    }
    return findHelper(node->right, value); // Search in right subtree
}

// Find the maximum value in the BST
int BinaryTree::Maximum() const {
    if (!root) {
        std::cerr << "Maximum called on empty tree!" << std::endl;
        throw std::out_of_range("Tree is empty");
    }
    Node* current = root;
    while (current->right) {
        current = current->right;
    }
    return current->data;
}

// Perform an inorder traversal of the BST and prints the contents of the tree in ascending order
void BinaryTree::InorderTraverse() const {
    inorderTraverseHelper(root);
    std::cout << std::endl;
}

// Helper function for InorderTraverse - recursively traverses the tree in LNR (Left, Node, Right) order
void BinaryTree::inorderTraverseHelper(Node* node) const {
    if (node) {
        inorderTraverseHelper(node->left);  // Visit left subtree
        std::cout << node->data << " ";    // Visit current node
        inorderTraverseHelper(node->right); // Visit right subtree
    }
}

bool BinaryTree::isValidBST() const {
    return isValidBSTHelper(root, INT_MIN, INT_MAX);
}

bool BinaryTree::isValidBSTHelper(Node* node, int min, int max) const {
    if (!node) return true;
    if (node->data <= min || node->data >= max) return false;
    return isValidBSTHelper(node->left, min, node->data) &&
           isValidBSTHelper(node->right, node->data, max);
}