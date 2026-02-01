cmake_minimum_required(VERSION 3.21.0)

add_library(serialize STATIC
    5_src/serializeUnit.c
)

target_include_directories(serialize PUBLIC
    3_inc
    4_config
    5_src
)

add_subdirectory(6_test/gtest)
