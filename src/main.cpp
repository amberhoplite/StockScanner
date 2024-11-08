#include <iostream>
#include <vector>
#include "functions.h"

int main() {
    int choice;
    std::vector<double> stockPrices;


    // Main program loop for showing the menu and processing user input
    while (true) {
        StockScanner::showMenu();
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
        } else if (choice == 3) {
            std::cout << "Exiting program.\n";
            break;
        } else {
            std::cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}
