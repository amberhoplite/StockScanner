# Find and include Google Test, CURL, and SQLite
find_package(GTest CONFIG REQUIRED)
find_package(CURL REQUIRED)
find_package(unofficial-sqlite3 CONFIG REQUIRED)


# Add a static library for shared test helpers
add_library(test_helpers STATIC test_helpers.cpp)


# Include directories for the project
target_include_directories(test_helpers PRIVATE ../include)


# Define the test executable for StockScannerTests
add_executable(StockScannerTests 
    ../src/core/functions.cpp
    ../src/database/database_utils.cpp
    ../src/menu/menu_actions.cpp
    ../src/sorting/sorting_analysis.cpp
    ../src/linked_lists/stack_queue.cpp
    ../src/binary_tree/binary_tree.cpp
    StockScannerTests.cpp
)
target_link_libraries(StockScannerTests PRIVATE test_helpers GTest::gtest GTest::gtest_main CURL::libcurl unofficial::sqlite3::sqlite3)
add_test(NAME AllTestsInStockScannerTests COMMAND StockScannerTests)


# Define the test executable for StackQueueTests
add_executable(StackQueueTests 
    ../src/linked_lists/stack_queue.cpp
    StackQueueTests.cpp
)
target_link_libraries(StackQueueTests PRIVATE test_helpers GTest::gtest GTest::gtest_main CURL::libcurl unofficial::sqlite3::sqlite3)
add_test(NAME AllTestsInStackQueueTests COMMAND StackQueueTests)


# Define the test executable for BinaryTreePerformanceTests
add_executable(BinaryTreePerformanceTests 
    ../src/binary_tree/binary_tree.cpp
    BinaryTreePerformanceTests.cpp
)
target_link_libraries(BinaryTreePerformanceTests PRIVATE test_helpers GTest::gtest GTest::gtest_main CURL::libcurl unofficial::sqlite3::sqlite3)
add_test(NAME AllTestsInBinaryTreePerformanceTests COMMAND BinaryTreePerformanceTests)


add_executable(BinaryTreeFunctionalityTests 
    test_helpers.cpp
    ../src/binary_tree/binary_tree.cpp
    BinaryTreeFunctionalityTests.cpp
)
target_link_libraries(BinaryTreeFunctionalityTests PRIVATE GTest::gtest GTest::gtest_main)
add_test(NAME AllTestsInBinaryTreeFunctionalityTests COMMAND BinaryTreeFunctionalityTests)


# Define the test executable for HashTablePerformanceTests
add_executable(HashTablePerformanceTests 
    ../src/hash_tables/hash_table.h
    ../src/hash_tables/open_addressing_hash_table.h
    HashTablePerformanceTests.cpp
)
target_link_libraries(HashTablePerformanceTests PRIVATE test_helpers GTest::gtest GTest::gtest_main CURL::libcurl unofficial::sqlite3::sqlite3)
add_test(NAME AllTestsInHashTablePerformanceTests COMMAND HashTablePerformanceTests)
