#pragma once

#include <sqlite3.h>
#include <vector>
#include <string>

namespace StockScanner {
    // Function to initialize the database
    bool initializeDatabase();

    // Function to insert stock data into the database
    bool insertStockData(const std::string& ticker, const std::vector<std::pair<std::string, double>>& data);

    // Function to check if stock data for a specific ticker already exists
    bool checkStockDataExists(const std::string& ticker);

    // Function to load stock data if it exists in database
    std::vector<double> getStockDataFromDatabase(const std::string& ticker);

    // Closes the database connection
    void closeDatabase();
}
