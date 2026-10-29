cmake_minimum_required(VERSION 3.21.0)

# Definition of test case executable and its dependencies
add_executable(integrationTest
)

target_include_directories(integrationTest
    PUBLIC
)

# Possibility to add preprocessor definitions and compiler options for the test case
target_compile_definitions(integrationTest PRIVATE GTESTING)
# target_compile_options(integrationTest PRIVATE)

# Make the test case discoverable by gtest
# the --gtest_shuffle causes the random of the order in which tests are executed
gtest_discover_tests(integrationTest
    EXTRA_ARGS --gtest_shuffle
    XML_OUTPUT_DIR ${CMAKE_BINARY_DIR}/output/gtest)
