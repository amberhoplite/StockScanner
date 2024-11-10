#include <iostream>
#include <vector>
#include "functions.h"

int main() {
    int choice;
    std::vector<double> stockPrices;
    double threshold = 5.0; // Default threshold percentage
    size_t windowSize = 3;  // Default sliding window size


    // Main program loop for showing the menu and processing user input
    while (true) {
        StockScanner::showMenu(threshold, windowSize);
        if (!(std::cin >> choice)) {
        std::cout << "Invalid input. Please enter a number.\n";
        std::cin.clear(); // Clear the error flag
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore the invalid input
        continue;
    }
        if (choice == 1) {
            std::string ticker;
            std::cout << "Enter stock ticker: ";
            std::cin >> ticker;

            // Load stock data for the given ticker
            stockPrices = StockScanner::loadStockData(ticker);

            // Check if data was loaded successfully
            if (!stockPrices.empty()) {
                std::cout << "Stock data loaded successfully.\n\n";
            } else {
                std::cout << "Failed to load stock data.\n";
            }

        } else if (choice == 2) {
            // Check if stock data is available for averaging
            if (stockPrices.empty()) {
                std::cout << "No stock data available. Please load stock data first.\n";
            } else {
                // Calculate and display the average stock price
                double averagePrice = StockScanner::calculateAveragePrice(stockPrices);
                std::cout << "Average Stock Price: " << averagePrice << "\n\n";
            }
        }else if (choice == 3) {
            // Check threshold
            if (stockPrices.empty()) {
                std::cout << "No stock data available. Please load stock data first.\n";
            } else {
                bool result = StockScanner::checkThreshold(stockPrices, threshold);
                if (result) {
                    std::cout << "The price movement exceeds the threshold.\n";
                } else {
                    std::cout << "The price movement does not meet the threshold.\n";
                }
            }
        } else if (choice == 4) {
            // Modify threshold setting
            std::cout << "Enter new threshold percentage: ";
            std::cin >> threshold;
            std::cout << "Threshold updated to " << threshold << "%.\n";
        } else if (choice == 5) {
            // Apply sliding window
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
        } else if (choice == 6) {
            // Modify sliding window size
            std::cout << "Enter new sliding window size: ";
            std::cin >> windowSize;
            std::cout << "Sliding window size updated to " << windowSize << ".\n";
        } else if (choice == 7) {
            // Detect momentum
            if (stockPrices.empty()) {
                std::cout << "No stock data available. Please load stock data first.\n";
            } else {
                std::deque<double> pricesDeque(stockPrices.begin(), stockPrices.end());

                // Apply sliding window first
                std::deque<double> windowedPrices = StockScanner::applySlidingWindow(pricesDeque, windowSize);

                bool momentum = StockScanner::detectMomentum(windowedPrices);
                if (momentum) {
                    std::cout << "Positive momentum detected.\n\n";
                } else {
                    std::cout << "No positive momentum detected.\n\n";
                }
            }
        } else if (choice == 8) {
            std::cout << "Exiting program.\n";
            break;
        } else {
            std::cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}
