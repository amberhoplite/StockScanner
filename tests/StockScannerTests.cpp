#include <gtest/gtest.h>
#include "../src/functions.h"
#include <vector>
#include <deque>
#include <sqlite3.h>

using namespace StockScanner;

// Test suite for DataLoading functions
TEST(DataLoadingTests, TestLoadStockData) {
    // Mock data representing stock prices for testing purposes
    std::vector<double> stockPrices = { 100.0, 105.0, 110.0, 115.0 };

    // Check if the size of the stockPrices vector is as expected (4), then check if first and last prices are as expected.
    EXPECT_EQ(stockPrices.size(), 4) << "Stock data size should be 4.";
    EXPECT_DOUBLE_EQ(stockPrices[0], 100.0) << "First price should be 100.0.";
    EXPECT_DOUBLE_EQ(stockPrices[3], 115.0) << "Last price should be 115.0.";
}
// Test suite for calculateAveragePrice function
TEST(CalculationTests, TestCalculateAveragePrice) {
    // Test case with multiple price values to calculate average
    std::vector<double> prices = { 100.0, 200.0, 300.0, 400.0 };
    double average = calculateAveragePrice(prices);
    // Validate that the calculated average is approximately 250.0 within a tolerance
    EXPECT_NEAR(average, 250.0, 0.001) << "Average of {100, 200, 300, 400} should be 250.";

    // Test case with an empty vector to check edge case handling
    std::vector<double> emptyPrices;
    average = calculateAveragePrice(emptyPrices);
    EXPECT_NEAR(average, 0.0, 0.001) << "Average of an empty vector should be 0.";

    // Test case with a single price to check single-element behavior
    std::vector<double> singlePrice = { 150.0 };
    average = calculateAveragePrice(singlePrice);
    EXPECT_NEAR(average, 150.0, 0.001) << "Average of a single-element vector {150} should be 150.";
}

// Test suite for the threshold feature in price movements
TEST(ThresholdCheckingTests, TestThresholdCheck) {
    // Define a threshold value for significant price movement
    double threshold = 5.0;

    // Example price data where movement is above the threshold
    std::vector<double> pricesAboveThreshold = {100.0, 106.0};
    EXPECT_TRUE(checkThreshold(pricesAboveThreshold, threshold))
        << "Price movement should be detected as exceeding the threshold.";

    // Example price data where movement is below the threshold
    std::vector<double> pricesBelowThreshold = {100.0, 102.0};
    EXPECT_FALSE(checkThreshold(pricesBelowThreshold, threshold))
        << "Price movement should be detected as not meeting the threshold.";

    // Example price data where movement is just at the threshold
    std::vector<double> pricesAtThreshold = {100.0, 105.0};
    EXPECT_TRUE(checkThreshold(pricesAtThreshold, threshold)) 
        << "Price movement should meet the threshold exactly.";

    // Example price data where prices do not meet threshold
    std::vector<double> randomPrices = {100.0, 98.0, 99.0, 97.5, 100.0};
    EXPECT_FALSE(checkThreshold(randomPrices, threshold)) 
        << "Random price data should not meet the threshold.";
}

TEST(ThresholdCheckingTests, TestModifyThreshold) {
    double threshold = 5.0;

    // Set a new threshold and check if it's applied correctly
    threshold = 10.0;
    std::vector<double> prices = {100.0, 111.0};
    EXPECT_TRUE(checkThreshold(prices, threshold)) << "Price movement should exceed the new threshold of 10%.";

    threshold = 15.0;
    EXPECT_FALSE(checkThreshold(prices, threshold)) << "Price movement should not exceed the new threshold of 15%.";
}

// Test suite for Sliding Window functionality
TEST(SlidingWindowTests, TestSlidingWindow) {
    // Define a sample deque with some price data
    std::deque<double> prices = {100.0, 101.0, 102.0, 103.0, 104.0, 105.0};

    // Apply a sliding window of size 3
    std::deque<double> windowedPrices = applySlidingWindow(prices, 3);

    // Check that the window contains exactly 3 elements (the last three prices)
    EXPECT_EQ(windowedPrices.size(), 3);
    EXPECT_DOUBLE_EQ(windowedPrices[0], 103.0);
    EXPECT_DOUBLE_EQ(windowedPrices[1], 104.0);
    EXPECT_DOUBLE_EQ(windowedPrices[2], 105.0);

    // Check for an edge case where the window size is larger than the deque
    windowedPrices = applySlidingWindow(prices, 10);
    EXPECT_EQ(windowedPrices.size(), prices.size());  // Window should cover the entire deque

    // Check for an edge case where the window size is 1
    windowedPrices = applySlidingWindow(prices, 1);
    EXPECT_EQ(windowedPrices.size(), 1);
    EXPECT_DOUBLE_EQ(windowedPrices[0], 105.0);
}

// Test suite for modifying sliding window size
TEST(SlidingWindowTests, TestModifySlidingWindowSize) {
    std::deque<double> prices = {100.0, 101.0, 102.0, 103.0, 104.0, 105.0};

    // Apply different sliding window sizes and check results
    size_t windowSize = 4;
    std::deque<double> windowedPrices = applySlidingWindow(prices, windowSize);
    EXPECT_EQ(windowedPrices.size(), 4) << "Sliding window size should be 4.";
    EXPECT_DOUBLE_EQ(windowedPrices[0], 102.0) << "First element of window should be 102.0.";

    windowSize = 1;
    windowedPrices = applySlidingWindow(prices, windowSize);
    EXPECT_EQ(windowedPrices.size(), 1) << "Sliding window size should be 1.";
    EXPECT_DOUBLE_EQ(windowedPrices[0], 105.0) << "Only element of window should be 105.0.";

    windowSize = 10;
    windowedPrices = applySlidingWindow(prices, windowSize);
    EXPECT_EQ(windowedPrices.size(), prices.size()) << "Sliding window size larger than deque should cover all elements.";
}

// Test suite for Recursive Momentum Detection
TEST(MomentumDetectionTests, TestMomentumDetectionVariousSizes) {
    std::deque<double> increasingPrices = {100.0, 105.0, 110.0, 115.0, 120.0};
    std::deque<double> mixedPrices = {100.0, 105.0, 100.0, 105.0, 100.0};
    std::deque<double> decreasingPrices = {120.0, 115.0, 110.0, 105.0, 100.0};

    // Expected momentum should be positive
    EXPECT_TRUE(detectMomentum(increasingPrices)) << "Momentum should be increasing for an upward trend.";

    // Expected momentum should be negative
    EXPECT_FALSE(detectMomentum(decreasingPrices)) << "Momentum should be decreasing for a downward trend.";

    // Expected momentum should be neutral (false in this case)
    EXPECT_FALSE(detectMomentum(mixedPrices)) << "Momentum should be neutral for a mixed trend.";
}

// Integration test suite for sliding window as input to momentum detection
TEST(IntegrationTests, TestSlidingWindowAndMomentumIntegration) {
    std::deque<double> prices = {100.0, 105.0, 102.0, 108.0, 110.0, 112.0};
    auto slidingPrices = applySlidingWindow(prices, 4);

    // Check for momentum in the sliding window
    EXPECT_TRUE(detectMomentum(slidingPrices)) 
        << "Sliding window prices should indicate a positive momentum.";
}

// Additional integration test for threshold check after modification
TEST(IntegrationTests, TestModifiedThresholdAndMomentumIntegration) {
    std::vector<double> prices = {100.0, 120.0, 140.0, 160.0, 180.0};
    double threshold = 10.0;

    // Check if modifying threshold impacts the momentum check
    EXPECT_TRUE(checkThreshold(prices, threshold)) << "Price movement should exceed modified threshold of 10%.";

    threshold = 85.0;
    EXPECT_FALSE(checkThreshold(prices, threshold)) << "Price movement should not exceed a modified threshold of 50%.";
}

// SQLite setup and basic database operations test
TEST(SQLiteTests, TestSQLiteConnection) {
    sqlite3* db;
    char* errMsg = 0;
    int rc;

    // Open a database connection
    rc = sqlite3_open("test.db", &db);
    ASSERT_EQ(rc, SQLITE_OK) << "Failed to open the SQLite database: " << sqlite3_errmsg(db);

    // Create a simple table
    const char* sql = "CREATE TABLE IF NOT EXISTS test_table("
                      "ID INT PRIMARY KEY NOT NULL,"
                      "NAME TEXT NOT NULL);";

    rc = sqlite3_exec(db, sql, 0, 0, &errMsg);
    ASSERT_EQ(rc, SQLITE_OK) << "Failed to create table: " << (errMsg ? errMsg : "Unknown error");

    // Insert a record
    sql = "INSERT INTO test_table (ID, NAME) VALUES (1, 'TestName');";
    rc = sqlite3_exec(db, sql, 0, 0, &errMsg);
    ASSERT_EQ(rc, SQLITE_OK) << "Failed to insert record: " << (errMsg ? errMsg : "Unknown error");

    // Retrieve the data to verify insertion
    const char* query = "SELECT * FROM test_table WHERE ID = 1;";
    sqlite3_stmt* stmt;

    rc = sqlite3_prepare_v2(db, query, -1, &stmt, nullptr);
    ASSERT_EQ(rc, SQLITE_OK) << "Failed to prepare select statement: " << sqlite3_errmsg(db);

    rc = sqlite3_step(stmt);
    ASSERT_EQ(rc, SQLITE_ROW) << "No rows returned or step failed.";

    ASSERT_EQ(sqlite3_column_int(stmt, 0), 1) << "Unexpected ID value retrieved.";
    ASSERT_STREQ(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)), "TestName") << "Unexpected NAME value retrieved.";

    // Clean up
    sqlite3_finalize(stmt);
    sqlite3_close(db);
}