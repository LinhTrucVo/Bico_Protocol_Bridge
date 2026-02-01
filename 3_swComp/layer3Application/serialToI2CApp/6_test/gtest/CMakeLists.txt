cmake_minimum_required(VERSION 3.21.0)

# Definition of test case executable and its dependencies
add_executable(testSerialToI2CApp
    ${CMAKE_CURRENT_SOURCE_DIR}/testSerialToI2CApp.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/mock/mockSerialToI2CApp.c
    ${CMAKE_CURRENT_SOURCE_DIR}/fake/fakeSerialToI2CApp.c
)

target_include_directories(testSerialToI2CApp
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/fake
    ${CMAKE_CURRENT_SOURCE_DIR}/mock
    ${CMAKE_CURRENT_SOURCE_DIR}/stub
    ${CMAKE_CURRENT_SOURCE_DIR}/../../3_inc
    ${CMAKE_CURRENT_SOURCE_DIR}/../../5_src  
    ${CMAKE_CURRENT_SOURCE_DIR}/../../4_config
)

# # Link with Google Test and FFF
# target_link_libraries(testSerialToI2CApp
#     gtest
#     gtest_main
#     gmock
#     gmock_main
# )

# Possibility to add preprocessor definitions and compiler options for the test case
target_compile_definitions(testSerialToI2CApp PRIVATE GTESTING)
# target_compile_options(testSerialToI2CApp PRIVATE)

# Make the test case discoverable by gtest
# the --gtest_shuffle causes the random of the order in which tests are executed
gtest_discover_tests(testSerialToI2CApp
    EXTRA_ARGS --gtest_shuffle
    XML_OUTPUT_DIR ${CMAKE_BINARY_DIR}/output/gtest)
