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
  Mid-level services that provide more business logic and data processing that are not provided by the drivers. This layer includes:
  
  - **Protocol Services**: Command parsing (Serialize) and response formatting (Deserialize)
  - **Data Services**: Configuration management
  - **Storage Services**: High-level NVM operations with integrity checking and wear leveling
  - **Peripheral Services**: ADC, GPIO/PWM, I2C, and SPI operations with state management

..  toctree::
    :maxdepth: 1

    layer2Service/configService/index.rst
    layer2Service/deserialize/index.rst
    layer2Service/nvmService/index.rst
    layer2Service/serialize/index.rst
    layer2Service/analogService/index.rst
    layer2Service/digitalService/index.rst
    layer2Service/i2cService/index.rst
    layer2Service/spiService/index.rst

**Layer 3: Application Layer**
  High-level application modules that implement the system features. The Central App Controller coordinates 
  all service modules.

..  toctree::
    :maxdepth: 1

    layer3Application/centralAppController/index.rst


Information Flow
****************

Commands flow through the layers:

1. Serial data → ComService (buffered reception via callbacks)
2. ComService → Central App Controller (frame extraction with prefix/postfix)
3. Central App Controller → Deserialize (parse UDS request)
4. Central App Controller → Peripheral Services (execute typed API calls)
5. Peripheral Services → Drivers (hardware operations)

Responses flow back:

1. Drivers → Peripheral Services → Central App Controller
2. Central App Controller → Serialize (format UDS response)
3. Central App Controller → ComService (framed transmission)

Design Principles
*****************

- **Separation of Concerns**: Each layer has clear responsibilities without overlap
- **Hardware Independence**: Applications and services are independent of vendor HAL implementations
- **Modularity**: Functions can be developed, tested, and maintained independently
- **Scalability**: New features can be added by creating new application modules
- **Reusability**: Services and drivers can be shared across multiple applications

Design Decision: Why CAC Routes Through Peripheral Services
************************************************************

The Central App Controller (CAC) calls peripheral Service modules
rather than calling drivers directly.

**Current Design: CAC → Peripheral Service → Driver**

.. list-table::
   :header-rows: 1
   :widths: 25 75

   * - Benefit
     - Why it matters
   * - Encapsulation
     - the service module hides driver-specific details (e.g., CS pin management for SPI, master/slave mode switching for I2C). CAC doesn't need to know hardware wiring.
   * - Testability
     - You can unit-test the service module in isolation by mocking the driver. You can also test CAC by mocking the service module — two clean boundaries.
   * - Multi-step operations
     - Some operations require sequencing (assert CS → transmit → deassert CS, or check mode → switch mode → transfer). the service module owns that logic.
   * - State management
     - the service module tracks channel configs, pin modes, device states. If CAC called the driver directly, CAC would need to manage all that state itself.
   * - Scalability
     - Adding a new peripheral operation only touches the service module — CAC just adds one more RID mapping line.

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

**Conclusion**: The peripheral service layer exists because peripheral operations are not single function calls —
they involve state, sequencing, and error recovery. Keeping that in a dedicated service module keeps
CAC's job clean: *map UDS → typed API call → encode response*. Nothing more.
