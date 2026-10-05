# Source and include lists of the hardware independent software, shared by every device workspace.
# Port implementations (<drv>Port*.c) are provided by the device workspace, not listed here.

set(_bicoSwCompRoot ${CMAKE_CURRENT_LIST_DIR})

set(_bicoSwCompComponents
    layer1Driver/adcDriver
    layer1Driver/gpioDriver
    layer1Driver/i2cMasterDriver
    layer1Driver/i2cSlaveDriver
    layer1Driver/nvmDriver
    layer1Driver/pwmDriver
    layer1Driver/serialDriver
    layer1Driver/spiMasterDriver
    layer1Driver/spiSlaveDriver
    layer2Service/analogService
    layer2Service/comService
    layer2Service/configService
    layer2Service/deserialize
    layer2Service/digitalService
    layer2Service/i2cService
    layer2Service/nvmService
    layer2Service/serialize
    layer2Service/spiService
    layer3Application/centralAppController
)

set(BICO_PROTOCOL_BRIDGE_SWCOMP_SOURCES "")
set(BICO_PROTOCOL_BRIDGE_SWCOMP_INCLUDE_DIRS "")

foreach(_comp IN LISTS _bicoSwCompComponents)
    file(GLOB _compSources "${_bicoSwCompRoot}/${_comp}/5_src/*.c")
    list(APPEND BICO_PROTOCOL_BRIDGE_SWCOMP_SOURCES ${_compSources})
    list(APPEND BICO_PROTOCOL_BRIDGE_SWCOMP_INCLUDE_DIRS
        ${_bicoSwCompRoot}/${_comp}/3_inc
        ${_bicoSwCompRoot}/${_comp}/4_config
        ${_bicoSwCompRoot}/${_comp}/5_src
    )
endforeach()
