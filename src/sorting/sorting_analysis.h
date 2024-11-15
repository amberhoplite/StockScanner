#pragma once

#include <vector>
#include <string>

using SortFunction = void(*)(std::vector<double>&);

// Function prototypes for different sorting algorithms
void selectionSort(std::vector<double>& data);
void mergeSort(std::vector<double>& arr, size_t left, size_t right);
void heapSort(std::vector<double>& data);

void measureSortingPerformance(const std::vector<double>& data, SortFunction sortFunction, const std::string& algorithmName);
void runSortingAnalysis();

// Helper functions
void merge(std::vector<double>& data, size_t left, size_t mid, size_t right);
void heapify(std::vector<double>& data, size_t n, size_t i);