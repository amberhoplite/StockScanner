#pragma once

#include <vector>
#include <iostream>
#include <iomanip>
#include <chrono>
#include <stack>
#include <queue>
#include <deque>
#include <unordered_map>

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

// Generates unique random key-value pairs
std::vector<std::pair<int, std::string>> generateUniqueRandomKeyValuePairs(size_t count);

// Prints a performance table for hash table operations
void printHashTablePerformanceTable(const std::vector<double>& insertTimes, const std::vector<double>& retrieveTimes,
                                    const std::vector<double>& removeTimes, const std::string& label);

// Template function to measure performance of hash table operations
template <typename HashTable>
std::tuple<std::vector<double>, std::vector<double>, std::vector<double>> measureHashTablePerformance(
    HashTable& hashTable, const std::vector<std::pair<int, std::string>>& data) {
    std::vector<double> insertTimes, retrieveTimes, removeTimes;

    for (size_t count : {100, 1000, 10000}) {
        // Measure insertion time
        auto start = std::chrono::high_resolution_clock::now();
        for (size_t i = 0; i < count; ++i) {
            hashTable.insert(data[i].first, data[i].second);
        }
        auto end = std::chrono::high_resolution_clock::now();
        insertTimes.push_back(std::chrono::duration<double, std::milli>(end - start).count());

        // Measure retrieval time
        start = std::chrono::high_resolution_clock::now();
        for (size_t i = 0; i < count; ++i) {
            hashTable.retrieve(data[i].first);
        }
        end = std::chrono::high_resolution_clock::now();
        retrieveTimes.push_back(std::chrono::duration<double, std::milli>(end - start).count());

        // Measure removal time
        start = std::chrono::high_resolution_clock::now();
        for (size_t i = 0; i < count; ++i) {
            hashTable.remove(data[i].first);
        }
        end = std::chrono::high_resolution_clock::now();
        removeTimes.push_back(std::chrono::duration<double, std::milli>(end - start).count());
    }

    return {insertTimes, retrieveTimes, removeTimes};
}

// Overload for std::unordered_map
std::tuple<std::vector<double>, std::vector<double>, std::vector<double>> measureHashTablePerformance(
    std::unordered_map<int, std::string>& hashTable, const std::vector<std::pair<int, std::string>>& data);