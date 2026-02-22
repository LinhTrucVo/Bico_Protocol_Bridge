spiMasterDriver Software Component
####################################

Introduction
************

The SPI Master Driver provides hardware abstraction for the SPI communication protocol in master mode.
It handles bus initialization, clock configuration, chip select management, and data transfer operations.


References
**********

Other relevant documents, e.g. ISO standards, whitepapers, etc.


Static architecture
*******************

Component
=========

..  swc:: spiMasterDriver
    :provides: spiMasterDriver.h – SPI master bus initialization, clock configuration, chip select management, and data transfer.
    :requires: Vendor HAL or register-level SPI peripheral access.

Public interfaces
=================

..  sw-if:: spiMasterDriverUnit.h

    Public interface of spiMasterDriverUnit.

    ..  sw-ifelement:: SpiMasterDriverUnit_Init()
        :arguments:     return: SpiMasterDriver_Status_t;    pConfig: const SpiMasterDriver_Config_t*;

        Initializes the SPI master peripheral with the provided configuration structure.

        **Arguments:**

        - **pConfig**: Pointer to SPI master driver configuration structure (clockSpeed, mode, bitOrder).

        **Return values:** SPI_MASTER_STATUS_OK on success, SPI_MASTER_STATUS_INVALID_PARAM for a NULL pointer.

        **Restrictions:** Must be called before any other SPI master driver function.

    ..  sw-ifelement:: SpiMasterDriverUnit_Configure()
        :arguments:     return: SpiMasterDriver_Status_t;    clockSpeed: uint32_t;    mode: SpiMasterDriver_Mode_t;    bitOrder: SpiMasterDriver_BitOrder_t;

        Reconfigures clock speed, SPI mode, and bit order at runtime.

        **Arguments:**

        - **clockSpeed**: Desired SPI clock speed in Hz.
        - **mode**: SPI mode (SPI_MODE_0, SPI_MODE_1, SPI_MODE_2, SPI_MODE_3).
        - **bitOrder**: Bit transmission order (SPI_BIT_ORDER_MSB_FIRST or SPI_BIT_ORDER_LSB_FIRST).

        **Return values:** SPI_MASTER_STATUS_OK on success, SPI_MASTER_STATUS_INVALID_PARAM for unsupported values.

        **Restrictions:** None.

    ..  sw-ifelement:: SpiMasterDriverUnit_SelectChip()
        :arguments:     return: SpiMasterDriver_Status_t;    cs: SpiMasterDriver_ChipSelect_t;

        Asserts (activates) the specified chip-select line.

        **Arguments:**

        - **cs**: Chip-select identifier to assert.

        **Return values:** SPI_MASTER_STATUS_OK on success, SPI_MASTER_STATUS_INVALID_PARAM for an invalid chip-select.

        **Restrictions:** None.

    ..  sw-ifelement:: SpiMasterDriverUnit_DeselectChip()
        :arguments:     return: SpiMasterDriver_Status_t;    cs: SpiMasterDriver_ChipSelect_t;

        Deasserts (releases) the specified chip-select line.

        **Arguments:**

        - **cs**: Chip-select identifier to release.

        **Return values:** SPI_MASTER_STATUS_OK on success, SPI_MASTER_STATUS_INVALID_PARAM for an invalid chip-select.

        **Restrictions:** None.

    ..  sw-ifelement:: SpiMasterDriverUnit_Transmit()
        :arguments:     return: SpiMasterDriver_Status_t;    pData: const uint8_t*;    length: uint16_t;

        Transmits data over SPI (receive data is discarded).

        **Arguments:**

        - **pData**: Pointer to the data buffer to transmit.
        - **length**: Number of bytes to transmit.

        **Return values:** SPI_MASTER_STATUS_OK on success, SPI_MASTER_STATUS_INVALID_PARAM for a NULL pointer or zero length, SPI_MASTER_STATUS_TIMEOUT on timeout.

        **Restrictions:** Chip-select must be asserted before calling this function.

    ..  sw-ifelement:: SpiMasterDriverUnit_Receive()
        :arguments:     return: SpiMasterDriver_Status_t;    pData: uint8_t*;    length: uint16_t;

        Receives data over SPI (dummy bytes are transmitted).

        **Arguments:**

        - **pData**: Pointer to the buffer for received data.
        - **length**: Number of bytes to receive.

        **Return values:** SPI_MASTER_STATUS_OK on success, SPI_MASTER_STATUS_INVALID_PARAM for a NULL pointer or zero length, SPI_MASTER_STATUS_TIMEOUT on timeout.

        **Restrictions:** Chip-select must be asserted before calling this function.

    ..  sw-ifelement:: SpiMasterDriverUnit_TransmitReceive()
        :arguments:     return: SpiMasterDriver_Status_t;    pTxData: const uint8_t*;    pRxData: uint8_t*;    length: uint16_t;

        Performs a full-duplex SPI transfer.

        **Arguments:**

        - **pTxData**: Pointer to the data buffer to transmit.
        - **pRxData**: Pointer to the buffer for received data.
        - **length**: Number of bytes to transfer.

        **Return values:** SPI_MASTER_STATUS_OK on success, SPI_MASTER_STATUS_INVALID_PARAM for NULL pointers or zero length, SPI_MASTER_STATUS_TIMEOUT on timeout.

        **Restrictions:** Chip-select must be asserted before calling this function.

    ..  sw-ifelement:: SpiMasterDriverUnit_TransmitWithTimeout()
        :arguments:     return: SpiMasterDriver_Status_t;    pData: const uint8_t*;    length: uint16_t;    timeoutMs: uint32_t;

        Transmits data with an explicit timeout.

        **Arguments:**

        - **pData**: Pointer to the data buffer to transmit.
        - **length**: Number of bytes to transmit.
        - **timeoutMs**: Maximum time in milliseconds to wait for completion.

        **Return values:** SPI_MASTER_STATUS_OK on success, SPI_MASTER_STATUS_INVALID_PARAM for a NULL pointer or zero length, SPI_MASTER_STATUS_TIMEOUT if the operation exceeded the timeout.

        **Restrictions:** Chip-select must be asserted before calling this function.

    ..  sw-ifelement:: SpiMasterDriverUnit_IsBusy()
        :arguments:     return: SpiMasterDriver_Status_t;    pIsBusy: bool*;

        Returns whether the SPI bus is currently busy.

        **Arguments:**

        - **pIsBusy**: Pointer to store the result; set to ``true`` if the bus is busy.

        **Return values:** SPI_MASTER_STATUS_OK on success, SPI_MASTER_STATUS_INVALID_PARAM for a NULL pointer.

        **Restrictions:** None.

    ..  sw-ifelement:: SpiMasterDriverUnit_RegisterCallback()
        :arguments:     return: SpiMasterDriver_Status_t;    callback: SpiMasterDriver_Callback_t;

        Registers a callback invoked on transfer completion.

        **Arguments:**

        - **callback**: Function pointer to the callback. Pass NULL to deregister.

        **Return values:** SPI_MASTER_STATUS_OK on success.

        **Restrictions:** Callbacks are invoked from interrupt context; they must be short and non-blocking.

    ..  sw-ifelement:: SpiMasterDriverUnit_DeInit()
        :arguments:     return: SpiMasterDriver_Status_t;

        De-initializes the SPI master peripheral and releases resources.

        **Arguments:** None.

        **Return values:** SPI_MASTER_STATUS_OK on success.

        **Restrictions:** None.


Requirements
************

.. toctree::
    :maxdepth: 1

    ./1_swcReq/spiMasterDriverReq.rst


Design documentation
********************

.. toctree::
    :maxdepth: 1

    ./2_design/spiMasterDriverComp.rst


Code documentation
******************

.. toctree::
    :maxdepth: 1

    ./2_design/spiMasterDriverCfg.rst
    ./2_design/spiMasterDriverUnit.rst
