cmake_minimum_required(VERSION 3.21.0)

# Definition of test case executable and its dependencies
add_executable(testSerialToAnalogApp
    ${CMAKE_CURRENT_SOURCE_DIR}/testSerialToAnalogApp.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/mock/mockSerialToAnalogApp.c
    ${CMAKE_CURRENT_SOURCE_DIR}/fake/fakeSerialToAnalogApp.c
)

target_include_directories(testSerialToAnalogApp
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/fake
    ${CMAKE_CURRENT_SOURCE_DIR}/mock
    ${CMAKE_CURRENT_SOURCE_DIR}/stub
    ${CMAKE_CURRENT_SOURCE_DIR}/../../3_inc
    ${CMAKE_CURRENT_SOURCE_DIR}/../../5_src  
    ${CMAKE_CURRENT_SOURCE_DIR}/../../4_config
)

# # Link with Google Test and FFF
# target_link_libraries(testSerialToAnalogApp
#     gtest
#     gtest_main
#     gmock
#     gmock_main
# )

# Possibility to add preprocessor definitions and compiler options for the test case
target_compile_definitions(testSerialToAnalogApp PRIVATE GTESTING)
# target_compile_options(testSerialToAnalogApp PRIVATE)

# Make the test case discoverable by gtest
# the --gtest_shuffle causes the random of the order in which tests are executed
gtest_discover_tests(testSerialToAnalogApp
    EXTRA_ARGS --gtest_shuffle
    XML_OUTPUT_DIR ${CMAKE_BINARY_DIR}/output/gtest)
