#include "stack_queue.h"
#include <iostream>

// Constructor
Stack::Stack() : top(nullptr), size(0) {}

// Destructor
Stack::~Stack() {
    while (top) {
        Node* temp = top;
        top = top->prev; // Move to the previous node
        delete temp;     // Free the current node
    }
}

// Insert a value onto the stack
void Stack::Insert(int value) {
    Node* newNode = new Node(value);
    newNode->prev = top;  // Link the new node to the current top
    top = newNode;        // Update the top pointer
    ++size;
}

// Remove and return the value from the top
int Stack::Remove() {
    if (!top) {
        throw std::out_of_range("Stack is empty. Cannot remove.");
    }
    int value = top->data; // Retrieve the value from the top
    Node* temp = top;      // Store the current top
    top = top->prev;       // Move the top pointer to the previous node
    delete temp;           // Delete the old top node
    --size;
    return value;
}

// Print the stack from top to bottom
void Stack::Print() const {
    Node* current = top;
    std::cout << "Stack (top to bottom): ";
    while (current) {
        std::cout << current->data << " ";
        current = current->prev;
    }
    std::cout << std::endl;
}



// Constructor
Queue::Queue() : front(nullptr), rear(nullptr), size(0) {}

// Destructor
Queue::~Queue() {
    while (front) {
        Node* temp = front;
        front = front->next; // Move to the next node
        delete temp;         // Free the current node
    }
}

// Insert a value at the rear of the queue
void Queue::Insert(int value) {
    Node* newNode = new Node(value);
    if (!rear) {                    // If the queue is empty
        front = rear = newNode;     // Front and rear point to the new node
    } else {
        rear->next = newNode;       // Link the new node to the rear
        newNode->prev = rear;       // Update the prev pointer of the new node
        rear = newNode;             // Update the rear pointer
    }
    ++size;
}

// Remove and return the value at the front of the queue
int Queue::Remove() {
    if (!front) {
        throw std::out_of_range("Queue is empty. Cannot remove.");
    }
    int value = front->data;   // Retrieve the value from the front
    Node* temp = front;        // Store the current front
    front = front->next;       // Move the front pointer to the next node
    if (front) {
        front->prev = nullptr; // Reset the previous pointer of the new front
    } else {
        rear = nullptr;        // If the queue becomes empty, reset the rear pointer
    }
    delete temp;
    --size;
    return value;
}

// Print the queue from front to rear
void Queue::Print() const {
    Node* current = front;
    std::cout << "Queue (front to rear): ";
    while (current) {
        std::cout << current->data << " ";
        current = current->next;
    }
    std::cout << std::endl;
}