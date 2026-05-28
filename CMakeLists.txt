cmake_minimum_required(VERSION 3.21.0)

project(BicoProtocolBridge)

# Enable testing
enable_testing()

# Add subdirectories for original template
add_subdirectory(3_swComp/function1/comp1)

#============================================================================
# Layer 1 - Hardware Drivers
#============================================================================
add_subdirectory(3_swComp/layer1Driver/adcDriver)
add_subdirectory(3_swComp/layer1Driver/gpioDriver)
add_subdirectory(3_swComp/layer1Driver/i2cMasterDriver)
add_subdirectory(3_swComp/layer1Driver/i2cSlaveDriver)
add_subdirectory(3_swComp/layer1Driver/nvmDriver)
add_subdirectory(3_swComp/layer1Driver/pwmDriver)
add_subdirectory(3_swComp/layer1Driver/serialDriver)
add_subdirectory(3_swComp/layer1Driver/spiMasterDriver)
add_subdirectory(3_swComp/layer1Driver/spiSlaveDriver)

#============================================================================
# Layer 2 - Services
#============================================================================
add_subdirectory(3_swComp/layer2Service/configService)
add_subdirectory(3_swComp/layer2Service/deserialize)
add_subdirectory(3_swComp/layer2Service/nvmService)
add_subdirectory(3_swComp/layer2Service/serialize)

#============================================================================
# Layer 3 - Applications
#============================================================================
add_subdirectory(3_swComp/layer3Application/centralAppController)
add_subdirectory(3_swComp/layer3Application/ANALOGAPP)
add_subdirectory(3_swComp/layer3Application/DIGITALAPP)
add_subdirectory(3_swComp/layer3Application/I2CAPP)
add_subdirectory(3_swComp/layer3Application/SPIAPP)


