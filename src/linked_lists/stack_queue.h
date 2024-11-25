#pragma once

#include <iostream>

// Node structure for the doubly-linked list
class Node {
public:
    int data;
    Node* next;
    Node* prev;

    // Constructor to initialize a node with a value
    explicit Node(int value) : data(value), next(nullptr), prev(nullptr) {}
};

// Stack class using a doubly-linked list
class Stack {
private:
    Node* top;
    int size;

public:
    // Constructor: initializes an empty stack
    Stack();

    // Destructor: cleans up dynamically allocated memory
    ~Stack();

    void Insert(int value);
    int Remove();

    // Prints the stack from top to bottom
    void Print() const;

    // Returns the current size of the stack
    int getSize() const noexcept { return size; }
};

// Queue class using a doubly-linked list
class Queue {
private:
    Node* front;
    Node* rear;
    int size;

public:
    // Constructor: initializes an empty queue
    Queue();

    // Destructor: cleans up dynamically allocated memory
    ~Queue();

    void Insert(int value);
    int Remove();

    // Prints the queue from front to rear
    void Print() const;

    // Returns the current size of the queue
    int getSize() const { return size; }
};
