cmake_minimum_required(VERSION 3.21.0)

# ADC Driver Library
add_library(adcDriver STATIC
    5_src/adcDriverUnit.c
)

target_include_directories(adcDriver PUBLIC
    3_inc
    4_config
    5_src
)

target_link_libraries(adcDriver PUBLIC
    bico_protocol_bridge_port
)
