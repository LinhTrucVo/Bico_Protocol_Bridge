cmake_minimum_required(VERSION 3.21.0)

add_library(dataConversionService STATIC
    5_src/dataConversionServiceUnit.c
)

target_include_directories(dataConversionService PUBLIC
    3_inc
    4_config
    5_src
)

add_subdirectory(6_test/gtest)
