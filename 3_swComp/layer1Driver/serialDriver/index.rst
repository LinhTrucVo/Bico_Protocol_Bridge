serialDriver Software Component
################################

Introduction
************

The Serial Driver provides hardware abstraction for UART/USART serial communication.
It handles serial port initialization, baud rate configuration, and data transmission/reception operations.


References
**********

Other relevant documents, e.g. ISO standards, whitepapers, etc.


Static architecture
*******************

Component
=========

..  swc:: serialDriver
    :provides: serialDriver.h – Serial port initialization, baud rate configuration, and data transmit/receive operations.
    :requires: Vendor HAL or register-level UART/USART peripheral access.

Public interfaces
=================

..  sw-if:: serialDriverUnit.h

    Public interface of serialDriverUnit.

    ..  sw-ifelement:: SerialDriverUnit_Init()
        :arguments:     return: SerialDriver_Status_t;    pConfig: const SerialDriver_Config_t*;

        Initializes the UART peripheral with the provided configuration structure.

        **Arguments:**

        - **pConfig**: Pointer to serial driver configuration structure (baudrate, parity, stopBits, dataBits).

        **Return values:** SERIAL_STATUS_OK on success, SERIAL_STATUS_INVALID_PARAM for a NULL pointer.

        **Restrictions:** Must be called before any other serial driver function.

    ..  sw-ifelement:: SerialDriverUnit_Configure()
        :arguments:     return: SerialDriver_Status_t;    baudrate: SerialDriver_Baudrate_t;    parity: SerialDriver_Parity_t;    stopBits: SerialDriver_StopBits_t;    dataBits: SerialDriver_DataBits_t;

        Reconfigures the serial port parameters at runtime.

        **Arguments:**

        - **baudrate**: Desired baud rate.
        - **parity**: Parity mode (SERIAL_PARITY_NONE, SERIAL_PARITY_EVEN, SERIAL_PARITY_ODD).
        - **stopBits**: Stop bit count (SERIAL_STOPBITS_1, SERIAL_STOPBITS_2).
        - **dataBits**: Word length (SERIAL_DATABITS_7, SERIAL_DATABITS_8, SERIAL_DATABITS_9).

        **Return values:** SERIAL_STATUS_OK on success, SERIAL_STATUS_INVALID_PARAM for unsupported parameter values.

        **Restrictions:** None.

    ..  sw-ifelement:: SerialDriverUnit_Send()
        :arguments:     return: SerialDriver_Status_t;    pData: const uint8_t*;    length: uint16_t;

        Transmits data using the default timeout.

        **Arguments:**

        - **pData**: Pointer to the data buffer to transmit.
        - **length**: Number of bytes to transmit.

        **Return values:** SERIAL_STATUS_OK on success, SERIAL_STATUS_INVALID_PARAM for a NULL pointer or zero length, SERIAL_STATUS_TIMEOUT on timeout.

        **Restrictions:** None.

    ..  sw-ifelement:: SerialDriverUnit_SendWithTimeout()
        :arguments:     return: SerialDriver_Status_t;    pData: const uint8_t*;    length: uint16_t;    timeoutMs: uint32_t;

        Transmits data with an explicit timeout.

        **Arguments:**

        - **pData**: Pointer to the data buffer to transmit.
        - **length**: Number of bytes to transmit.
        - **timeoutMs**: Maximum time in milliseconds to wait for completion.

        **Return values:** SERIAL_STATUS_OK on success, SERIAL_STATUS_INVALID_PARAM for a NULL pointer or zero length, SERIAL_STATUS_TIMEOUT if the operation exceeded the timeout.

        **Restrictions:** None.

    ..  sw-ifelement:: SerialDriverUnit_Receive()
        :arguments:     return: SerialDriver_Status_t;    pData: uint8_t*;    maxLength: uint16_t;    pReceivedLength: uint16_t*;

        Receives data using the default timeout.

        **Arguments:**

        - **pData**: Pointer to the buffer for received data.
        - **maxLength**: Maximum number of bytes the buffer can hold.
        - **pReceivedLength**: Pointer to store the actual number of bytes received.

        **Return values:** SERIAL_STATUS_OK on success, SERIAL_STATUS_INVALID_PARAM for NULL pointers or zero maxLength, SERIAL_STATUS_TIMEOUT on timeout.

        **Restrictions:** None.

    ..  sw-ifelement:: SerialDriverUnit_ReceiveWithTimeout()
        :arguments:     return: SerialDriver_Status_t;    pData: uint8_t*;    maxLength: uint16_t;    pReceivedLength: uint16_t*;    timeoutMs: uint32_t;

        Receives data with an explicit timeout.

        **Arguments:**

        - **pData**: Pointer to the buffer for received data.
        - **maxLength**: Maximum number of bytes the buffer can hold.
        - **pReceivedLength**: Pointer to store the actual number of bytes received.
        - **timeoutMs**: Maximum time in milliseconds to wait for data.

        **Return values:** SERIAL_STATUS_OK on success, SERIAL_STATUS_INVALID_PARAM for NULL pointers or zero maxLength, SERIAL_STATUS_TIMEOUT if the operation exceeded the timeout.

        **Restrictions:** None.

    ..  sw-ifelement:: SerialDriverUnit_GetAvailable()
        :arguments:     return: SerialDriver_Status_t;    pAvailable: uint16_t*;

        Returns the number of bytes available in the receive buffer.

        **Arguments:**

        - **pAvailable**: Pointer to store the count of available bytes.

        **Return values:** SERIAL_STATUS_OK on success, SERIAL_STATUS_INVALID_PARAM for a NULL pointer.

        **Restrictions:** None.

    ..  sw-ifelement:: SerialDriverUnit_FlushRx()
        :arguments:     return: SerialDriver_Status_t;

        Discards all data currently in the receive buffer.

        **Arguments:** None.

        **Return values:** SERIAL_STATUS_OK on success.

        **Restrictions:** None.

    ..  sw-ifelement:: SerialDriverUnit_FlushTx()
        :arguments:     return: SerialDriver_Status_t;

        Discards all data currently pending in the transmit buffer.

        **Arguments:** None.

        **Return values:** SERIAL_STATUS_OK on success.

        **Restrictions:** None.

    ..  sw-ifelement:: SerialDriverUnit_RegisterRxCallback()
        :arguments:     return: SerialDriver_Status_t;    callback: SerialDriver_RxCallback_t;

        Registers a callback invoked when received data is available.

        **Arguments:**

        - **callback**: Function pointer to the RX callback. Pass NULL to deregister.

        **Return values:** SERIAL_STATUS_OK on success.

        **Restrictions:** Callback is invoked from interrupt context and must be short and non-blocking.

    ..  sw-ifelement:: SerialDriverUnit_RegisterTxCallback()
        :arguments:     return: SerialDriver_Status_t;    callback: SerialDriver_TxCallback_t;

        Registers a callback invoked when a transmit operation completes.

        **Arguments:**

        - **callback**: Function pointer to the TX callback. Pass NULL to deregister.

        **Return values:** SERIAL_STATUS_OK on success.

        **Restrictions:** Callback is invoked from interrupt context and must be short and non-blocking.

    ..  sw-ifelement:: SerialDriverUnit_GetStatus()
        :arguments:     return: SerialDriver_Status_t;    pStatus: SerialDriver_Status_t*;

        Returns the current status of the serial driver.

        **Arguments:**

        - **pStatus**: Pointer to store the current driver status code.

        **Return values:** SERIAL_STATUS_OK on success, SERIAL_STATUS_INVALID_PARAM for a NULL pointer.

        **Restrictions:** None.

    ..  sw-ifelement:: SerialDriverUnit_DeInit()
        :arguments:     return: SerialDriver_Status_t;

        De-initializes the UART peripheral and releases resources.

        **Arguments:** None.

        **Return values:** SERIAL_STATUS_OK on success.

        **Restrictions:** None.


Requirements
************

.. toctree::
    :maxdepth: 1

    ./1_swcReq/serialDriverReq.rst


Design documentation
********************

.. toctree::
    :maxdepth: 1

    ./2_design/serialDriverComp.rst


Code documentation
******************

.. toctree::
    :maxdepth: 1

    ./2_design/serialDriverCfg.rst
    ./2_design/serialDriverUnit.rst
