#pragma once

#include <vector>
#include <optional>
#include <stdexcept>

template <typename KeyType, typename ValueType>
class OpenAddressingHashTable {
private:
    // Structure to represent a key-value pair and its state
    struct Entry {
        KeyType key;
        ValueType value;
        bool isOccupied;    // Indicates if this slot is currently occupied
        bool isDeleted;     // Indicates if this slot has been deleted
    };

    std::vector<std::optional<Entry>> table; // Hash table storage
    size_t capacity;                         // Total slots in the hash table
    size_t size;                             // Current number of elements
    float loadFactor;                        // Load factor threshold for resizing

    // Hash function
    size_t hash(const KeyType& key, size_t attempt = 0) const {
        if (capacity == 0) {
            throw std::logic_error("Hash table capacity is zero");
        }
        return (std::hash<KeyType>{}(key) + attempt) % capacity;
    }

    // Resize the hash table when the load factor is exceeded
    void resize() {
        size_t newCapacity = capacity * 2;
        std::vector<std::optional<Entry>> newTable(newCapacity);

        for (const auto& entry : table) {
            if (entry && entry->isOccupied && !entry->isDeleted) {
                size_t attempt = 0;
                size_t newIndex;
                do {
                    newIndex = (std::hash<KeyType>{}(entry->key) + attempt) % newCapacity;
                    ++attempt;
                } while (newTable[newIndex]);

                newTable[newIndex] = entry;
            }
        }

        table = std::move(newTable);
        capacity = newCapacity;
    }


public:
    // Constructor
    explicit OpenAddressingHashTable(size_t initialCapacity = 16, float loadFactorThreshold = 0.75f)
        : capacity(initialCapacity), size(0), loadFactor(loadFactorThreshold) {
        table.resize(capacity);
    }

    // Insert a key-value pair
    void insert(const KeyType& key, const ValueType& value) {
        if (static_cast<float>(size) / capacity > loadFactor) {
            resize();
        }

        size_t attempt = 0;
        size_t index;

        do {
            index = hash(key, attempt++);
            if (!table[index] || table[index]->isDeleted) {
                table[index] = Entry{key, value, true, false};
                ++size;
                return;
            } else if (table[index]->key == key) {
                table[index]->value = value; // Update value if key exists
                return;
            }
        } while (attempt < capacity);

        throw std::runtime_error("Hash table is full");
    }

    // Retrieve a value by key
    std::optional<ValueType> retrieve(const KeyType& key) const {
        size_t attempt = 0;
        size_t index;

        do {
            index = hash(key, attempt++);
            if (!table[index]) {
                return std::nullopt; // Key not found
            } else if (table[index]->isOccupied && !table[index]->isDeleted && table[index]->key == key) {
                return table[index]->value;
            }
        } while (attempt < capacity);

        return std::nullopt; // Key not found
    }

    // Remove a key-value pair
    bool remove(const KeyType& key) {
        size_t attempt = 0;
        size_t index;

        do {
            index = hash(key, attempt++);
            if (!table[index]) {
                return false; // Key not found
            } else if (table[index]->isOccupied && !table[index]->isDeleted && table[index]->key == key) {
                table[index]->isDeleted = true;
                table[index]->isOccupied = false; // Mark slot as no longer occupied
                --size;
                return true;
            }
        } while (attempt < capacity);

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