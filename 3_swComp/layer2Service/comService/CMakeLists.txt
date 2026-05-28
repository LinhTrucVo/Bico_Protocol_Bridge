cmake_minimum_required(VERSION 3.21.0)

add_library(comService STATIC
    5_src/comServiceUnit.c
)

target_include_directories(comService PUBLIC
    3_inc
    4_config
    5_src
)

target_link_libraries(comService PUBLIC
    serialDriver
)

add_subdirectory(6_test/gtest)
