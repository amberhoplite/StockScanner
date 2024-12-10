#include <gtest/gtest.h>
#include "../src/linked_lists/stack_queue.h"
#include "test_helpers.h" 
#include <vector>
#include <iostream>
#include <iomanip>
#include <stack>
#include <queue>

// Test suite for Stack
TEST(StackTests, BasicOperations) {
    Stack stack;

    // Test insertion and size
    stack.Insert(10);
    stack.Insert(20);
    stack.Insert(30);
    EXPECT_EQ(stack.getSize(), 3);

    // Test print
    std::ostringstream output;
    std::streambuf* oldCoutBuffer = std::cout.rdbuf(output.rdbuf());
    stack.Print();
    std::cout.rdbuf(oldCoutBuffer); // Reset cout to its original buffer

    EXPECT_EQ(output.str(), "Stack (top to bottom): 30 20 10 \n");

    // Test removal
    EXPECT_EQ(stack.Remove(), 30);
    EXPECT_EQ(stack.Remove(), 20);
    EXPECT_EQ(stack.Remove(), 10);
    EXPECT_EQ(stack.getSize(), 0);

    // Test underflow
    EXPECT_THROW(stack.Remove(), std::out_of_range);
}

// Test suite for Queue
TEST(QueueTests, BasicOperations) {
    Queue queue;

    // Test insertion and size
    queue.Insert(10);
    queue.Insert(20);
    queue.Insert(30);
    EXPECT_EQ(queue.getSize(), 3);

    // Test print
    std::ostringstream output;
    std::streambuf* oldCoutBuffer = std::cout.rdbuf(output.rdbuf());
    queue.Print();
    std::cout.rdbuf(oldCoutBuffer); // Reset cout to its original buffer

    EXPECT_EQ(output.str(), "Queue (front to rear): 10 20 30 \n");

    // Test removal
    EXPECT_EQ(queue.Remove(), 10);
    EXPECT_EQ(queue.Remove(), 20);
    EXPECT_EQ(queue.Remove(), 30);
    EXPECT_EQ(queue.getSize(), 0);

    // Test underflow
    EXPECT_THROW(queue.Remove(), std::out_of_range);
}

// Test Suite for Performance Tests
TEST(PerformanceTests, StackAndQueuePerformance) {
    auto data = generateRandomNumbers(10000);

    // Measure performance for Stack
    auto [stackInsertTimes, stackDeleteTimes] = measurePerformance<Stack>(data);

    // Measure performance for Queue
    auto [queueInsertTimes, queueDeleteTimes] = measurePerformance<Queue>(data);

    // Print results in the table
    printPerformanceTable(stackInsertTimes, stackDeleteTimes, queueInsertTimes, queueDeleteTimes);
}

TEST(PerformanceTests, StackAndQueuePerformanceWithSTL) {
    auto data = generateRandomNumbers(10000);

    // Measure performance for custom Stack
    auto [stackInsertTimes, stackDeleteTimes] = measurePerformance<Stack>(data);

    // Measure performance for STL stack
    auto [stlStackInsertTimes, stlStackDeleteTimes] = measureSTLPerformance<std::stack<int>>(data);

    // Measure performance for custom Queue
    auto [queueInsertTimes, queueDeleteTimes] = measurePerformance<Queue>(data);

    // Measure performance for STL queue
    auto [stlQueueInsertTimes, stlQueueDeleteTimes] = measureSTLPerformance<std::queue<int>>(data);

    // Print results
    std::cout << "\nSTL Performance (ms):\n";
    printPerformanceTable(stlStackInsertTimes, stlStackDeleteTimes, stlQueueInsertTimes, stlQueueDeleteTimes);
}