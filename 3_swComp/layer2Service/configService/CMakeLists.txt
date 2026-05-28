cmake_minimum_required(VERSION 3.21.0)

add_library(configService STATIC
    5_src/configServiceUnit.c
)

target_include_directories(configService PUBLIC
    3_inc
    4_config
    5_src
)

target_link_libraries(configService PUBLIC nvmService)

add_subdirectory(6_test/gtest)
