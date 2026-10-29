cmake_minimum_required(VERSION 3.21.0)

# GPIO Driver Library
add_library(gpioDriver STATIC
    5_src/gpioDriverUnit.c
)

target_include_directories(gpioDriver PUBLIC
    3_inc
    4_config
    5_src
)

target_link_libraries(gpioDriver PUBLIC
    bico_protocol_bridge_port
)
