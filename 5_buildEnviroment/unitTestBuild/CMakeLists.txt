# JSON library for the HAL fakes (halFake)
include(FetchContent)
FetchContent_Declare(nlohmann_json
    URL https://github.com/nlohmann/json/releases/download/v3.11.3/json.tar.xz
    URL_HASH SHA256=d6c65aca6b1ed68e7a182f4757257b107ae403032760ed6ef121c9d55e81757d
)
FetchContent_MakeAvailable(nlohmann_json)

add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/halFake ${CMAKE_CURRENT_BINARY_DIR}/halFake)

# Add subdirectories
set(PRJ_DIR ../../)
# add_subdirectory(${PRJ_DIR}/3_1_swComp/layer1Driver/adcDriver/6_test/gtest ${CMAKE_CURRENT_BINARY_DIR}/adcDriver)
add_subdirectory(${PRJ_DIR}/3_1_swComp/layer1Driver/gpioDriver/6_test/gtest ${CMAKE_CURRENT_BINARY_DIR}/gpioDriver)
# add_subdirectory(${PRJ_DIR}/3_1_swComp/layer1Driver/i2cMasterDriver/6_test/gtest ${CMAKE_CURRENT_BINARY_DIR}/i2cMasterDriver)
# add_subdirectory(${PRJ_DIR}/3_1_swComp/layer1Driver/i2cSlaveDriver/6_test/gtest ${CMAKE_CURRENT_BINARY_DIR}/i2cSlaveDriver)
# add_subdirectory(${PRJ_DIR}/3_1_swComp/layer1Driver/nvmDriver/6_test/gtest ${CMAKE_CURRENT_BINARY_DIR}/nvmDriver)
# add_subdirectory(${PRJ_DIR}/3_1_swComp/layer1Driver/pwmDriver/6_test/gtest ${CMAKE_CURRENT_BINARY_DIR}/pwmDriver)
# add_subdirectory(${PRJ_DIR}/3_1_swComp/layer1Driver/serialDriver/6_test/gtest ${CMAKE_CURRENT_BINARY_DIR}/serialDriver)
# add_subdirectory(${PRJ_DIR}/3_1_swComp/layer1Driver/spiMasterDriver/6_test/gtest ${CMAKE_CURRENT_BINARY_DIR}/spiMasterDriver)
# add_subdirectory(${PRJ_DIR}/3_1_swComp/layer1Driver/spiSlaveDriver/6_test/gtest ${CMAKE_CURRENT_BINARY_DIR}/spiSlaveDriver)
# add_subdirectory(${PRJ_DIR}/3_1_swComp/layer2Service/configService/6_test/gtest ${CMAKE_CURRENT_BINARY_DIR}/configService)
# add_subdirectory(${PRJ_DIR}/3_1_swComp/layer2Service/deserialize/6_test/gtest ${CMAKE_CURRENT_BINARY_DIR}/deserialize)
# add_subdirectory(${PRJ_DIR}/3_1_swComp/layer2Service/nvmService/6_test/gtest ${CMAKE_CURRENT_BINARY_DIR}/nvmService)
# add_subdirectory(${PRJ_DIR}/3_1_swComp/layer2Service/serialize/6_test/gtest ${CMAKE_CURRENT_BINARY_DIR}/serialize)
# add_subdirectory(${PRJ_DIR}/3_1_swComp/layer3Application/centralAppController/6_test/gtest ${CMAKE_CURRENT_BINARY_DIR}/centralAppController)
