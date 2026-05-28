#################################
What is this component about?
#################################

The Serial Driver provides a hardware abstraction layer (HAL wrapper) for UART/USART serial communication.
It manages serial port initialization, runtime configuration, interrupt/DMA-driven data transmission and reception,
callback notification, and error handling. It does not manage any internal buffering — ring buffer
management is the responsibility of the ComService (upper layer).

The component serves as the lowest communication layer in the Bico Protocol Bridge,
enabling the ComService (Layer 2) to perform serial data exchange independently of the underlying hardware platform.

#################################
Static structure
#################################

..  uml:: serialDriverStaticStructure.puml

The Serial Driver consists of:

- **SerialDriverUnit** – The main module providing the public API for all serial operations.
- **SerialDriver_Handle_t** – Internal state structure holding configuration, callbacks, and driver state.
- **SerialDriver_Config_t** – Configuration structure for baudrate, parity, stop bits, and data bits.
- **Vendor UART HAL** – External hardware abstraction provided by the MCU vendor (e.g., STM32 HAL).

#################################
Dynamic behaviour
#################################

* State machine diagram

..  uml:: serialDriverStateMachine.puml

The driver operates in five states:

- **Uninitialized** – Default state after reset. No API calls are accepted except Init.
- **Idle** – Initialized and ready for TX/RX operations.
- **TX Busy** – Actively transmitting data via interrupt or DMA.
- **RX Busy** – Actively receiving data via interrupt or DMA (continuous background reception).
- **Error** – A UART error occurred (overrun, framing, parity, noise). Requires re-initialization.

* Sequence diagram

..  uml:: serialDriverSequenceDiagram.puml

The sequence diagram covers:

- Initialization with parameter validation
- Interrupt-driven transmit and receive operations
- Timeout-based send/receive with abort mechanism
- Runtime reconfiguration
- Callback registration and invocation from ISR context
- Error detection and notification

#################################
Design choices
#################################

Description:
************
Provide a consistent, platform-independent UART access API that abstracts vendor-specific
HAL implementations while supporting both interrupt-driven and DMA-based data transfer modes.

Assumptions and influencing factors:
************************************
* UART peripheral supports both interrupt and DMA transfer modes.
* The vendor HAL provides callback mechanisms for TX complete, RX complete, and error events.
* The ComService (upper layer) polls for received data periodically and does not require real-time ISR-level response.
* Baud rates from 9600 to 921600 bps are required by the system.
* Multiple protocol bridges (SPI, I2C, Digital, Analog) share the same serial interface via ComService.
* Configuration parameters must be changeable at runtime without full system restart.

Solutions list:
***************

Solution 1 - HAL wrapper
=========================
Wrap vendor UART HAL providing interrupt/DMA-driven TX and RX.
Upper layer (ComService) manages its own ring buffers.
Driver only handles HAL initialization, data transfer, callbacks, and error reporting.

Solution 2 - Custom register-level UART driver
===============================================
Implement full UART driver directly accessing peripheral registers per platform.
Maximum control but requires separate implementation for each MCU family.

Solution 3 - Polling-based HAL wrapper
=======================================
Wrap vendor HAL with blocking polling calls.
Simplest implementation but blocks CPU during transfers, unsuitable for real-time requirements.

Solution evaluation:
********************

+------------------------------------------+------------+------------+------------+
| Criterion                                | Solution 1 | Solution 2 | Solution 3 |
+==========================================+============+============+============+
| Portability across MCU families          | High       | Low        | High       |
+------------------------------------------+------------+------------+------------+
| CPU efficiency (non-blocking)            | High       | High       | Low        |
+------------------------------------------+------------+------------+------------+
| Implementation effort                    | Medium     | High       | Low        |
+------------------------------------------+------------+------------+------------+
| Supports DMA and Interrupt modes         | Yes        | Yes        | No         |
+------------------------------------------+------------+------------+------------+
| Integration time                         | Short      | Long       | Short      |
+------------------------------------------+------------+------------+------------+
| Meets timing requirements (<1ms latency) | Yes        | Yes        | No         |
+------------------------------------------+------------+------------+------------+

Final solution:
****************
Solution 1 selected: HAL wrapper (no internal buffering).

Rationale:
- Provides portability across different MCU platforms by abstracting vendor HAL.
- Interrupt/DMA-driven operation ensures non-blocking behavior and meets <1ms latency requirement.
- Moderate implementation effort with good maintainability.
- Compile-time configuration flags (DMA, callbacks, flow control) allow feature scaling per deployment.
