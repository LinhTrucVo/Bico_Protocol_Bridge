add_library(bpbHalFake STATIC
    ${CMAKE_CURRENT_SOURCE_DIR}/bpbHalFake.cpp
)

target_include_directories(bpbHalFake PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(bpbHalFake PUBLIC
    nlohmann_json::nlohmann_json
    GTest::gtest
)
