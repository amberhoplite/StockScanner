#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <numeric>
#include <curl/curl.h>
#include "functions.h"


// Callback function for curl to handle data received from HTTP response
// Appends the response data to the provided string
size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

// Displays the menu options
void showMenu() {
    std::cout << "Menu:\n";
    std::cout << "1. Get Stock Ticker Data\n";
    std::cout << "2. Calculate Average Stock Price\n";
    std::cout << "3. Exit\n";
    std::cout << "Select an option: ";
}

// Reads the API key from a config file to avoid hardcoding sensitive API keys
std::string loadApiKeyFromConfig() {
    std::ifstream configFile("config.txt");
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
        std::string url = "https://www.alphavantage.co/query?function=TIME_SERIES_INTRADAY"
                          "&symbol=" + ticker +
                          "&interval=5min"
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
            std::cout << "Data fetched successfully: \n" << readBuffer << "\n";
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
