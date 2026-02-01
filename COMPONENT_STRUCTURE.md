# Bico Protocol Bridge - Component Structure

## Overview
This document provides an overview of all software components created based on the project architecture.

## Component Organization

### Layer 1 - Hardware Drivers (HAL Abstraction)
Located in: `3_swComp/layer1Driver/`

1. **adcDriver** - Analog-to-Digital Converter Driver
   - Supports multiple ADC channels
   - Provides blocking and non-blocking conversion modes
   - Vendor HAL abstraction layer (TODO: Implement vendor-specific code)

2. **gpioDriver** - General Purpose Input/Output Driver
   - Pin configuration (input/output/alternate/analog)
   - Digital read/write operations
   - Pin toggle functionality

3. **i2cMasterDriver** - I2C Master Mode Driver
   - I2C write operations
   - I2C read operations
   - Combined write-read operations

4. **i2cSlaveDriver** - I2C Slave Mode Driver
   - Slave device implementation
   - Data reception from master
   - Data transmission to master

5. **nvmDriver** - Non-Volatile Memory Driver
   - Flash/EEPROM abstraction
   - Read/write/erase operations
   - Data persistence management

6. **pwmDriver** - Pulse Width Modulation Driver
   - PWM signal generation
   - Duty cycle control
   - Frequency configuration

7. **serialDriver** - Serial/UART Driver
   - UART communication
   - Configurable baud rate
   - Transmit and receive operations

8. **spiMasterDriver** - SPI Master Mode Driver
   - SPI communication in master mode
   - Data transfer operations
   - Chip select management

9. **spiSlaveDriver** - SPI Slave Mode Driver
   - SPI communication in slave mode
   - Data exchange with master

### Layer 2 - Services (Business Logic)
Located in: `3_swComp/layer2Service/`

1. **calibrationService** - Sensor Calibration Service
   - Calibration data management
   - Calibration algorithms
   - Offset and gain correction

2. **configService** - Configuration Service
   - System configuration management
   - Parameter storage and retrieval
   - Configuration validation

3. **dataConversionService** - Data Conversion Service
   - Unit conversions
   - Data format transformations
   - Scaling operations

4. **deserialize** - Deserialization Service
   - Binary data parsing
   - Protocol frame decoding
   - Data extraction from serial streams

5. **nvmService** - NVM Service
   - High-level NVM operations
   - Configuration persistence
   - Data integrity checks

6. **serialize** - Serialization Service
   - Data packaging
   - Protocol frame encoding
   - Serial stream preparation

### Layer 3 - Applications (Application Logic)
Located in: `3_swComp/layer3Application/`

1. **centralAppController** - Central Application Controller
   - Main application coordinator
   - State machine management
   - Inter-module communication

2. **serialToAnalogApp** - Serial to Analog Conversion Application
   - Receives commands via serial
   - Controls analog output (DAC/PWM)
   - Implements SerialToAnalog feature requirement

3. **serialToDigitalApp** - Serial to Digital I/O Application
   - Receives commands via serial
   - Controls digital GPIO pins
   - Implements SerialToDigital feature requirement

4. **serialToI2CApp** - Serial to I2C Bridge Application
   - Serial to I2C protocol bridge
   - I2C device control via serial commands
   - Implements SerialToI2C feature requirement

5. **serialToSPIApp** - Serial to SPI Bridge Application
   - Serial to SPI protocol bridge
   - SPI device control via serial commands
   - Implements SerialToSPI feature requirement

## Component Template Structure

Each component follows the standardized template structure:

```
<componentName>/
├── CMakeLists.txt              # Build configuration
├── 1_swcReq/                   # Requirements documentation
│   └── <componentName>Req.rst
├── 2_design/                   # Design documentation
│   └── <componentName>Comp.rst
├── 3_inc/                      # Public header files
│   └── <componentName>.h
├── 4_config/                   # Configuration files
│   └── <componentName>Cfg.h
├── 5_src/                      # Source implementation
│   ├── <componentName>Unit.h
│   └── <componentName>Unit.c
├── 6_test/                     # Test files
│   └── gtest/
│       ├── CMakeLists.txt
│       └── test<ComponentName>.cpp
├── 7_tools/                    # Tools and utilities
│   └── index.rst
└── 8_misc/                     # Miscellaneous
    └── index.rst
```

## Implementation Status

### ✅ Completed
- All Layer 1 driver component structures created
- All Layer 2 service component structures created
- All Layer 3 application component structures created
- Root CMakeLists.txt updated with all components
- Test infrastructure setup for all components

### ⚠️ TODO - Vendor-Specific Implementation
All driver components contain TODO comments indicating where vendor-specific HAL code should be implemented:

- ADC HAL initialization and operations
- GPIO HAL configuration and operations
- I2C HAL master/slave operations
- NVM HAL read/write/erase operations
- PWM HAL timer configuration
- Serial/UART HAL transmit/receive
- SPI HAL master/slave operations

### ⚠️ TODO - Service Logic Implementation
Service layer components have placeholder implementations. Business logic needs to be implemented:

- Calibration algorithms
- Configuration management logic
- Data conversion formulas
- Serialization/deserialization protocols
- NVM service high-level operations

### ⚠️ TODO - Application Logic Implementation
Application layer components have state machine structure but need specific logic:

- Serial command parsing
- Protocol implementation for each bridge type
- State machine behavior
- Error handling and recovery

## Build System

The project uses CMake as the build system. To build:

```bash
mkdir build
cd build
cmake ..
cmake --build .
```

To run tests:
```bash
ctest
```

## Architecture Alignment

This component structure aligns with the architecture defined in:
- `1_requirement/` - Feature requirements
- `2_architecture/fucntionView/` - Functional architecture

Each component maps to a function block in the architecture:
- Layer 1 maps to hardware abstraction functions
- Layer 2 maps to service functions
- Layer 3 maps to application functions

## Next Steps

1. Implement vendor-specific HAL code for target microcontroller
2. Implement business logic for services
3. Implement application-specific protocols
4. Write comprehensive unit tests
5. Perform integration testing
6. Document detailed design decisions

## Notes

- All components use consistent naming conventions
- Each component is independently testable
- Clear separation between layers enables modular development
- TODO markers indicate where implementation is needed
- Template structure promotes consistency across the project
