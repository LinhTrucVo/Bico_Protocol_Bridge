cmake_minimum_required(VERSION 3.21.0)

# Definition of test case executable and its dependencies
add_executable(testSpiMasterDriver
    ${CMAKE_CURRENT_SOURCE_DIR}/testSpiMasterDriver.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/mock/mockSpiMasterDriver.c
    ${CMAKE_CURRENT_SOURCE_DIR}/fake/fakeSpiMasterDriver.c
)

target_include_directories(testSpiMasterDriver
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/fake
    ${CMAKE_CURRENT_SOURCE_DIR}/mock
    ${CMAKE_CURRENT_SOURCE_DIR}/stub
    ${CMAKE_CURRENT_SOURCE_DIR}/../../3_inc
    ${CMAKE_CURRENT_SOURCE_DIR}/../../5_src  
    ${CMAKE_CURRENT_SOURCE_DIR}/../../4_config
)

# # Link with Google Test and FFF
# target_link_libraries(testSpiMasterDriver
#     gtest
#     gtest_main
#     gmock
#     gmock_main
# )

# Possibility to add preprocessor definitions and compiler options for the test case
target_compile_definitions(testSpiMasterDriver PRIVATE GTESTING)
# target_compile_options(testSpiMasterDriver PRIVATE)

# Make the test case discoverable by gtest
# the --gtest_shuffle causes the random of the order in which tests are executed
gtest_discover_tests(testSpiMasterDriver
    EXTRA_ARGS --gtest_shuffle
    XML_OUTPUT_DIR ${CMAKE_BINARY_DIR}/output/gtest)
