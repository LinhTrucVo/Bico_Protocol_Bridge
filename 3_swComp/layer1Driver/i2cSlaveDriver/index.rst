i2cSlaveDriver Software Component
###################################

Introduction
************

The I2C Slave Driver provides hardware abstraction for the I2C communication protocol in slave mode.
It handles slave address configuration and data reception/transmission under master control.


References
**********

Other relevant documents, e.g. ISO standards, whitepapers, etc.


Static architecture
*******************

Component
=========

..  swc:: i2cSlaveDriver
    :provides: i2cSlaveDriver.h – I2C slave initialization, address configuration, and data transfer operations.
    :requires: Vendor HAL or register-level I2C peripheral access.

Public interfaces
=================

..  sw-if:: i2cSlaveDriverUnit.h

    Public interface of i2cSlaveDriverUnit.

    ..  sw-ifelement:: I2cSlaveDriverUnit_Init()
        :arguments:     return: I2cSlaveDriver_Status_t;    pConfig: const I2cSlaveDriver_Config_t*;

        Initializes the I2C slave peripheral with own address and operating mode.

        **Arguments:**

        - **pConfig**: Pointer to I2C slave driver configuration structure (own address, address mode).

        **Return values:** I2C_SLAVE_STATUS_OK on success, I2C_SLAVE_STATUS_INVALID_PARAM for a NULL pointer.

        **Restrictions:** Must be called before any other I2C slave driver function.

    ..  sw-ifelement:: I2cSlaveDriverUnit_SetAddress()
        :arguments:     return: I2cSlaveDriver_Status_t;    address: I2cSlaveDriver_Address_t;

        Sets the I2C slave own address.

        **Arguments:**

        - **address**: The 7-bit or 10-bit address this slave shall respond to.

        **Return values:** I2C_SLAVE_STATUS_OK on success, I2C_SLAVE_STATUS_INVALID_PARAM for an out-of-range address.

        **Restrictions:** None.

    ..  sw-ifelement:: I2cSlaveDriverUnit_GetAddress()
        :arguments:     return: I2cSlaveDriver_Status_t;    pAddress: I2cSlaveDriver_Address_t*;

        Reads back the currently configured I2C slave own address.

        **Arguments:**

        - **pAddress**: Pointer to store the current slave address.

        **Return values:** I2C_SLAVE_STATUS_OK on success, I2C_SLAVE_STATUS_INVALID_PARAM for a NULL pointer.

        **Restrictions:** None.

    ..  sw-ifelement:: I2cSlaveDriverUnit_SetTxBuffer()
        :arguments:     return: I2cSlaveDriver_Status_t;    pData: const uint8_t*;    length: uint16_t;

        Sets the transmit buffer to be sent when addressed by a master.

        **Arguments:**

        - **pData**: Pointer to the data buffer to transmit.
        - **length**: Number of bytes available in the transmit buffer.

        **Return values:** I2C_SLAVE_STATUS_OK on success, I2C_SLAVE_STATUS_INVALID_PARAM for a NULL pointer or zero length.

        **Restrictions:** The buffer must remain valid until the master read transaction is complete.

    ..  sw-ifelement:: I2cSlaveDriverUnit_SetRxBuffer()
        :arguments:     return: I2cSlaveDriver_Status_t;    pData: uint8_t*;    maxLength: uint16_t;

        Sets the receive buffer for incoming master writes.

        **Arguments:**

        - **pData**: Pointer to the buffer for received data.
        - **maxLength**: Maximum number of bytes the buffer can hold.

        **Return values:** I2C_SLAVE_STATUS_OK on success, I2C_SLAVE_STATUS_INVALID_PARAM for a NULL pointer or zero length.

        **Restrictions:** The buffer must remain valid until I2cSlaveDriverUnit_GetRxLength() is called and data is processed.

    ..  sw-ifelement:: I2cSlaveDriverUnit_GetRxLength()
        :arguments:     return: I2cSlaveDriver_Status_t;    pLength: uint16_t*;

        Returns the number of bytes received in the last master-write transaction.

        **Arguments:**

        - **pLength**: Pointer to store the number of bytes received.

        **Return values:** I2C_SLAVE_STATUS_OK on success, I2C_SLAVE_STATUS_INVALID_PARAM for a NULL pointer.

        **Restrictions:** None.

    ..  sw-ifelement:: I2cSlaveDriverUnit_IsAddressed()
        :arguments:     return: I2cSlaveDriver_Status_t;    pIsAddressed: bool*;

        Returns whether the slave has been addressed by a master since the last check.

        **Arguments:**

        - **pIsAddressed**: Pointer to store the result; set to ``true`` if the slave was addressed.

        **Return values:** I2C_SLAVE_STATUS_OK on success, I2C_SLAVE_STATUS_INVALID_PARAM for a NULL pointer.

        **Restrictions:** None.

    ..  sw-ifelement:: I2cSlaveDriverUnit_RegisterRxCallback()
        :arguments:     return: I2cSlaveDriver_Status_t;    callback: I2cSlaveDriver_RxCallback_t;

        Registers a callback invoked when a complete master-write is received.

        **Arguments:**

        - **callback**: Function pointer to the RX callback. Pass NULL to deregister.

        **Return values:** I2C_SLAVE_STATUS_OK on success.

        **Restrictions:** Callback is invoked from interrupt context and must be short and non-blocking.

    ..  sw-ifelement:: I2cSlaveDriverUnit_RegisterTxCallback()
        :arguments:     return: I2cSlaveDriver_Status_t;    callback: I2cSlaveDriver_TxCallback_t;

        Registers a callback invoked when the master requests a read; the callback shall fill the TX buffer.

        **Arguments:**

        - **callback**: Function pointer to the TX callback. Pass NULL to deregister.

        **Return values:** I2C_SLAVE_STATUS_OK on success.

        **Restrictions:** Callback is invoked from interrupt context; it must populate the TX buffer via I2cSlaveDriverUnit_SetTxBuffer() and be short and non-blocking.

    ..  sw-ifelement:: I2cSlaveDriverUnit_RegisterAddressMatchCallback()
        :arguments:     return: I2cSlaveDriver_Status_t;    callback: I2cSlaveDriver_AddressMatchCallback_t;

        Registers a callback invoked when the slave address is matched on the bus.

        **Arguments:**

        - **callback**: Function pointer to the address-match callback. Pass NULL to deregister.

        **Return values:** I2C_SLAVE_STATUS_OK on success.

        **Restrictions:** Callback is invoked from interrupt context and must be short and non-blocking.

    ..  sw-ifelement:: I2cSlaveDriverUnit_DeInit()
        :arguments:     return: I2cSlaveDriver_Status_t;

        De-initializes the I2C slave peripheral and releases resources.

        **Arguments:** None.

        **Return values:** I2C_SLAVE_STATUS_OK on success.

        **Restrictions:** None.


Requirements
************

.. toctree::
    :maxdepth: 1

    ./1_swcReq/i2cSlaveDriverReq.rst


Design documentation
********************

.. toctree::
    :maxdepth: 1

    ./2_design/i2cSlaveDriverComp.rst


Code documentation
******************

.. toctree::
    :maxdepth: 1

    ./2_design/i2cSlaveDriverCfg.rst
    ./2_design/i2cSlaveDriverUnit.rst
