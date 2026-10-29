cmake_minimum_required(VERSION 3.21.0)

add_library(i2cMasterDriver STATIC
    5_src/i2cMasterDriverUnit.c
)

target_include_directories(i2cMasterDriver PUBLIC
    3_inc
    4_config
    5_src
)

target_link_libraries(i2cMasterDriver PUBLIC bico_protocol_bridge_port)
