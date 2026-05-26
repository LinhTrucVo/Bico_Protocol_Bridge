SW Function Architecture
########################

This document describes the software function architecture for the Bico Protocol Bridge project.

Architecture Overview
*********************

The system is organized into a three-layer architecture, each with distinct responsibilities:

**Layer 1: Driver Layer**
  Low-level hardware abstraction that wraps vendor HAL APIs. This layer provides a consistent interface 
  for hardware peripherals (UART, I2C, SPI, ADC, GPIO, PWM, NVM) without exposing vendor-specific implementations.
  Drivers handle hardware initialization, configuration, and basic operations.

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

**Layer 2: Service Layer**
  Mid-level services that provide business logic and data processing. This layer includes:
  
  - **Protocol Services**: Command parsing (Serialize) and response formatting (Deserialize)
  - **Data Services**: Configuration management
  - **Storage Services**: High-level NVM operations with integrity checking and wear leveling

..  toctree::
    :maxdepth: 1

    layer2Service/configService/index.rst
    layer2Service/deserialize/index.rst
    layer2Service/nvmService/index.rst
    layer2Service/serialize/index.rst

**Layer 3: Application Layer**
  High-level application modules that implement the system features. The Central App Controller coordinates 
  all application modules:
  
  - SerialToAnalog: ADC channel management, sampling, threshold monitoring
  - SerialToDigital: GPIO control and PWM generation
  - SerialToI2C: I2C master/slave bridge operations
  - SerialToSPI: SPI master/slave bridge operations

..  toctree::
    :maxdepth: 1

    layer3Application/centralAppController/index.rst
    layer3Application/serialToAnalogApp/index.rst
    layer3Application/serialToDigitalApp/index.rst
    layer3Application/serialToI2CApp/index.rst
    layer3Application/serialToSPIApp/index.rst


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

Design Decision: Why CAC Routes Through App Modules
****************************************************

The Central App Controller (CAC) calls peripheral App modules (SerialToXxxApp)
rather than calling drivers directly.

**Current Design: CAC → SerialToXxxApp → Driver**

.. list-table::
   :header-rows: 1
   :widths: 25 75

   * - Benefit
     - Why it matters
   * - Encapsulation
     - The app module hides driver-specific details (e.g., CS pin management for SPI, master/slave mode switching for I2C). CAC doesn't need to know hardware wiring.
   * - Testability
     - You can unit-test the app module in isolation by mocking the driver. You can also test CAC by mocking the app module — two clean boundaries.
   * - Multi-step operations
     - Some operations require sequencing (assert CS → transmit → deassert CS, or check mode → switch mode → transfer). The app module owns that logic.
   * - State management
     - The app module tracks channel configs, pin modes, device states. If CAC called the driver directly, CAC would need to manage all that state itself.
   * - Scalability
     - Adding a new peripheral operation only touches the app module — CAC just adds one more RID mapping line.

**Alternative: CAC Calls Drivers Directly**

.. list-table::
   :header-rows: 1
   :widths: 30 70

   * - Benefit
     - Cost
   * - Fewer layers, slightly less code
     - CAC becomes a god object — owns UDS mapping, hardware sequencing, state management, error handling for ALL peripherals
   * - Marginally faster call path
     - Untestable in isolation; any driver change ripples into CAC
   * - —
     - Adding a new feature (e.g., I2C repeated start) means modifying CAC instead of a focused module

**Conclusion**: The app layer exists because peripheral operations are not single function calls —
they involve state, sequencing, and error recovery. Keeping that in a dedicated module keeps
CAC's job clean: *map UDS → typed API call → encode response*. Nothing more.
