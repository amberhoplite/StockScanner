#include "menu_actions.h"
#include "../core/functions.h"
#include "../sorting/sorting_analysis.h"
#include <iostream>
#include <deque>

namespace MenuActions {

    void showMenu(double threshold, size_t windowSize, int menuLevel) {
        if (menuLevel == 1) {
            std::cout << "Main Menu:\n";
            std::cout << "1. Stock Data Operations\n";
            std::cout << "2. Threshold and Window Settings\n";
            std::cout << "3. Sorting Analysis\n";
            std::cout << "4. Exit\n";
        } else if (menuLevel == 2) {
            std::cout << "Stock Data Operations:\n";
            std::cout << "1. Get Stock Ticker Data\n";
            std::cout << "2. Calculate Average Stock Price\n";
            std::cout << "3. Check Threshold\n";
            std::cout << "4. Back to Main Menu\n";
        } else if (menuLevel == 3) {
            std::cout << "Threshold and Window Settings:\n";
            std::cout << "1. Modify Threshold Setting (Current: " << threshold << "%)\n";
            std::cout << "2. Apply Sliding Window\n";
            std::cout << "3. Modify Sliding Window Size (Current: " << windowSize << ")\n";
            std::cout << "4. Detect Momentum\n";
            std::cout << "5. Back to Main Menu\n";
        } else if (menuLevel == 4) {
            std::cout << "Sorting Analysis:\n";
            std::cout << "1. Run Sorting Analysis (On Random data)\n";
            std::cout << "2. Back to Main Menu\n";
        }
        std::cout << "Select an option: ";
    }

    void getStockData(std::vector<double>& stockPrices, const std::string& timeframe) {
        std::string ticker;
        std::cout << "Enter stock ticker: ";
        std::cin >> ticker;
        stockPrices = StockScanner::loadStockData(ticker, timeframe);

        if (!stockPrices.empty()) {
            std::cout << "Stock data loaded successfully.\n\n";
        } else {
            std::cout << "Failed to load stock data.\n";
        }
    }

    void calculateAverage(const std::vector<double>& stockPrices) {
        if (stockPrices.empty()) {
            std::cout << "No stock data available. Please load stock data first.\n";
        } else {
            double averagePrice = StockScanner::calculateAveragePrice(stockPrices);
            std::cout << "Average Stock Price: " << averagePrice << "\n\n";
        }
    }

    void checkThreshold(const std::vector<double>& stockPrices, double threshold) {
        if (stockPrices.empty()) {
            std::cout << "No stock data available. Please load stock data first.\n";
        } else {
            bool result = StockScanner::checkThreshold(stockPrices, threshold);
            std::cout << (result ? "The price movement exceeds the threshold.\n" 
                                  : "The price movement does not meet the threshold.\n");
        }
    }

    void modifyThreshold(double& threshold) {
        std::cout << "Enter new threshold percentage: ";
        std::cin >> threshold;
        std::cout << "Threshold updated to " << threshold << "%.\n";
    }

    void applySlidingWindow(const std::vector<double>& stockPrices, size_t windowSize) {
        if (stockPrices.empty()) {
            std::cout << "No stock data available. Please load stock data first.\n";
        } else {
            std::deque<double> pricesDeque(stockPrices.begin(), stockPrices.end());
            std::deque<double> windowedPrices = StockScanner::applySlidingWindow(pricesDeque, windowSize);
            std::cout << "Sliding window applied (size " << windowSize << "). Windowed prices: ";
            for (double price : windowedPrices) {
                std::cout << price << " ";
            }
            std::cout << "\n";
        }
    }

    void modifyWindowSize(size_t& windowSize) {
        std::cout << "Enter new sliding window size: ";
        std::cin >> windowSize;
        std::cout << "Sliding window size updated to " << windowSize << ".\n";
    }

    void detectMomentum(const std::vector<double>& stockPrices, size_t windowSize) {
        if (stockPrices.empty()) {
            std::cout << "No stock data available. Please load stock data first.\n";
        } else {
            std::deque<double> pricesDeque(stockPrices.begin(), stockPrices.end());
            std::deque<double> windowedPrices = StockScanner::applySlidingWindow(pricesDeque, windowSize);

            bool momentum = StockScanner::detectMomentum(windowedPrices);
            std::cout << (momentum ? "Positive momentum detected.\n\n" 
                                   : "No positive momentum detected.\n\n");
        }
    }

    void changeTimeframe(std::string& timeframe) {
        std::cout << "Enter timeframe (options: 5min, 15min, daily, hourly): ";
        std::cin >> timeframe;
        if (StockScanner::timeframeMap.find(timeframe) == StockScanner::timeframeMap.end()) {
            std::cout << "Invalid timeframe. Setting to default ('daily').\n";
            timeframe = "daily";
        }
    }
}
