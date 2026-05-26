cmake_minimum_required(VERSION 3.21.0)

# Definition of test case executable and its dependencies
add_executable(testCentralAppController
    ${CMAKE_CURRENT_SOURCE_DIR}/testCentralAppController.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/mock/mockCentralAppController.c
    ${CMAKE_CURRENT_SOURCE_DIR}/fake/fakeCentralAppController.c
)

target_include_directories(testCentralAppController
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/fake
    ${CMAKE_CURRENT_SOURCE_DIR}/mock
    ${CMAKE_CURRENT_SOURCE_DIR}/stub
    ${CMAKE_CURRENT_SOURCE_DIR}/../../3_inc
    ${CMAKE_CURRENT_SOURCE_DIR}/../../5_src
    ${CMAKE_CURRENT_SOURCE_DIR}/../../4_config
    # Layer2 Deserialize
    ${CMAKE_CURRENT_SOURCE_DIR}/../../../../layer2Service/deserialize/3_inc
    ${CMAKE_CURRENT_SOURCE_DIR}/../../../../layer2Service/deserialize/5_src
    ${CMAKE_CURRENT_SOURCE_DIR}/../../../../layer2Service/deserialize/4_config
    # Layer2 Serialize
    ${CMAKE_CURRENT_SOURCE_DIR}/../../../../layer2Service/serialize/3_inc
    ${CMAKE_CURRENT_SOURCE_DIR}/../../../../layer2Service/serialize/5_src
    ${CMAKE_CURRENT_SOURCE_DIR}/../../../../layer2Service/serialize/4_config
    # Layer2 ConfigService
    ${CMAKE_CURRENT_SOURCE_DIR}/../../../../layer2Service/configService/3_inc
    ${CMAKE_CURRENT_SOURCE_DIR}/../../../../layer2Service/configService/5_src
    ${CMAKE_CURRENT_SOURCE_DIR}/../../../../layer2Service/configService/4_config
    # Layer3 Peripheral Apps
    ${CMAKE_CURRENT_SOURCE_DIR}/../../../../layer3Application/serialToAnalogApp/3_inc
    ${CMAKE_CURRENT_SOURCE_DIR}/../../../../layer3Application/serialToAnalogApp/5_src
    ${CMAKE_CURRENT_SOURCE_DIR}/../../../../layer3Application/serialToDigitalApp/3_inc
    ${CMAKE_CURRENT_SOURCE_DIR}/../../../../layer3Application/serialToDigitalApp/5_src
    ${CMAKE_CURRENT_SOURCE_DIR}/../../../../layer3Application/serialToI2CApp/3_inc
    ${CMAKE_CURRENT_SOURCE_DIR}/../../../../layer3Application/serialToI2CApp/5_src
    ${CMAKE_CURRENT_SOURCE_DIR}/../../../../layer3Application/serialToSPIApp/3_inc
    ${CMAKE_CURRENT_SOURCE_DIR}/../../../../layer3Application/serialToSPIApp/5_src
)

# Possibility to add preprocessor definitions and compiler options for the test case
target_compile_definitions(testCentralAppController PRIVATE GTESTING)

# Make the test case discoverable by gtest
gtest_discover_tests(testCentralAppController EXTRA_ARGS --gtest_shuffle
    XML_OUTPUT_DIR ${CMAKE_BINARY_DIR}/output/gtest)