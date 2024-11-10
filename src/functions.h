#pragma once

#include <vector>
#include <string>
#include <deque>

namespace StockScanner {
    void showMenu(double threshold, size_t windowSize);

    std::vector<double> loadStockData(const std::string& ticker);

    double calculateAveragePrice(const std::vector<double>& prices);

    bool checkThreshold(const std::vector<double>& prices, double threshold);

    std::deque<double> applySlidingWindow(const std::deque<double>& prices, size_t windowSize);

    bool detectMomentum(const std::deque<double>& prices, size_t index = 0, int trendCount = 0);
}