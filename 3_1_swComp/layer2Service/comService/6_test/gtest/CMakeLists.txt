cmake_minimum_required(VERSION 3.21.0)

add_executable(testComService
    testComService.cpp
)

target_include_directories(testComService PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/..
    ${CMAKE_CURRENT_SOURCE_DIR}/../../3_inc
    ${CMAKE_CURRENT_SOURCE_DIR}/../../4_config
    ${CMAKE_CURRENT_SOURCE_DIR}/../../5_src
    ${CMAKE_CURRENT_SOURCE_DIR}/mock
    ${CMAKE_CURRENT_SOURCE_DIR}/fake
)

target_link_libraries(testComService PRIVATE
    gtest
    gtest_main
)
