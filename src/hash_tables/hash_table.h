#pragma once

#include <vector>
#include <list>
#include <functional>
#include <optional>
#include <stdexcept>

template <typename KeyType, typename ValueType>
class HashTable {
private:
    // A list of key-value pairs represents each bucket
    using Bucket = std::list<std::pair<KeyType, ValueType>>;

    std::vector<Bucket> table;    // The hash table storage
    size_t capacity;              // Total number of buckets
    size_t size;                  // Total number of elements
    float loadFactor;             // Load factor threshold for resizing

    // Hash function
    size_t hash(const KeyType& key) const {
        return std::hash<KeyType>{}(key) % capacity;
    }

    // Resizes the table when the load factor exceeds the threshold
    void resize() {
        size_t newCapacity = capacity * 2;
        std::vector<Bucket> newTable(newCapacity);

        for (const auto& bucket : table) {
            for (const auto& pair : bucket) {
                size_t newIndex = std::hash<KeyType>{}(pair.first) % newCapacity;
                newTable[newIndex].emplace_back(pair);
            }
        }

        table = std::move(newTable);
        capacity = newCapacity;
    }

public:
    // Constructor
    explicit HashTable(size_t initialCapacity = 16, float loadFactorThreshold = 0.75f)
        : capacity(initialCapacity), size(0), loadFactor(loadFactorThreshold) {
        table.resize(capacity);
    }

    // Insert a key-value pair
    void insert(const KeyType& key, const ValueType& value) {
        size_t index = hash(key);
        for (auto& pair : table[index]) {
            if (pair.first == key) {
                pair.second = value; // Update value if key already exists
                return;
            }
        }
        table[index].emplace_back(key, value);
        ++size;

        if (static_cast<float>(size) / capacity > loadFactor) {
            resize();
        }
    }

    // Retrieve a value by key
    std::optional<ValueType> retrieve(const KeyType& key) const {
        size_t index = hash(key);
        for (const auto& pair : table[index]) {
            if (pair.first == key) {
                return pair.second;
            }
        }
        return std::nullopt;
    }

    // Remove a key-value pair
    bool remove(const KeyType& key) {
        size_t index = hash(key);
        if (index >= table.size()) {
            std::cerr << "Error: Index " << index << " out of bounds for table size " << table.size() << "\n";
            throw std::out_of_range("Hash index out of bounds");
        }

        auto& bucket = table[index];
        for (auto it = bucket.begin(); it != bucket.end(); ++it) {
            if (it->first == key) {
                bucket.erase(it);
                --size;
                return true;
            }
        }
        return false; // Key not found
    }


    // Get the current size of the hash table
    size_t getSize() const {
        return size;
    }

    // Get the capacity of the hash table
    size_t getCapacity() const {
        return capacity;
    }
};