#pragma once
#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <vector>
#include <string>
#include <deque>

void showMenu();

std::vector<double> loadStockData(const std::string& ticker);

double calculateAveragePrice(const std::vector<double>& prices);

bool checkThreshold(const std::vector<double>& prices, double threshold);

std::deque<double> applySlidingWindow(const std::deque<double>& prices, size_t windowSize);

#endif