cmake_minimum_required(VERSION 3.10)
project(StockScanner)

# Enable testing for the entire project
set(BUILD_TESTING ON)
include(CTest)
enable_testing()

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)

# Use vcpkg toolchain file to locate dependencies
set(CMAKE_TOOLCHAIN_FILE "${CMAKE_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake")

# Include directories for header files
include_directories(include)

# Add the main executable
add_executable(StockScanner src/main.cpp src/functions.cpp)

# Link libraries for CURL
find_package(CURL REQUIRED)
target_link_libraries(StockScanner PRIVATE CURL::libcurl)

# Add the tests subdirectory
add_subdirectory(tests)


