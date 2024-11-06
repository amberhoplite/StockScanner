#include <gtest/gtest.h>
#include "../src/functions.h"
#include <vector>

// Test suite for StockScanner functions
TEST(StockScannerTests, TestLoadStockData) {
    // Mock data representing stock prices for testing purposes
    std::vector<double> stockPrices = { 100.0, 105.0, 110.0, 115.0 };

    // Check if the size of the stockPrices vector is as expected (4), then check if first and last prices are as expected.
    EXPECT_EQ(stockPrices.size(), 4) << "Stock data size should be 4.";
    EXPECT_DOUBLE_EQ(stockPrices[0], 100.0) << "First price should be 100.0.";
    EXPECT_DOUBLE_EQ(stockPrices[3], 115.0) << "Last price should be 115.0.";
}
// Test suite for calculateAveragePrice function
TEST(StockScannerTests, TestCalculateAveragePrice) {
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
