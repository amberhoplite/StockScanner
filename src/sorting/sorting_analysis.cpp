#include "sorting_analysis.h"
#include <algorithm>
#include <chrono>
#include <iostream>
#include <random>
#include <vector>
#include <iomanip> 

void selectionSort(std::vector<double>& data) {
    size_t n = data.size();
    if (n == 0) return; // Handle empty vectors

    for (size_t i = 0; i < n - 1; ++i) {
        size_t minIndex = i;
        for (size_t j = i + 1; j < n; ++j) {
            if (data[j] < data[minIndex]) {
                minIndex = j;
            }
        }
        std::swap(data[i], data[minIndex]);
    }
}

void merge(std::vector<double>& data, size_t left, size_t mid, size_t right) {
    // Guard against out-of-bounds access by checking vector size
    if (left >= data.size() || mid >= data.size() || right >= data.size()) return;

    size_t n1 = mid - left + 1;
    size_t n2 = right - mid;

    std::vector<double> L(n1), R(n2);

    for (size_t i = 0; i < n1; ++i) {
        L[i] = data[left + i];
    }
    for (size_t j = 0; j < n2; ++j) {
        R[j] = data[mid + 1 + j];
    }

    size_t i = 0, j = 0, k = left;

    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            data[k] = L[i];
            i++;
        } else {
            data[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        data[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        data[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(std::vector<double>& arr, size_t left, size_t right) {
    if (arr.empty() || left >= right) return;  // Check for empty array to prevent unintended recursion

    size_t mid = left + (right - left) / 2;
    mergeSort(arr, left, mid);
    mergeSort(arr, mid + 1, right);
    merge(arr, left, mid, right);
}

void heapify(std::vector<double>& data, size_t n, size_t i) {
    size_t largest = i; // Initialize largest as root
    size_t left = 2 * i + 1;
    size_t right = 2 * i + 2;

    if (left < n && data[left] > data[largest]) {
        largest = left;
    }

    if (right < n && data[right] > data[largest]) {
        largest = right;
    }

    if (largest != i) {
        std::swap(data[i], data[largest]);
        heapify(data, n, largest);
    }
}

void heapSort(std::vector<double>& data) {
    size_t n = data.size();

    // Return immediately if empty or has only one element
    if (n <= 1) return;

    // Build heap (rearrange array)
    for (size_t i = n / 2; i > 0; i--) {
        heapify(data, n, i - 1);
    }

    // Extract elements from heap one by one
    for (size_t i = n - 1; i > 0; i--) {
        std::swap(data[0], data[i]);
        heapify(data, i, 0);
    }
}


void measureSortingPerformance(const std::vector<double>& data, SortFunction sortFunction, const std::string& algorithmName, size_t dataSize, const std::string& timeUnit, double conversionFactor) {
    std::vector<double> dataCopy = data;
    auto start = std::chrono::high_resolution_clock::now();

    sortFunction(dataCopy);

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;

    double displayTime = elapsed.count() * conversionFactor;

    // Print the results with data size information in a consistent format
    std::cout << std::setw(12) << dataSize
              << " | " << std::setw(15) << algorithmName
              << " | Time Taken: " << std::fixed << std::setprecision(3)
              << std::setw(10) << displayTime << " " << timeUnit << std::endl;
}

void runSortingAnalysis() {
    std::vector<size_t> dataSizes = {100, 1000, 10000, 100000};
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0.0, 100.0);

    for (size_t size : dataSizes) {
        // Generate random data
        std::vector<double> data(size);
        std::generate(data.begin(), data.end(), [&]() { return dis(gen); });

        // Determine the time unit to use based on the data size
        std::string timeUnit;
        double conversionFactor; // Factor to convert seconds to the desired unit

        auto start = std::chrono::high_resolution_clock::now();
        selectionSort(data);
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed = end - start;

        if (elapsed.count() < 0.001) {
            timeUnit = "microseconds";
            conversionFactor = 1e6;  // Convert seconds to microseconds
        } else if (elapsed.count() < 1.0) {
            timeUnit = "milliseconds";
            conversionFactor = 1e3;  // Convert seconds to milliseconds
        } else {
            timeUnit = "seconds";
            conversionFactor = 1.0;  // Keep as seconds
        }

        // Print a header to differentiate between different data sizes
        std::cout << "\nAnalyzing Sorting Performance for Data Size: " << size << "\n" << std::string(60, '-') << "\n";

        // Measure performance for each algorithm using consistent units for the current data size
        measureSortingPerformance(data, selectionSort, "SelectionSort", size, timeUnit, conversionFactor);
        measureSortingPerformance(data, [](std::vector<double>& d) { mergeSort(d, 0, d.size() - 1); }, "MergeSort", size, timeUnit, conversionFactor);
        measureSortingPerformance(data, heapSort, "HeapSort", size, timeUnit, conversionFactor);
        measureSortingPerformance(data, [](std::vector<double>& d) { std::sort(d.begin(), d.end()); }, "std::sort", size, timeUnit, conversionFactor);
    }
}