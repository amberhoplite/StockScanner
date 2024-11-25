#include "sorting_analysis.h"
#include <algorithm>
#include <chrono>
#include <iostream>
#include <random>
#include <vector>
#include <iomanip> 
#include <cmath>
#include <fstream>

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

void countingSort(std::vector<double>& data) {
    if (data.empty()) return; // Handle empty vector

    // Find the range of the input data
    double minValue = *std::min_element(data.begin(), data.end());
    double maxValue = *std::max_element(data.begin(), data.end());

    // Scale data to integers if necessary (for future price integration)
    int scaleFactor = 100; // Multiplier for floating-point data to maintain precision
    std::vector<int> scaledData(data.size());
    for (size_t i = 0; i < data.size(); ++i) {
        scaledData[i] = static_cast<int>(std::floor((data[i] - minValue) * scaleFactor));
    }

    // Determine the range of scaled integers
    int scaledRange = static_cast<int>((maxValue - minValue) * scaleFactor) + 1;

    // Create a count array and initialize to 0
    std::vector<int> count(scaledRange, 0);

    // Count occurrences of each scaled integer
    for (int value : scaledData) {
        count[value]++;
    }

    // Overwrite the original data with sorted values
    size_t index = 0;
    for (int i = 0; i < scaledRange; ++i) {
        while (count[i] > 0) {
            data[index++] = minValue + static_cast<double>(i) / scaleFactor;
            count[i]--;
        }
    }
}

void measureSortingPerformance(const std::vector<double>& data, SortFunction sortFunction, const std::string& algorithmName, size_t dataSize, const std::string& timeUnit, double conversionFactor,std::ofstream& outFile) {

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

    // Write to CSV
    if (outFile.is_open()) {
        outFile << dataSize << "," << algorithmName << "," << displayTime << "\n";
    }
}

void runSortingAnalysis() {
    std::ofstream outFile("sorting_analysis_results.csv");

    // Write the CSV header
    if (outFile.is_open()) {
        outFile << "Data Size,Algorithm,Time Taken (microseconds)\n";
    } else {
        std::cerr << "Failed to open CSV file for writing. Results will not be saved.\n";
    }
    
    std::vector<size_t> dataSizes = {100, 1000, 10000, 100000};
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0.0, 100.0);

    for (size_t size : dataSizes) {
        // Generate random data
        std::vector<double> data(size);
        std::generate(data.begin(), data.end(), [&]() { return dis(gen); });

        // Use microseconds as timeUnit
        std::string timeUnit = "microseconds";
        double conversionFactor = 1e6; // Convert seconds to microseconds

        // Print a header to differentiate between different data sizes
        std::cout << "\nAnalyzing Sorting Performance for Data Size: " << size << "\n" << std::string(60, '-') << "\n";

        // Measure performance for each algorithm using consistent units for the current data size
        measureSortingPerformance(data, selectionSort, "SelectionSort", size, timeUnit, conversionFactor, outFile);
        measureSortingPerformance(data, [](std::vector<double>& d) { mergeSort(d, 0, d.size() - 1); }, "MergeSort", size, timeUnit, conversionFactor, outFile);
        measureSortingPerformance(data, heapSort, "HeapSort", size, timeUnit, conversionFactor, outFile);
        measureSortingPerformance(data, countingSort, "CountingSort", size, timeUnit, conversionFactor, outFile);
        measureSortingPerformance(data, [](std::vector<double>& d) { std::sort(d.begin(), d.end()); }, "std::sort", size, timeUnit, conversionFactor, outFile);
    }

    if (outFile.is_open()) {
        outFile.close();
        std::cout << "\nSorting analysis results saved to 'sorting_analysis_results.csv'.\n";
    }
}