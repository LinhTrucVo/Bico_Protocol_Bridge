cmake_minimum_required(VERSION 3.21.0)

add_library(serialDriver STATIC
    5_src/serialDriverUnit.c
)

target_include_directories(serialDriver PUBLIC
    3_inc
    4_config
    5_src
)

target_link_libraries(serialDriver PUBLIC bico_protocol_bridge_port)
