cmake_minimum_required(VERSION 3.21.0)

add_library(I2CAPP STATIC
    5_src/I2CAPPUnit.c
)

target_include_directories(I2CAPP PUBLIC
    3_inc
    4_config
    5_src
)

add_subdirectory(6_test/gtest)
