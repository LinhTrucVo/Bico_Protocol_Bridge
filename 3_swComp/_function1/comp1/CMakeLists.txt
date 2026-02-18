cmake_minimum_required(VERSION 3.21.0)

add_library(comp1 STATIC
    5_src/comp1Unit1.c
)

target_include_directories(comp1 PUBLIC
    3_inc
    4_config
    5_src
)

target_link_libraries(comp1 PUBLIC
    addon1
)

# Add tests subdirectory
add_subdirectory(6_test/gtest)