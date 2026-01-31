cmake_minimum_required(VERSION 3.21.0)

# Definition of test case executable and its dependencies
add_executable(testComp1
    ${CMAKE_CURRENT_SOURCE_DIR}/testComp1.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/mock/mockComp1.c
    ${CMAKE_CURRENT_SOURCE_DIR}/mock/fakeComp1.c
)

target_include_directories(testComp1
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/fake
    ${CMAKE_CURRENT_SOURCE_DIR}/mock
    ${CMAKE_CURRENT_SOURCE_DIR}/stub
    ${CMAKE_CURRENT_SOURCE_DIR}/../../inc
    ${CMAKE_CURRENT_SOURCE_DIR}/../../src  
    ${CMAKE_CURRENT_SOURCE_DIR}/../../config
)

# # Link with Google Test and FFF
# target_link_libraries(testComp1
#     gtest
#     gtest_main
#     gmock
#     gmock_main
# )

# Possibility to add preprocessor definitions and compiler options for the test case
target_compile_definitions(testComp1 PRIVATE GTESTING)
# target_compile_options(testComp1 PRIVATE)

# Make the test case discoverable by gtest
# the --gtest_shuffle causes the random of the order in which tests are executed
gtest_discover_tests(testComp1
    EXTRA_ARGS --gtest_shuffle
    XML_OUTPUT_DIR ${CMAKE_BINARY_DIR}/output/gtest)