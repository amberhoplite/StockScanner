#include "test_helpers.h"
#include <chrono>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <cstdlib>
#include <vector>
#include <algorithm>

#include "test_helpers.h"
#include "../src/linked_lists/stack_queue.h"
#include <stack>
#include <queue>
#include <unordered_set>
#include <unordered_map>

// Generates random integers
std::vector<int> generateRandomNumbers(size_t count) {
    std::vector<int> numbers(count);
    for (size_t i = 0; i < count; ++i) {
        numbers[i] = rand() % 100000; // Random numbers between 0 and 99,999
    }
    return numbers;
}

// Prints a performance table
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

// Checks if a vector is sorted
bool isSorted(const std::vector<double>& data) {
    return std::adjacent_find(data.begin(), data.end(), std::greater<double>()) == data.end();
}

// Generates unique random key-value pairs
std::vector<std::pair<int, std::string>> generateUniqueRandomKeyValuePairs(size_t count) {
    std::unordered_set<int> uniqueKeys;
    std::vector<std::pair<int, std::string>> data;

    while (data.size() < count) {
        int key = rand() % 100000; // Random keys
        if (uniqueKeys.insert(key).second) { // Only add if unique
            data.emplace_back(key, "Value" + std::to_string(key));
        }
    }
    return data;
}

// Prints a performance table for hash table operations
void printHashTablePerformanceTable(const std::vector<double>& insertTimes, const std::vector<double>& retrieveTimes,
                                    const std::vector<double>& removeTimes, const std::string& label) {
    const int colWidth = 10;

    auto formatValue = [](double value) {
        std::ostringstream oss;
        oss << std::fixed << std::setprecision(4) << value;
        return oss.str();
    };

    std::cout << "Performance for: " << label << "\n";
    std::cout << "┌────────────┬───────────┬───────────┬───────────┐\n";
    std::cout << "│ Operation  │ 100       │ 1000      │ 10000     │\n";
    std::cout << "├────────────┼───────────┼───────────┼───────────┤\n";

    std::cout << "│ Insert     │"
              << std::setw(colWidth) << formatValue(insertTimes[0])
              << " │" << std::setw(colWidth) << formatValue(insertTimes[1])
              << " │" << std::setw(colWidth) << formatValue(insertTimes[2]) << " │\n";

    std::cout << "│ Retrieve   │"
              << std::setw(colWidth) << formatValue(retrieveTimes[0])
              << " │" << std::setw(colWidth) << formatValue(retrieveTimes[1])
              << " │" << std::setw(colWidth) << formatValue(retrieveTimes[2]) << " │\n";

    std::cout << "│ Remove     │"
              << std::setw(colWidth) << formatValue(removeTimes[0])
              << " │" << std::setw(colWidth) << formatValue(removeTimes[1])
              << " │" << std::setw(colWidth) << formatValue(removeTimes[2]) << " │\n";

    std::cout << "└────────────┴───────────┴───────────┴───────────┘\n";
}

// Overload for STL containers like std::unordered_map
std::tuple<std::vector<double>, std::vector<double>, std::vector<double>> measureHashTablePerformance(
    std::unordered_map<int, std::string>& hashTable, const std::vector<std::pair<int, std::string>>& data) {
    
    std::vector<double> insertTimes, retrieveTimes, removeTimes;

    for (size_t count : {100, 1000, 10000}) {
        size_t datasetSize = std::min(count, data.size()); // Ensure we don't exceed the available data size
        
        // Measure insertion time
        auto start = std::chrono::high_resolution_clock::now();
        for (size_t i = 0; i < std::min(count, data.size()); ++i) {
            hashTable[data[i].first] = data[i].second; // Insert or update
        }
        auto end = std::chrono::high_resolution_clock::now();
        insertTimes.push_back(std::chrono::duration<double, std::milli>(end - start).count());

        // Measure retrieval time
        start = std::chrono::high_resolution_clock::now();
        for (size_t i = 0; i < datasetSize; ++i) {
            auto it = hashTable.find(data[i].first);
            if (it == hashTable.end()) {
                std::cerr << "Key not found during retrieval: " << data[i].first << "\n";
            }
        }
        end = std::chrono::high_resolution_clock::now();
        retrieveTimes.push_back(std::chrono::duration<double, std::milli>(end - start).count());

        // Measure removal time
        start = std::chrono::high_resolution_clock::now();
        for (size_t i = 0; i < datasetSize; ++i) {
            if (hashTable.erase(data[i].first) != 1) {
                std::cerr << "Failed to remove key: " << data[i].first << "\n";
            }
        }
        end = std::chrono::high_resolution_clock::now();
        removeTimes.push_back(std::chrono::duration<double, std::milli>(end - start).count());
    }

    return {insertTimes, retrieveTimes, removeTimes};
}