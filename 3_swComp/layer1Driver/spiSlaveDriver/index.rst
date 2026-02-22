spiSlaveDriver Software Component
###################################

Introduction
************

The SPI Slave Driver provides hardware abstraction for the SPI communication protocol in slave mode.
It handles slave configuration and data reception/transmission under master control.


References
**********

Other relevant documents, e.g. ISO standards, whitepapers, etc.


Static architecture
*******************

Component
=========

..  swc:: spiSlaveDriver
    :provides: spiSlaveDriver.h – SPI slave initialization, mode configuration, and data transfer operations.
    :requires: Vendor HAL or register-level SPI peripheral access.

Public interfaces
=================

..  sw-if:: spiSlaveDriverUnit.h

    Public interface of spiSlaveDriverUnit.

    ..  sw-ifelement:: SpiSlaveDriverUnit_Init()
        :arguments:     return: SpiSlaveDriver_Status_t;    pConfig: const SpiSlaveDriver_Config_t*;

        Initializes the SPI slave peripheral with the provided configuration structure.

        **Arguments:**

        - **pConfig**: Pointer to SPI slave driver configuration structure (mode, bitOrder, dataFrameSize).

        **Return values:** SPI_SLAVE_STATUS_OK on success, SPI_SLAVE_STATUS_INVALID_PARAM for a NULL pointer.

        **Restrictions:** Must be called before any other SPI slave driver function.

    ..  sw-ifelement:: SpiSlaveDriverUnit_SetTxBuffer()
        :arguments:     return: SpiSlaveDriver_Status_t;    pData: const uint8_t*;    length: uint16_t;

        Sets the transmit buffer to be sent when the master initiates a read.

        **Arguments:**

        - **pData**: Pointer to the data buffer to transmit.
        - **length**: Number of bytes available in the transmit buffer.

        **Return values:** SPI_SLAVE_STATUS_OK on success, SPI_SLAVE_STATUS_INVALID_PARAM for a NULL pointer or zero length.

        **Restrictions:** The buffer must remain valid until the master read transaction is complete.

    ..  sw-ifelement:: SpiSlaveDriverUnit_SetRxBuffer()
        :arguments:     return: SpiSlaveDriver_Status_t;    pData: uint8_t*;    maxLength: uint16_t;

        Sets the receive buffer for incoming master writes.

        **Arguments:**

        - **pData**: Pointer to the buffer for received data.
        - **maxLength**: Maximum number of bytes the buffer can hold.

        **Return values:** SPI_SLAVE_STATUS_OK on success, SPI_SLAVE_STATUS_INVALID_PARAM for a NULL pointer or zero length.

        **Restrictions:** The buffer must remain valid until SpiSlaveDriverUnit_GetRxLength() is called and data is processed.

    ..  sw-ifelement:: SpiSlaveDriverUnit_GetRxLength()
        :arguments:     return: SpiSlaveDriver_Status_t;    pLength: uint16_t*;

        Returns the number of bytes received in the last master transaction.

        **Arguments:**

        - **pLength**: Pointer to store the number of bytes received.

        **Return values:** SPI_SLAVE_STATUS_OK on success, SPI_SLAVE_STATUS_INVALID_PARAM for a NULL pointer.

        **Restrictions:** None.

    ..  sw-ifelement:: SpiSlaveDriverUnit_IsSelected()
        :arguments:     return: SpiSlaveDriver_Status_t;    pIsSelected: bool*;

        Returns whether the chip-select line is currently asserted by the master.

        **Arguments:**

        - **pIsSelected**: Pointer to store the result; set to ``true`` if chip-select is asserted.

        **Return values:** SPI_SLAVE_STATUS_OK on success, SPI_SLAVE_STATUS_INVALID_PARAM for a NULL pointer.

        **Restrictions:** None.

    ..  sw-ifelement:: SpiSlaveDriverUnit_RegisterRxCallback()
        :arguments:     return: SpiSlaveDriver_Status_t;    callback: SpiSlaveDriver_RxCallback_t;

        Registers a callback invoked when a complete master-write is received.

        **Arguments:**

        - **callback**: Function pointer to the RX callback. Pass NULL to deregister.

        **Return values:** SPI_SLAVE_STATUS_OK on success.

        **Restrictions:** Callback is invoked from interrupt context and must be short and non-blocking.

    ..  sw-ifelement:: SpiSlaveDriverUnit_RegisterTxCallback()
        :arguments:     return: SpiSlaveDriver_Status_t;    callback: SpiSlaveDriver_TxCallback_t;

        Registers a callback invoked when the master requests a read; the callback shall fill the TX buffer.

        **Arguments:**

        - **callback**: Function pointer to the TX callback. Pass NULL to deregister.

        **Return values:** SPI_SLAVE_STATUS_OK on success.

        **Restrictions:** Callback is invoked from interrupt context; it must populate the TX buffer via SpiSlaveDriverUnit_SetTxBuffer() and be short and non-blocking.

    ..  sw-ifelement:: SpiSlaveDriverUnit_DeInit()
        :arguments:     return: SpiSlaveDriver_Status_t;

        De-initializes the SPI slave peripheral and releases resources.

        **Arguments:** None.

        **Return values:** SPI_SLAVE_STATUS_OK on success.

        **Restrictions:** None.


Requirements
************

.. toctree::
    :maxdepth: 1

    ./1_swcReq/spiSlaveDriverReq.rst


Design documentation
********************

.. toctree::
    :maxdepth: 1

    ./2_design/spiSlaveDriverComp.rst


Code documentation
******************

.. toctree::
    :maxdepth: 1

    ./2_design/spiSlaveDriverCfg.rst
    ./2_design/spiSlaveDriverUnit.rst
