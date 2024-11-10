#include <iostream>
#include <deque>
#include <vector>
#include <string>
#include <fstream>
#include <numeric>
#include <curl/curl.h>
#include "functions.h"
#include <nlohmann/json.hpp>

using json = nlohmann::json;

namespace StockScanner {

    // Callback function for curl to handle data received from HTTP response
    // Appends the response data to the provided string
    size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
        ((std::string*)userp)->append((char*)contents, size * nmemb);
        return size * nmemb;
    }

    // Displays the menu options
    void showMenu(double threshold, size_t windowSize) {
        std::cout << "Menu:\n";
        std::cout << "1. Get Stock Ticker Data\n";
        std::cout << "2. Calculate Average Stock Price\n";
        std::cout << "3. Check Threshold\n";
        std::cout << "4. Modify Threshold Setting (Current: " << threshold << "%)\n";
        std::cout << "5. Apply Sliding Window\n";
        std::cout << "6. Modify Sliding Window Size (Current: " << windowSize << ")\n";
        std::cout << "7. Detect Momentum\n";
        std::cout << "8. Exit\n";
        std::cout << "Select an option: ";
    }

    // Reads the API key from a config file to avoid hardcoding sensitive API keys
    std::string loadApiKeyFromConfig() {
        std::ifstream configFile("../../config.txt");
        std::string line, apiKey;
        if (configFile.is_open()) {
            while (std::getline(configFile, line)) {
                if (line.find("STOCK_API_KEY=") == 0) {
                    apiKey = line.substr(14); // Extract value after "STOCK_API_KEY="
                    break;
                }
            }
            configFile.close();
        }
        return apiKey;
    }

    // Fetches stock price data from an API given a ticker symbol
    std::vector<double> loadStockData(const std::string& ticker) {
    #ifndef UNIT_TESTING
        std::string readBuffer;     // Buffer to store the response data
        std::vector<double> prices; // Vector to store parsed price data

        CURL* curl;
        CURLcode res;
        curl_global_init(CURL_GLOBAL_DEFAULT);
        curl = curl_easy_init();

        if (curl) {
            std::string apiKey = loadApiKeyFromConfig();
            if (apiKey.empty()) {
                std::cerr << "API key not found. Please set STOCK_API_KEY in config.txt.\n";
            } else {
                std::cout << "API key loaded successfully.\n";
            }

            // Construct API request URL
            std::string url = "https://www.alphavantage.co/query?function=TIME_SERIES_DAILY"
                            "&symbol=" + ticker +
                            "&apikey=" + apiKey;

            // Set curl options for URL and callback function
            curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

            // Perform the request
            res = curl_easy_perform(curl);

            // Check if the request was successful
            if (res != CURLE_OK) {
                std::cerr << "cURL error: " << curl_easy_strerror(res) << "\n";
            } else {
                try {
                    // Parse JSON data
                    auto jsonResponse = json::parse(readBuffer);

                    // Navigate to "Time Series (5min)" and extract close prices
                    auto timeSeries = jsonResponse["Time Series (Daily)"];
                    for (auto& [timestamp, data] : timeSeries.items()) {
                        prices.push_back(std::stod(data["4. close"].get<std::string>()));
                    }

                    std::cout << "Data parsed successfully: \n";
                } catch (const json::exception& e) {
                    std::cerr << "JSON parsing error: " << e.what() << "\n";
                }
            }

            curl_easy_cleanup(curl);
        }

        curl_global_cleanup();
        return prices;
    #else
        // Mock data for testing
        return {100.0, 105.0, 110.0, 115.0};
    #endif
    }

    // Calculates and returns the average of a vector of prices
    // Return 0 if there are no prices to average
    double calculateAveragePrice(const std::vector<double>& prices) {
        if (prices.empty()) {
            return 0.0;
        }
        double sum = std::accumulate(prices.begin(), prices.end(), 0.0);
        return sum / prices.size();
    }

    // Checks if the price change exceeds the threshold percentage
    bool checkThreshold(const std::vector<double>& prices, double threshold) {
        if (prices.size() < 2) return false;

        // Calculate percentage change between the first and last price
        double percentChange = ((prices.back() - prices.front()) / prices.front()) * 100;
        return std::abs(percentChange) >= threshold;
    }

    // Returns a sliding window of the last n elements from a deque
    std::deque<double> applySlidingWindow(const std::deque<double>& prices, size_t windowSize) {
        if (windowSize >= prices.size()) {
            return prices;  // Return entire deque if window size exceeds the number of elements
        }

        return std::deque<double>(prices.end() - windowSize, prices.end());
    }

    // Recursive function to detect momentum based on price differences
    bool detectMomentum(const std::deque<double>& prices, size_t index, int trendCount) {
        if (index >= prices.size() - 1) {
            return trendCount >= static_cast<int>(prices.size()) - 1;  // Positive trend if consistent
        }

        // Determine if current price is higher or lower than the next one
        bool isIncreasing = prices[index] < prices[index + 1];
        if ((isIncreasing && trendCount >= 0) || (!isIncreasing && trendCount <= 0)) {
            trendCount += isIncreasing ? 1 : -1;
        } else {
            trendCount = isIncreasing ? 1 : -1;  // Reset the trend if it switches
        }

        // Continue recursion
        return detectMomentum(prices, index + 1, trendCount);
    }
}