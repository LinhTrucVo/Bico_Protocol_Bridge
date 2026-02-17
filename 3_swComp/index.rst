SW Function Component
#####################

This document describes the software function component architecture for the Bico Protocol Bridge project.

Architecture Overview
*********************

The system is organized into a three-layer architecture with 18 components total. 
Each component is responsible for specific functionality and follows a consistent structure.

Component Architecture Diagram
*******************************

..  uml:: ComponentArchitecture.puml

Layer Structure
***************

**Layer 1: Hardware Drivers (9 components)**
  Low-level hardware abstraction layer that provides vendor-independent interfaces to MCU peripherals.
  All drivers wrap vendor-specific HAL APIs.

**Layer 2: Services (4 components)**
  Mid-level services providing business logic, data processing, and protocol handling.
  Services are reusable across multiple applications.

**Layer 3: Applications (5 components)**
  High-level application modules implementing system features.
  The Central App Controller coordinates all application modules.

Component Count Summary
************************

- **Total Components**: 18
- **Layer 1 (Drivers)**: 9 components
- **Layer 2 (Services)**: 4 components  
- **Layer 3 (Applications)**: 5 components

Layer 1: Hardware Driver Components
************************************

..  toctree::
    :maxdepth: 1
    
    layer1Driver/adcDriver/index.rst
    layer1Driver/gpioDriver/index.rst
    layer1Driver/i2cMasterDriver/index.rst
    layer1Driver/i2cSlaveDriver/index.rst
    layer1Driver/nvmDriver/index.rst
    layer1Driver/pwmDriver/index.rst
    layer1Driver/serialDriver/index.rst
    layer1Driver/spiMasterDriver/index.rst
    layer1Driver/spiSlaveDriver/index.rst

**Driver Responsibilities:**

- Hardware initialization and configuration
- Register-level peripheral access
- Interrupt handling
- DMA configuration (where applicable)
- Error detection and reporting

Layer 2: Service Components
****************************

..  toctree::
    :maxdepth: 1
    
    layer2Service/configService/index.rst
    layer2Service/deserialize/index.rst
    layer2Service/nvmService/index.rst
    layer2Service/serialize/index.rst

**Service Responsibilities:**

- **configService**: Configuration parameter management and validation
- **deserialize**: Parse incoming serial commands to data structures
- **serialize**: Format outgoing responses from data structures
- **nvmService**: High-level NVM operations with integrity checking

Layer 3: Application Components
********************************

..  toctree::
    :maxdepth: 1
    
    layer3Application/centralAppController/index.rst
    layer3Application/serialToAnalogApp/index.rst
    layer3Application/serialToDigitalApp/index.rst
    layer3Application/serialToI2CApp/index.rst
    layer3Application/serialToSPIApp/index.rst

**Application Responsibilities:**

- **centralAppController**: Command dispatch and application coordination
- **serialToAnalogApp**: Multi-channel ADC management with raw data handling
- **serialToDigitalApp**: GPIO control and PWM generation
- **serialToI2CApp**: I2C master/slave bridge operations
- **serialToSPIApp**: SPI master/slave bridge operations

Component Structure
*******************

Each component follows a consistent directory structure:

.. code-block:: text

    componentName/
    ├── CMakeLists.txt          # Build configuration
    ├── 1_swcReq/               # Component requirements
    ├── 2_design/               # Design documentation
    ├── 3_inc/                  # Public header files
    ├── 4_config/               # Configuration headers
    ├── 5_src/                  # Implementation files
    ├── 6_test/                 # Unit tests
    ├── 7_tools/                # Development tools
    └── 8_misc/                 # Miscellaneous files

Dependencies
************

**Layer 3 → Layer 2 Dependencies:**

- All applications depend on: serialize, deserialize
- centralAppController depends on: configService
- Applications use services for data formatting and configuration

**Layer 2 → Layer 1 Dependencies:**

- deserialize, serialize → serialDriver
- configService, nvmService → nvmDriver

**Layer 1 → Hardware:**

- All drivers interface with MCU peripherals through vendor HAL

**Key Design Principles:**

- No upward dependencies (lower layers don't depend on higher layers)
- Applications are independent of each other
- Services are reusable across applications
- Drivers provide hardware abstraction

Data Flow
*********

**Command Processing Flow:**

1. Serial data received by serialDriver
2. deserialize service parses data to structures
3. centralAppController dispatches to appropriate application
4. Application executes command using services and drivers
5. serialize service formats response
6. serialDriver transmits response

**Raw Data Philosophy:**

The system works with raw hardware values:

- ADC: Raw counts (0-255, 0-4095, etc.)
- GPIO: Digital states (0/1)
- I2C/SPI: Raw byte streams
- No physical unit conversion or calibration in firmware

Build System
************

Components are built using CMake with a hierarchical structure:

- Root CMakeLists.txt includes all component subdirectories
- Each component has its own CMakeLists.txt
- Static libraries are created for each component
- Final executable links all component libraries

Implementation Status
**********************

**Current State:**

- ✅ Component structure defined
- ✅ Header files created with API declarations
- ✅ CMake build system configured
- ✅ Documentation framework established

**TODO:**

- ⚠️ Vendor-specific HAL implementation in drivers
- ⚠️ Service logic implementation
- ⚠️ Application state machine implementation
- ⚠️ Unit test development

For detailed implementation guidelines, see IMPLEMENTATION_GUIDE.md in the project root.
