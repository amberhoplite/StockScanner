#pragma once
#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <vector>
#include <string>

void showMenu();

std::vector<double> loadStockData(const std::string& ticker);

double calculateAveragePrice(const std::vector<double>& prices);

bool checkThreshold(const std::vector<double>& prices, double threshold);

#endif