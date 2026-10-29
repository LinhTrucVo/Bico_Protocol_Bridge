cmake_minimum_required(VERSION 3.21.0)
add_library(spiMasterDriver STATIC
    5_src/spiMasterDriverUnit.c
)
target_include_directories(spiMasterDriver PUBLIC
    3_inc
    4_config
    5_src
)
target_link_libraries(spiMasterDriver PUBLIC bico_protocol_bridge_port)
