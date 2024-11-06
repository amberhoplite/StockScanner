#pragma once

#include <vector>
#include <string>

// Displays a simple menu to the user
void showMenu();

// Loads stock data for a given ticker symbol. This function fetches stock data from the AlphaVantage API 
// if available, or returns mock data for testing when UNIT_TESTING is defined.
std::vector<double> loadStockData(const std::string& ticker);

// Calculates the average price from a vector of prices
double calculateAveragePrice(const std::vector<double>& prices);
