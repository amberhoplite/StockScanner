#include <gtest/gtest.h>
#include <unordered_map>
#include "test_helpers.h"
#include "../src/hash_tables/hash_table.h" // Phase 1 Hash Table
#include "../src/hash_tables/open_addressing_hash_table.h" // Phase 2 Hash Table

// Test Phase 1: Chaining
TEST(HashTablePerformanceTests, Phase1ChainingPerformance) {
    HashTable<int, std::string> hashTable;
    auto data = generateUniqueRandomKeyValuePairs(10000); // Use appropriate dataset

    auto [insertTimes, retrieveTimes, removeTimes] = measureHashTablePerformance(hashTable, data);

    std::cout << "\nPerformance Results for Phase 1 Hash Table (Chaining):\n";
    printHashTablePerformanceTable(insertTimes, retrieveTimes, removeTimes, "Phase 1 Hash Table (Chaining)");
}


// Test Phase 2: Open Addressing
TEST(HashTablePerformanceTests, Phase2OpenAddressingPerformance) {
    OpenAddressingHashTable<int, std::string> hashTable;
    auto data = generateUniqueRandomKeyValuePairs(10000); // Use appropriate dataset

    auto [insertTimes, retrieveTimes, removeTimes] = measureHashTablePerformance(hashTable, data);

    std::cout << "\nPerformance Results for Phase 2 Hash Table (Open Addressing):\n";
    printHashTablePerformanceTable(insertTimes, retrieveTimes, removeTimes, "Phase 2 Hash Table (Open Addressing)");
}


// Test Built-in Hash Table
TEST(HashTablePerformanceTests, BuiltInHashTablePerformance) {
    std::unordered_map<int, std::string> hashTable;
    auto data = generateUniqueRandomKeyValuePairs(10000); // Use appropriate dataset

    auto [insertTimes, retrieveTimes, removeTimes] = measureHashTablePerformance(hashTable, data);

    std::cout << "\nPerformance Results for Built-in Hash Table:\n";
    printHashTablePerformanceTable(insertTimes, retrieveTimes, removeTimes, "Built-in Hash Table");
}

