#pragma once

#include <vector>
#include <string>
#include <deque>
#include <sqlite3.h>
#include <unordered_map> 

namespace StockScanner {
    void showMenu(double threshold, size_t windowSize);

    std::vector<double> loadStockData(const std::string& ticker, const std::string& timeframe);

    double calculateAveragePrice(const std::vector<double>& prices);

    bool checkThreshold(const std::vector<double>& prices, double threshold);

    std::deque<double> applySlidingWindow(const std::deque<double>& prices, size_t windowSize);

    bool detectMomentum(const std::deque<double>& prices, size_t index = 0, int trendCount = 0);

    struct TimeframeInfo {
        std::string apiFunction;
        std::string jsonKey;
    };
    
    extern const std::unordered_map<std::string, TimeframeInfo> timeframeMap;
}