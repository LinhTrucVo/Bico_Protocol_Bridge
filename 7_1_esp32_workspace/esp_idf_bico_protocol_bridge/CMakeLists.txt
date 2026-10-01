# The following lines of boilerplate have to be in your project's
# CMakeLists in this exact order for cmake to work correctly
cmake_minimum_required(VERSION 3.16)

add_definitions(
-DARDUINO_USB_MODE=1
-DARDUINO_USB_CDC_ON_BOOT=1
)

set(EXTRA_COMPONENT_DIRS
    ${CMAKE_CURRENT_LIST_DIR}/main/bico_protocol_bridge_swcomp
    ${CMAKE_CURRENT_LIST_DIR}/main/bico_protocol_bridge_port_esp32
)

include($ENV{IDF_PATH}/tools/cmake/project.cmake)
project(bico_protocol_bridge_esp32)
