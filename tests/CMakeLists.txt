# Find and include Google Test and CURL
find_package(GTest CONFIG REQUIRED)
find_package(CURL REQUIRED)

# Define the test executable for StockScannerTests
add_executable(StockScannerTests StockScannerTests.cpp ../src/functions.cpp)
target_include_directories(StockScannerTests PRIVATE ../include)

# Link GTest targets and CURL for multi-threading
target_link_libraries(StockScannerTests PRIVATE GTest::gtest GTest::gtest_main CURL::libcurl)

# Register tests with CTest
add_test(NAME AllTestsInStockScannerTests COMMAND StockScannerTests)
