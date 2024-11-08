# StockScanner

## Features

- **Fetch Real-Time Stock Data**: Retrieves 5-minute intraday stock prices for a user-provided ticker symbol.
- **Calculate Average Stock Price**: Calculates the average of the retrieved stock prices.
- **Menu-Driven Interface**: Easy-to-use console menu for selecting options.


## Requirements

- **C++17** or later
- **CMake** for building the project
- **vcpkg** package manager for dependency management
- **Alpha Vantage API Key** (free API key available [here](https://www.alphavantage.co/support/#api-key))

### Dependencies

The following libraries are used in this project:

- **cURL**: For making HTTP requests.
- **nlohmann/json**: For parsing JSON responses.
- **Google Test**: For unit testing.

Install these dependencies using `vcpkg` with:

```bash
vcpkg install curl jsoncpp gtest
```

## Setup Instructions

1. **Clone the repository**:
   ```bash
   git clone --recurse-submodules https://github.com/amberhoplite/StockScanner.git
   cd StockScanner
   ```
2. **Set Up Your API Key**
   - Create a file named `config.txt` in the project root directory.

   - Add your Alpha Vantage API key to `config.txt` in the following format:
   ```plaintext
   STOCK_API_KEY=your_api_key_here
   ```

3. Build the Project
   - Ensure you have vcpkg installed and integrated with CMake. Then, in the project directory, build the project using CMake:

   ```bash
   mkdir build
   cd build
   cmake ..
   cmake --build .
   ```

4. Run the Application
   - After building, run the application from the build directory:

   ```bash
   ./StockScanner
   ```

## Usage

Upon launching, the program will display a menu with the following options:

1. Get Stock Ticker Data: Enter a stock ticker (e.g., AAPL) to fetch recent intraday price data.
2. Calculate Average Stock Price: Computes the average of the retrieved stock prices.
3. Exit: Exits the application.

### Sample Output
```plaintext
Menu:
1. Get Stock Ticker Data        
2. Calculate Average Stock Price
3. Exit
Select an option: 1
Enter stock ticker: aapl
API key loaded successfully.
Data parsed successfully: 
Stock data loaded successfully. 

Menu:
1. Get Stock Ticker Data        
2. Calculate Average Stock Price
3. Exit
Select an option: 2
Average Stock Price: 227.293    
```