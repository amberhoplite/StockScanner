#pragma once

#include <vector>
#include <iostream>
#include <iomanip>
#include <chrono>
#include <stack>
#include <queue>
#include <deque>

// Generates random integers
std::vector<int> generateRandomNumbers(size_t count);

// Prints a performance table
void printPerformanceTable(const std::vector<double>& stackInsert, const std::vector<double>& stackDelete,
                           const std::vector<double>& queueInsert, const std::vector<double>& queueDelete);

// Checks if a vector is sorted
bool isSorted(const std::vector<double>& data);

// Template function to measure performance of custom data structures
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

// Template function to measure performance of STL containers
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