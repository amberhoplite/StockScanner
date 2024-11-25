#include <gtest/gtest.h>
#include "../src/linked_lists/stack_queue.h"
#include <chrono>
#include <vector>
#include <cstdlib>

#include <iostream>
#include <iomanip>

#include <stack>
#include <queue>


// Helper function to generate random integers
std::vector<int> generateRandomNumbers(size_t count) {
    std::vector<int> numbers(count);
    for (size_t i = 0; i < count; ++i) {
        numbers[i] = rand() % 10000; // Generate random numbers between 0 and 9999
    }
    return numbers;
}

// Helper function to measure the performance of insertion and deletion
template <typename DataStructure>
std::pair<std::vector<double>, std::vector<double>> measurePerformance(const std::vector<int>& data) {
    DataStructure ds;
    std::vector<double> insertTimes;
    std::vector<double> deleteTimes;

    for (size_t count : {100, 1000, 10000}) {
        // Measure insertion time
        auto start = std::chrono::high_resolution_clock::now();
        for (size_t i = 0; i < count; ++i) {
            ds.Insert(data[i]);
        }
        auto end = std::chrono::high_resolution_clock::now();
        insertTimes.push_back(std::chrono::duration<double, std::milli>(end - start).count());

        // Measure deletion time
        start = std::chrono::high_resolution_clock::now();
        for (size_t i = 0; i < count; ++i) {
            ds.Remove();
        }
        end = std::chrono::high_resolution_clock::now();
        deleteTimes.push_back(std::chrono::duration<double, std::milli>(end - start).count());
    }

    return {insertTimes, deleteTimes};
}

// Helper function to measure the performance of STL linked-list, stack, queue
template <typename STLContainer>
std::pair<std::vector<double>, std::vector<double>> measureSTLPerformance(const std::vector<int>& data) {
    STLContainer container;
    std::vector<double> insertTimes;
    std::vector<double> deleteTimes;

    for (size_t count : {100, 1000, 10000}) {
        // Measure insertion time
        auto start = std::chrono::high_resolution_clock::now();
        for (size_t i = 0; i < count; ++i) {
            container.push(data[i]); // `push` for stack and queue
        }
        auto end = std::chrono::high_resolution_clock::now();
        insertTimes.push_back(std::chrono::duration<double, std::milli>(end - start).count());

        // Measure deletion time
        start = std::chrono::high_resolution_clock::now();
        for (size_t i = 0; i < count; ++i) {
            container.pop(); // `pop` for stack and queue
        }
        end = std::chrono::high_resolution_clock::now();
        deleteTimes.push_back(std::chrono::duration<double, std::milli>(end - start).count());
    }

    return {insertTimes, deleteTimes};
}

// Helper function to print the table
void printPerformanceTable(const std::vector<double>& stackInsert, const std::vector<double>& stackDelete,
                           const std::vector<double>& queueInsert, const std::vector<double>& queueDelete) {
    const int colWidth = 10;

    auto formatValue = [](double value) {
        std::ostringstream oss;
        oss << std::fixed << std::setprecision(4) << value;
        return oss.str();
    };

    std::cout << "┌───────────────┬───────────────────────────────────┬───────────────────────────────────┐\n";
    std::cout << "│               │ Insert(ms)                        │ Delete(ms)                        │\n";
    std::cout << "├───────────────┼───────────┬───────────┬───────────┼───────────┬───────────┬───────────┤\n";
    std::cout << "│ Datastructure │ 100       │ 1000      │ 10000     │ 100       │ 1000      │ 10000     │\n";
    std::cout << "├───────────────┼───────────┼───────────┼───────────┼───────────┼───────────┼───────────┤\n";

    // Print stack results
    std::cout << "│ Stack         │"
              << std::setw(colWidth) << formatValue(stackInsert[0])
              << " │" << std::setw(colWidth) << formatValue(stackInsert[1])
              << " │" << std::setw(colWidth) << formatValue(stackInsert[2])
              << " │" << std::setw(colWidth) << formatValue(stackDelete[0])
              << " │" << std::setw(colWidth) << formatValue(stackDelete[1])
              << " │" << std::setw(colWidth) << formatValue(stackDelete[2]) << " │\n";

    // Print queue results
    std::cout << "│ Queue         │"
              << std::setw(colWidth) << formatValue(queueInsert[0])
              << " │" << std::setw(colWidth) << formatValue(queueInsert[1])
              << " │" << std::setw(colWidth) << formatValue(queueInsert[2])
              << " │" << std::setw(colWidth) << formatValue(queueDelete[0])
              << " │" << std::setw(colWidth) << formatValue(queueDelete[1])
              << " │" << std::setw(colWidth) << formatValue(queueDelete[2]) << " │\n";

    std::cout << "└───────────────┴───────────┴───────────┴───────────┴───────────┴───────────┴───────────┘\n";
}

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