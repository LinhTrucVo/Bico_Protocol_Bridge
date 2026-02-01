SW Function Architecture Template
#################################

This document describes the software function architecture for the Bico Protocol Bridge project.

Architecture Overview
*********************

The system is organized into a three-layer architecture, each with distinct responsibilities:

**Layer 1: Driver Layer**
  Low-level hardware abstraction that wraps vendor HAL APIs. This layer provides a consistent interface 
  for hardware peripherals (UART, I2C, SPI, ADC, GPIO, PWM, NVM) without exposing vendor-specific implementations.
  Drivers handle hardware initialization, configuration, and basic operations.

**Layer 2: Service Layer**
  Mid-level services that provide business logic and data processing. This layer includes:
  
  - **Protocol Services**: Command parsing (Serialize) and response formatting (Deserialize)
  - **Data Services**: Configuration management, calibration, and data conversion between formats
  - **Storage Services**: High-level NVM operations with integrity checking and wear leveling

**Layer 3: Application Layer**
  High-level application modules that implement the system features. The Central App Controller coordinates 
  all application modules:
  
  - SerialToAnalog: ADC channel management, sampling, threshold monitoring
  - SerialToDigital: GPIO control and PWM generation
  - SerialToI2C: I2C master/slave bridge operations
  - SerialToSPI: SPI master/slave bridge operations

Information Flow
****************

Commands flow upward through the layers:

1. Serial data → Serialize (parse to data structure)
2. Serialize → Central App Controller (dispatch commands)
3. Central App Controller → Application modules (execute)
4. Applications → Services (process data)
5. Services → Drivers (hardware operations)

Responses flow downward:

1. Drivers → Services → Applications
2. Applications → Central App Controller
3. Central App Controller → Deserialize (format response)
4. Deserialize → Serial transmission

Design Principles
*****************

- **Separation of Concerns**: Each layer has clear responsibilities without overlap
- **Hardware Independence**: Applications and services are independent of vendor HAL implementations
- **Modularity**: Functions can be developed, tested, and maintained independently
- **Scalability**: New features can be added by creating new application modules
- **Reusability**: Services and drivers can be shared across multiple applications

Layer 1: Driver Layer
**********************

..  toctree::
    :maxdepth: 1

    layer1_driver/adcDriver/index.rst
    layer1_driver/gpioDriver/index.rst
    layer1_driver/i2cMasterDriver/index.rst
    layer1_driver/i2cSlaveDriver/index.rst
    layer1_driver/nvmDriver/index.rst
    layer1_driver/pwmDriver/index.rst
    layer1_driver/serialDriver/index.rst
    layer1_driver/spiMasterDriver/index.rst
    layer1_driver/spiSlaveDriver/index.rst

Layer 2: Service Layer
**********************

..  toctree::
    :maxdepth: 1

    layer2_service/calibrationService/index.rst
    layer2_service/configService/index.rst
    layer2_service/dataConversionService/index.rst
    layer2_service/deserialize/index.rst
    layer2_service/nvmService/index.rst
    layer2_service/serialize/index.rst

Layer 3: Application Layer
***************************

..  toctree::
    :maxdepth: 1

    layer3_application/centralAppController/index.rst
    layer3_application/serialToAnalogApp/index.rst
    layer3_application/serialToDigitalApp/index.rst
    layer3_application/serialToI2CApp/index.rst
    layer3_application/serialToSPIApp/index.rst
