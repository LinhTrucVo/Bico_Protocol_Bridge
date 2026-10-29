cmake_minimum_required(VERSION 3.21.0)
add_library(pwmDriver STATIC
    5_src/pwmDriverUnit.c
)
target_include_directories(pwmDriver PUBLIC
    3_inc
    4_config
    5_src
)
target_link_libraries(pwmDriver PUBLIC bico_protocol_bridge_port)
