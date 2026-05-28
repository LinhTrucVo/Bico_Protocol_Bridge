cmake_minimum_required(VERSION 3.21.0)

add_library(SPIAPP STATIC
    5_src/SPIAPPUnit.c
)

target_include_directories(SPIAPP PUBLIC
    3_inc
    4_config
    5_src
)

add_subdirectory(6_test/gtest)
