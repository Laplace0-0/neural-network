cmake_minimum_required(VERSION 3.10)
project(NEURAL CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -O2")

# --------------------------------------------------
# Include directories for the library
# --------------------------------------------------
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# --------------------------------------------------
# Library source files
# --------------------------------------------------
file(GLOB_RECURSE LIB_SOURCES
    "src/*.cpp"
)

# --------------------------------------------------
# Create Static Library
# --------------------------------------------------
add_library(neural STATIC ${LIB_SOURCES})

# Add public include path so other projects can use <neural/...>
target_include_directories(neural
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

# --------------------------------------------------
# Main executable (for demos or testing)
# --------------------------------------------------
add_executable(main src/main.cpp)
target_link_libraries(main PRIVATE neural)

# --------------------------------------------------
# Testing setup using GoogleTest
# --------------------------------------------------
include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/heads/main.zip
)
FetchContent_MakeAvailable(googletest)

enable_testing()

file(GLOB TEST_FILES "tests/*.cpp")

add_executable(matrix_tests ${TEST_FILES})
target_link_libraries(matrix_tests PRIVATE neural gtest gtest_main)

include(GoogleTest)
gtest_discover_tests(matrix_tests
    DISCOVERY_TIMEOUT 10
    EXTRA_ARGS --gtest_color=yes
    PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_BINARY_DIR}"
)

# --------------------------------------------------
# (Optional) Install support for reusability
# --------------------------------------------------
install(TARGETS neural EXPORT NeuralTargets
    ARCHIVE DESTINATION lib
    INCLUDES DESTINATION include
)
install(DIRECTORY include/neural DESTINATION include)
