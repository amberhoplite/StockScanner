#include "database_utils.h"
#include <iostream>
#include <sstream>

namespace StockScanner {

    static const char* DATABASE_NAME = "stock_data.db";
    sqlite3* db = nullptr;

    // Initialize the SQLite database (create tables if they don't exist)
    bool initializeDatabase() {
        int rc = sqlite3_open(DATABASE_NAME, &db);
        if (rc) {
            std::cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
            return false;
        }

        // Create a table for storing stock data if it doesn't already exist
        const char* createTableSQL = R"(
            CREATE TABLE IF NOT EXISTS stock_data (
                id INTEGER PRIMARY KEY AUTOINCREMENT,
                ticker TEXT NOT NULL,
                datetime TEXT NOT NULL,
                close_price REAL NOT NULL,
                UNIQUE(ticker, datetime)
            );
        )";

        char* errMsg = nullptr;
        rc = sqlite3_exec(db, createTableSQL, nullptr, nullptr, &errMsg);
        if (rc != SQLITE_OK) {
            std::cerr << "SQL error: " << errMsg << std::endl;
            sqlite3_free(errMsg);
            return false;
        }

        std::cout << "Database initialized successfully.\n";
        return true;
    }

    // Insert stock data into the SQLite database
    bool insertStockData(const std::string& ticker, const std::vector<std::pair<std::string, double>>& data) {
        if (!db) {
            std::cerr << "Database not initialized.\n";
            return false;
        }

        // Prepare an SQL statement to insert stock data or ignore if ticker/datetime combo already exists
        const char* insertSQL = "INSERT OR IGNORE INTO stock_data (ticker, datetime, close_price) VALUES (?, ?, ?);";
        sqlite3_stmt* stmt;

        for (const auto& [datetime, price] : data) {
            // Prepare insert statement
            int rc = sqlite3_prepare_v2(db, insertSQL, -1, &stmt, nullptr);
            if (rc != SQLITE_OK) {
                std::cerr << "Failed to prepare insert statement: " << sqlite3_errmsg(db) << std::endl;
                return false;
            }

            // Bind parameters
            sqlite3_bind_text(stmt, 1, ticker.c_str(), -1, SQLITE_STATIC);
            sqlite3_bind_text(stmt, 2, datetime.c_str(), -1, SQLITE_STATIC);
            sqlite3_bind_double(stmt, 3, price);

            // Execute insert
            rc = sqlite3_step(stmt);
            if (rc != SQLITE_DONE) {
                std::cerr << "Failed to insert data: " << sqlite3_errmsg(db) << std::endl;
                sqlite3_finalize(stmt);
                return false;
            }

            // Finalize the statement to release resources
            sqlite3_finalize(stmt);
        }

        std::cout << "Stock data inserted successfully.\n";
        return true;
    }

    // Check if stock data for a specific ticker already exists in the database
    bool checkStockDataExists(const std::string& ticker) {
        if (!db) {
            std::cerr << "Database not initialized.\n";
            return false;
        }

        const char* selectSQL = "SELECT COUNT(*) FROM stock_data WHERE ticker = ?;";
        sqlite3_stmt* stmt;

        int rc = sqlite3_prepare_v2(db, selectSQL, -1, &stmt, nullptr);
        if (rc != SQLITE_OK) {
            std::cerr << "Failed to prepare select statement: " << sqlite3_errmsg(db) << std::endl;
            return false;
        }

        // Bind the ticker parameter
        sqlite3_bind_text(stmt, 1, ticker.c_str(), -1, SQLITE_STATIC);

        rc = sqlite3_step(stmt);
        if (rc == SQLITE_ROW) {
            int count = sqlite3_column_int(stmt, 0);
            sqlite3_finalize(stmt);
            return count > 0;
        }

        sqlite3_finalize(stmt);
        return false;
    }

    // Load stock data if it exists in database
    std::vector<double> getStockDataFromDatabase(const std::string& ticker) {
        std::vector<double> prices;
        sqlite3* db = nullptr;
        sqlite3_stmt* stmt = nullptr;

        int rc = sqlite3_open("stock_data.db", &db);
        if (rc != SQLITE_OK) {
            std::cerr << "Failed to open the database: " << sqlite3_errmsg(db) << "\n";
            return prices;
        }

        const char* sql = "SELECT close_price FROM stock_data WHERE ticker = ? ORDER BY datetime;";
        rc = sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
        if (rc != SQLITE_OK) {
            std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << "\n";
            sqlite3_close(db);
            return prices;
        }

        sqlite3_bind_text(stmt, 1, ticker.c_str(), -1, SQLITE_STATIC);

        while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
            double price = sqlite3_column_double(stmt, 0);
            prices.push_back(price);
        }

        if (rc != SQLITE_DONE) {
            std::cerr << "Failed to retrieve data: " << sqlite3_errmsg(db) << "\n";
        }

        sqlite3_finalize(stmt);
        sqlite3_close(db);

        return prices;
    }

    // Cleanup function to close the database connection
    void closeDatabase() {
        if (db) {
            sqlite3_close(db);
            db = nullptr;
            std::cout << "Database connection closed.\n";
        }
    }
}
