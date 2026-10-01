include(${CMAKE_CURRENT_LIST_DIR}/../../../../3_swComp/bicoProtocolBridgeSwComp.cmake)

idf_component_register(
    SRCS
        adcPortEsp32.c
        gpioPortEsp32.c
        i2cMasterPortEsp32.c
        i2cSlavePortEsp32.c
        nvmPortEsp32.c
        pwmPortEsp32.c
        serialPortEsp32.c
        spiMasterPortEsp32.c
        spiSlavePortEsp32.c
    PRIV_INCLUDE_DIRS
        ../config
        # Port headers (<drv>Port.h) are part of the software, the port does not link against it.
        ${BICO_PROTOCOL_BRIDGE_SWCOMP_INCLUDE_DIRS}
    PRIV_REQUIRES
        esp_adc
        esp_timer
        esp_driver_gpio
        esp_driver_uart
        esp_driver_i2c
        esp_driver_spi
        esp_driver_ledc
        nvs_flash
        freertos
)
