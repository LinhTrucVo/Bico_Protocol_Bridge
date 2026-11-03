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

Public interfaces
#################################

..  sw-if:: serialDriverUnit.h
    :id: SWIF_SERIALDRIVER

    Public interface of serialDriverUnit.

    ..  sw-ifelement:: SerialDriverUnit_Init()
        :id: SWIFE_SERIALDRIVER_INIT
        :arguments:     return: SerialDriver_Status_t;    pConfig: const SerialDriver_Config_t*;

        Initializes the UART peripheral with the provided configuration structure.

        **Arguments:**

        - **pConfig**: Pointer to serial driver configuration structure (baudrate, parity, stopBits, dataBits).

        **Return values:** BPB_SERIAL_STATUS_OK on success, SERIAL_STATUS_INVALID_PARAM for a NULL pointer.

        **Restrictions:** Must be called before any other serial driver function.

    ..  sw-ifelement:: SerialDriverUnit_Configure()
        :id: SWIFE_SERIALDRIVER_CONFIGURE
        :arguments:     return: SerialDriver_Status_t;    baudrate: SerialDriver_Baudrate_t;    parity: SerialDriver_Parity_t;    stopBits: SerialDriver_StopBits_t;    dataBits: SerialDriver_DataBits_t;

        Reconfigures the serial port parameters at runtime.

        **Arguments:**

        - **baudrate**: Desired baud rate.
        - **parity**: Parity mode (BPB_SERIAL_PARITY_NONE, BPB_SERIAL_PARITY_EVEN, BPB_SERIAL_PARITY_ODD).
        - **stopBits**: Stop bit count (BPB_SERIAL_STOPBITS_1, BPB_SERIAL_STOPBITS_2).
        - **dataBits**: Word length (BPB_SERIAL_DATABITS_7, BPB_SERIAL_DATABITS_8, BPB_SERIAL_DATABITS_9).

        **Return values:** BPB_SERIAL_STATUS_OK on success, SERIAL_STATUS_INVALID_PARAM for unsupported parameter values.

        **Restrictions:** None.

    ..  sw-ifelement:: SerialDriverUnit_Send()
        :id: SWIFE_SERIALDRIVER_SEND
        :arguments:     return: SerialDriver_Status_t;    pData: const uint8_t*;    length: uint16_t;

        Transmits data using the default timeout.

        **Arguments:**

        - **pData**: Pointer to the data buffer to transmit.
        - **length**: Number of bytes to transmit.

        **Return values:** BPB_SERIAL_STATUS_OK on success, SERIAL_STATUS_INVALID_PARAM for a NULL pointer or zero length, BPB_SERIAL_STATUS_TIMEOUT on timeout.

        **Restrictions:** None.

    ..  sw-ifelement:: SerialDriverUnit_SendWithTimeout()
        :id: SWIFE_SERIALDRIVER_SENDWITHTIMEOUT
        :arguments:     return: SerialDriver_Status_t;    pData: const uint8_t*;    length: uint16_t;    timeoutMs: uint32_t;

        Transmits data with an explicit timeout.

        **Arguments:**

        - **pData**: Pointer to the data buffer to transmit.
        - **length**: Number of bytes to transmit.
        - **timeoutMs**: Maximum time in milliseconds to wait for completion.

        **Return values:** BPB_SERIAL_STATUS_OK on success, SERIAL_STATUS_INVALID_PARAM for a NULL pointer or zero length, BPB_SERIAL_STATUS_TIMEOUT if the operation exceeded the timeout.

        **Restrictions:** None.

    ..  sw-ifelement:: SerialDriverUnit_Receive()
        :id: SWIFE_SERIALDRIVER_RECEIVE
        :arguments:     return: SerialDriver_Status_t;    pData: uint8_t*;    maxLength: uint16_t;    pReceivedLength: uint16_t*;

        Receives data using the default timeout.

        **Arguments:**

        - **pData**: Pointer to the buffer for received data.
        - **maxLength**: Maximum number of bytes the buffer can hold.
        - **pReceivedLength**: Pointer to store the actual number of bytes received.

        **Return values:** BPB_SERIAL_STATUS_OK on success, SERIAL_STATUS_INVALID_PARAM for NULL pointers or zero maxLength, BPB_SERIAL_STATUS_TIMEOUT on timeout.

        **Restrictions:** None.

    ..  sw-ifelement:: SerialDriverUnit_ReceiveWithTimeout()
        :id: SWIFE_SERIALDRIVER_RECEIVEWITHTIMEOUT
        :arguments:     return: SerialDriver_Status_t;    pData: uint8_t*;    maxLength: uint16_t;    pReceivedLength: uint16_t*;    timeoutMs: uint32_t;

        Receives data with an explicit timeout.

        **Arguments:**

        - **pData**: Pointer to the buffer for received data.
        - **maxLength**: Maximum number of bytes the buffer can hold.
        - **pReceivedLength**: Pointer to store the actual number of bytes received.
        - **timeoutMs**: Maximum time in milliseconds to wait for data.

        **Return values:** BPB_SERIAL_STATUS_OK on success, SERIAL_STATUS_INVALID_PARAM for NULL pointers or zero maxLength, BPB_SERIAL_STATUS_TIMEOUT if the operation exceeded the timeout.

        **Restrictions:** None.

    ..  sw-ifelement:: SerialDriverUnit_GetAvailable()
        :id: SWIFE_SERIALDRIVER_GETAVAILABLE
        :arguments:     return: SerialDriver_Status_t;    pAvailable: uint16_t*;

        Returns the number of bytes available in the receive buffer.

        **Arguments:**

        - **pAvailable**: Pointer to store the count of available bytes.

        **Return values:** BPB_SERIAL_STATUS_OK on success, SERIAL_STATUS_INVALID_PARAM for a NULL pointer.

        **Restrictions:** None.

    ..  sw-ifelement:: SerialDriverUnit_FlushRx()
        :id: SWIFE_SERIALDRIVER_FLUSHRX
        :arguments:     return: SerialDriver_Status_t;

        Discards all data currently in the receive buffer.

        **Arguments:** None.

        **Return values:** BPB_SERIAL_STATUS_OK on success.

        **Restrictions:** None.

    ..  sw-ifelement:: SerialDriverUnit_FlushTx()
        :id: SWIFE_SERIALDRIVER_FLUSHTX
        :arguments:     return: SerialDriver_Status_t;

        Discards all data currently pending in the transmit buffer.

        **Arguments:** None.

        **Return values:** BPB_SERIAL_STATUS_OK on success.

        **Restrictions:** None.

    ..  sw-ifelement:: SerialDriverUnit_RegisterRxCallback()
        :id: SWIFE_SERIALDRIVER_REGISTERRXCALLBACK
        :arguments:     return: SerialDriver_Status_t;    callback: SerialDriver_RxCallback_t;

        Registers a callback invoked when received data is available.

        **Arguments:**

        - **callback**: Function pointer to the RX callback. Pass NULL to deregister.

        **Return values:** BPB_SERIAL_STATUS_OK on success.

        **Restrictions:** Callback is invoked from interrupt context and must be short and non-blocking.

    ..  sw-ifelement:: SerialDriverUnit_RegisterTxCallback()
        :id: SWIFE_SERIALDRIVER_REGISTERTXCALLBACK
        :arguments:     return: SerialDriver_Status_t;    callback: SerialDriver_TxCallback_t;

        Registers a callback invoked when a transmit operation completes.

        **Arguments:**

        - **callback**: Function pointer to the TX callback. Pass NULL to deregister.

        **Return values:** BPB_SERIAL_STATUS_OK on success.

        **Restrictions:** Callback is invoked from interrupt context and must be short and non-blocking.

    ..  sw-ifelement:: SerialDriverUnit_GetStatus()
        :id: SWIFE_SERIALDRIVER_GETSTATUS
        :arguments:     return: SerialDriver_Status_t;    pStatus: SerialDriver_Status_t*;

        Returns the current status of the serial driver.

        **Arguments:**

        - **pStatus**: Pointer to store the current driver status code.

        **Return values:** BPB_SERIAL_STATUS_OK on success, SERIAL_STATUS_INVALID_PARAM for a NULL pointer.

        **Restrictions:** None.

    ..  sw-ifelement:: SerialDriverUnit_DeInit()
        :id: SWIFE_SERIALDRIVER_DEINIT
        :arguments:     return: SerialDriver_Status_t;

        De-initializes the UART peripheral and releases resources.

        **Arguments:** None.

        **Return values:** BPB_SERIAL_STATUS_OK on success.

        **Restrictions:** None.

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
