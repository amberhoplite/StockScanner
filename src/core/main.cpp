#include <iostream>
#include <vector>
#include "functions.h"
#include "../database/database_utils.h"
#include "../sorting/sorting_analysis.h"
#include "../menu/menu_actions.h"

int main() {
    int choice;
    int menuLevel = 1;
    std::vector<double> stockPrices;
    std::string timeframe = "daily";    // Default timeframe
    double threshold = 5.0;             // Default threshold percentage
    size_t windowSize = 3;              // Default sliding window size

    // Initialize the Database to store stock prices
    if (!StockScanner::initializeDatabase()) {
        std::cerr << "Failed to initialize the database. Exiting.\n";
        return 1;
    }

    // Main program loop for showing the menu and processing user input
    while (true) {
        MenuActions::showMenu(threshold, windowSize, menuLevel);

        if (!(std::cin >> choice)) {
            std::cout << "Invalid input. Please enter a number.\n";
            std::cin.clear(); // Clear the error flag
            std::cin.ignore(
                std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore the invalid input
            continue;
        }

        if (menuLevel == 1) {
            if (choice == 1) menuLevel = 2;
            else if (choice == 2) menuLevel = 3;
            else if (choice == 3) menuLevel = 4;
            else if (choice == 4) {
                std::cout << "Exiting program.\n";
                break;
            }
        } else if (menuLevel == 2) {
            if (choice == 1) MenuActions::getStockData(stockPrices, timeframe);
            else if (choice == 2) MenuActions::calculateAverage(stockPrices);
            else if (choice == 3) MenuActions::checkThreshold(stockPrices, threshold);
            else if (choice == 4) menuLevel = 1;
        } else if (menuLevel == 3) {
            if (choice == 1) MenuActions::modifyThreshold(threshold);
            else if (choice == 2) MenuActions::applySlidingWindow(stockPrices, windowSize);
            else if (choice == 3) MenuActions::modifyWindowSize(windowSize);
            else if (choice == 4) MenuActions::detectMomentum(stockPrices, windowSize);
            else if (choice == 5) menuLevel = 1;
        } else if (menuLevel == 4) {
            if (choice == 1) runSortingAnalysis();
            else if (choice == 2) menuLevel = 1;
        }
    }

    StockScanner::closeDatabase();
    return 0;
}
