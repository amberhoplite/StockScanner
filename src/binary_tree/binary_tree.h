#pragma once

#include <iostream>
#include <optional>

class Node {
public:
    int data;
    Node* left;
    Node* right;

    Node(int value) : data(value), left(nullptr), right(nullptr) {}
};

class BinaryTree {
private:
    Node* root;

    // Helper functions
    Node* addHelper(Node* node, int value);
    Node* removeHelper(Node* node, int value);
    Node* findMin(Node* node);
    Node* findHelper(Node* node, int value) const;
    void inorderTraverseHelper(Node* node) const;
    bool isValidBSTHelper(Node* node, int min, int max) const;

public:
    // Constructor and Destructor
    BinaryTree();
    ~BinaryTree();
    void clear(Node* node);

    // Functions
    void Add(int value);
    void Remove(int value);
    int Maximum() const;
    bool Find(int value) const;
    void InorderTraverse() const;
    bool isValidBST() const;
};
