# Find and include Google Test and CURL
find_package(GTest CONFIG REQUIRED)
find_package(CURL REQUIRED)
find_package(unofficial-sqlite3 CONFIG REQUIRED)

# Define the test executable for StockScannerTests
add_executable(StockScannerTests 
    ../src/core/functions.cpp
    ../src/database/database_utils.cpp
    ../src/menu/menu_actions.cpp
    ../src/sorting/sorting_analysis.cpp
    ../src/linked_lists/stack_queue.cpp
    StockScannerTests.cpp
    StackQueueTests.cpp
)
# Include directories for the project
target_include_directories(StockScannerTests PRIVATE ../include)

# Link GTest targets, CURL, and SQLite
target_link_libraries(StockScannerTests PRIVATE GTest::gtest GTest::gtest_main CURL::libcurl unofficial::sqlite3::sqlite3)

# Register tests with CTest
add_test(NAME AllTestsInStockScannerTests COMMAND StockScannerTests)