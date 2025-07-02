cmake_minimum_required(VERSION 3.10)
project(MatrixNN CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -O2")

# Include and source directories
include_directories(include)
file(GLOB SRC_FILES "src/*.cpp")

# Main executable
add_executable(main src/main.cpp ${SRC_FILES})

# GoogleTest via FetchContent
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/heads/main.zip
  DOWNLOAD_EXTRACT_TIMESTAMP true
)
FetchContent_MakeAvailable(googletest)

enable_testing()

# Exclude main.cpp from test build
list(REMOVE_ITEM SRC_FILES ${CMAKE_SOURCE_DIR}/src/main.cpp)

file(GLOB TEST_FILES "tests/*.cpp")

# Test binary
add_executable(matrix_tests ${TEST_FILES} ${SRC_FILES})
target_link_libraries(matrix_tests gtest gtest_main)

# Let GoogleTest handle individual test cases
include(GoogleTest)
gtest_discover_tests(matrix_tests
    DISCOVERY_TIMEOUT 10
    EXTRA_ARGS --gtest_color=yes
    PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_BINARY_DIR}"
)

