#include <gtest/gtest.h>
#include "../src/binary_tree/binary_tree.h"
#include <chrono>
#include <iostream>
#include <iomanip>
#include "test_helpers.h"

// Forward declare the helper function from StackQueueTests
std::vector<int> generateRandomNumbers(size_t count);

// Test suite for Binary Tree performance
TEST(BinaryTreePerformanceTests, AddPerformance) {
    BinaryTree bst;

    std::vector<size_t> testSizes = {100, 1000, 10000, 100000};
    std::vector<double> timings;

    for (size_t size : testSizes) {
        // Generate random numbers
        auto numbers = generateRandomNumbers(size);

        // Measure time to add numbers to the BST
        auto start = std::chrono::high_resolution_clock::now();
        for (int num : numbers) {
            bst.Add(num);
        }
        auto end = std::chrono::high_resolution_clock::now();
        double elapsed = std::chrono::duration<double, std::milli>(end - start).count();

        timings.push_back(elapsed);
    }

    // Print results in a table format
    std::cout << "┌──────────────┬──────────────┐\n";
    std::cout << "│ Nodes Added  │ Time (ms)    │\n";
    std::cout << "├──────────────┼──────────────┤\n";

    for (size_t i = 0; i < testSizes.size(); ++i) {
        std::cout << "│ " << std::setw(12) << testSizes[i]
                  << " │ " << std::setw(12) << std::fixed << std::setprecision(4) << timings[i]
                  << " │\n";
    }

    std::cout << "└──────────────┴──────────────┘\n";
}