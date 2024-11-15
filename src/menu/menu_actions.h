#pragma once

#include <vector>
#include <string>
#include <deque>

namespace MenuActions {
    void showMenu(double threshold, size_t windowSize, int menuLevel = 1);
    void getStockData(std::vector<double>& stockPrices, const std::string& timeframe);
    void calculateAverage(const std::vector<double>& stockPrices);
    void checkThreshold(const std::vector<double>& stockPrices, double threshold);
    void modifyThreshold(double& threshold);
    void applySlidingWindow(const std::vector<double>& stockPrices, size_t windowSize);
    void modifyWindowSize(size_t& windowSize);
    void detectMomentum(const std::vector<double>& stockPrices, size_t windowSize);
    void changeTimeframe(std::string& timeframe);
}