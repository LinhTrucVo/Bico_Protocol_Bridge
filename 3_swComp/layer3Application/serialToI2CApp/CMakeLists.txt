cmake_minimum_required(VERSION 3.21.0)

add_library(serialToI2CApp STATIC
    5_src/serialToI2CAppUnit.c
)

target_include_directories(serialToI2CApp PUBLIC
    3_inc
    4_config
    5_src
)

add_subdirectory(6_test/gtest)
