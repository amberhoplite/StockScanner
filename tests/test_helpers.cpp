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
