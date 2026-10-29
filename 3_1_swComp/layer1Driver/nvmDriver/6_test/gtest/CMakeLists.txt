cmake_minimum_required(VERSION 3.21.0)

# Definition of test case executable and its dependencies
add_executable(testNvmDriver
    ${CMAKE_CURRENT_SOURCE_DIR}/testNvmDriver.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/mock/mockNvmDriver.c
    ${CMAKE_CURRENT_SOURCE_DIR}/fake/fakeNvmDriver.c
)

target_include_directories(testNvmDriver
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/fake
    ${CMAKE_CURRENT_SOURCE_DIR}/mock
    ${CMAKE_CURRENT_SOURCE_DIR}/stub
    ${CMAKE_CURRENT_SOURCE_DIR}/../../3_inc
    ${CMAKE_CURRENT_SOURCE_DIR}/../../5_src  
    ${CMAKE_CURRENT_SOURCE_DIR}/../../4_config
)

# # Link with Google Test and FFF
# target_link_libraries(testNvmDriver
#     gtest
#     gtest_main
#     gmock
#     gmock_main
# )

# Possibility to add preprocessor definitions and compiler options for the test case
target_compile_definitions(testNvmDriver PRIVATE GTESTING)
# target_compile_options(testNvmDriver PRIVATE)

# Make the test case discoverable by gtest
# the --gtest_shuffle causes the random of the order in which tests are executed
gtest_discover_tests(testNvmDriver
    EXTRA_ARGS --gtest_shuffle
    XML_OUTPUT_DIR ${CMAKE_BINARY_DIR}/output/gtest)
