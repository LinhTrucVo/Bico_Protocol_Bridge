#################################
What is this component about?
#################################

The I2C Slave Driver abstracts I2C slave operation and buffered transfers.


#################################
Static structure
#################################

..  uml:: i2cSlaveDriverStaticStructure.puml

Public interfaces
#################################

..  sw-if:: i2cSlaveDriverUnit.h
    :id: SWIF_I2CSLAVEDRIVER

    Public interface of i2cSlaveDriverUnit.

    ..  sw-ifelement:: I2cSlaveDriverUnit_Init()
        :id: SWIFE_I2CSLAVEDRIVER_INIT
        :arguments:     return: I2cSlaveDriver_Status_t;    pConfig: const I2cSlaveDriver_Config_t*;

        Initializes the I2C slave peripheral with own address and operating mode.

        **Arguments:**

        - **pConfig**: Pointer to I2C slave driver configuration structure (own address, address mode).

        **Return values:** BPB_I2C_SLAVE_STATUS_OK on success, I2C_SLAVE_STATUS_INVALID_PARAM for a NULL pointer.

        **Restrictions:** Must be called before any other I2C slave driver function.

    ..  sw-ifelement:: I2cSlaveDriverUnit_SetAddress()
        :id: SWIFE_I2CSLAVEDRIVER_SETADDRESS
        :arguments:     return: I2cSlaveDriver_Status_t;    address: I2cSlaveDriver_Address_t;

        Sets the I2C slave own address.

        **Arguments:**

        - **address**: The 7-bit or 10-bit address this slave shall respond to.

        **Return values:** BPB_I2C_SLAVE_STATUS_OK on success, I2C_SLAVE_STATUS_INVALID_PARAM for an out-of-range address.

        **Restrictions:** None.

    ..  sw-ifelement:: I2cSlaveDriverUnit_GetAddress()
        :id: SWIFE_I2CSLAVEDRIVER_GETADDRESS
        :arguments:     return: I2cSlaveDriver_Status_t;    pAddress: I2cSlaveDriver_Address_t*;

        Reads back the currently configured I2C slave own address.

        **Arguments:**

        - **pAddress**: Pointer to store the current slave address.

        **Return values:** BPB_I2C_SLAVE_STATUS_OK on success, I2C_SLAVE_STATUS_INVALID_PARAM for a NULL pointer.

        **Restrictions:** None.

    ..  sw-ifelement:: I2cSlaveDriverUnit_SetTxBuffer()
        :id: SWIFE_I2CSLAVEDRIVER_SETTXBUFFER
        :arguments:     return: I2cSlaveDriver_Status_t;    pData: const uint8_t*;    length: uint16_t;

        Sets the transmit buffer to be sent when addressed by a master.

        **Arguments:**

        - **pData**: Pointer to the data buffer to transmit.
        - **length**: Number of bytes available in the transmit buffer.

        **Return values:** BPB_I2C_SLAVE_STATUS_OK on success, I2C_SLAVE_STATUS_INVALID_PARAM for a NULL pointer or zero length.

        **Restrictions:** The buffer must remain valid until the master read transaction is complete.

    ..  sw-ifelement:: I2cSlaveDriverUnit_SetRxBuffer()
        :id: SWIFE_I2CSLAVEDRIVER_SETRXBUFFER
        :arguments:     return: I2cSlaveDriver_Status_t;    pData: uint8_t*;    maxLength: uint16_t;

        Sets the receive buffer for incoming master writes.

        **Arguments:**

        - **pData**: Pointer to the buffer for received data.
        - **maxLength**: Maximum number of bytes the buffer can hold.

        **Return values:** BPB_I2C_SLAVE_STATUS_OK on success, I2C_SLAVE_STATUS_INVALID_PARAM for a NULL pointer or zero length.

        **Restrictions:** The buffer must remain valid until I2cSlaveDriverUnit_GetRxLength() is called and data is processed.

    ..  sw-ifelement:: I2cSlaveDriverUnit_GetRxLength()
        :id: SWIFE_I2CSLAVEDRIVER_GETRXLENGTH
        :arguments:     return: I2cSlaveDriver_Status_t;    pLength: uint16_t*;

        Returns the number of bytes received in the last master-write transaction.

        **Arguments:**

        - **pLength**: Pointer to store the number of bytes received.

        **Return values:** BPB_I2C_SLAVE_STATUS_OK on success, I2C_SLAVE_STATUS_INVALID_PARAM for a NULL pointer.

        **Restrictions:** None.

    ..  sw-ifelement:: I2cSlaveDriverUnit_IsAddressed()
        :id: SWIFE_I2CSLAVEDRIVER_ISADDRESSED
        :arguments:     return: I2cSlaveDriver_Status_t;    pIsAddressed: bool*;

        Returns whether the slave has been addressed by a master since the last check.

        **Arguments:**

        - **pIsAddressed**: Pointer to store the result; set to ``true`` if the slave was addressed.

        **Return values:** BPB_I2C_SLAVE_STATUS_OK on success, I2C_SLAVE_STATUS_INVALID_PARAM for a NULL pointer.

        **Restrictions:** None.

    ..  sw-ifelement:: I2cSlaveDriverUnit_RegisterRxCallback()
        :id: SWIFE_I2CSLAVEDRIVER_REGISTERRXCALLBACK
        :arguments:     return: I2cSlaveDriver_Status_t;    callback: I2cSlaveDriver_RxCallback_t;

        Registers a callback invoked when a complete master-write is received.

        **Arguments:**

        - **callback**: Function pointer to the RX callback. Pass NULL to deregister.

        **Return values:** BPB_I2C_SLAVE_STATUS_OK on success.

        **Restrictions:** Callback is invoked from interrupt context and must be short and non-blocking.

    ..  sw-ifelement:: I2cSlaveDriverUnit_RegisterTxCallback()
        :id: SWIFE_I2CSLAVEDRIVER_REGISTERTXCALLBACK
        :arguments:     return: I2cSlaveDriver_Status_t;    callback: I2cSlaveDriver_TxCallback_t;

        Registers a callback invoked when the master requests a read; the callback shall fill the TX buffer.

        **Arguments:**

        - **callback**: Function pointer to the TX callback. Pass NULL to deregister.

        **Return values:** BPB_I2C_SLAVE_STATUS_OK on success.

        **Restrictions:** Callback is invoked from interrupt context; it must populate the TX buffer via I2cSlaveDriverUnit_SetTxBuffer() and be short and non-blocking.

    ..  sw-ifelement:: I2cSlaveDriverUnit_RegisterAddressMatchCallback()
        :id: SWIFE_I2CSLAVEDRIVER_REGISTERADDRESSMATCHCALLBACK
        :arguments:     return: I2cSlaveDriver_Status_t;    callback: I2cSlaveDriver_AddressMatchCallback_t;

        Registers a callback invoked when the slave address is matched on the bus.

        **Arguments:**

        - **callback**: Function pointer to the address-match callback. Pass NULL to deregister.

        **Return values:** BPB_I2C_SLAVE_STATUS_OK on success.

        **Restrictions:** Callback is invoked from interrupt context and must be short and non-blocking.

    ..  sw-ifelement:: I2cSlaveDriverUnit_DeInit()
        :id: SWIFE_I2CSLAVEDRIVER_DEINIT
        :arguments:     return: I2cSlaveDriver_Status_t;

        De-initializes the I2C slave peripheral and releases resources.

        **Arguments:** None.

        **Return values:** BPB_I2C_SLAVE_STATUS_OK on success.

        **Restrictions:** None.

#################################


Dynamic behaviour
#################################

* State machine diagram
..  uml:: i2cSlaveDriverStateMachine.puml

* Sequence diagram
..  uml:: i2cSlaveDriverSequenceDiagram.puml


#################################
Design chooices
#################################
Description:
************
Provide a portable I2C slave abstraction with buffered transfers.

Assumptions and influencing factors:
************************************
* Vendor HAL provides slave address matching and callbacks.

Solutions list:
***************
Solution 1 - HAL wrapper
Wrap vendor I2C slave HAL.

Solution 2 - Minimal ISR implementation
Implement full ISR logic per platform.

Solution evaluation:
********************
HAL wrapper reduces platform-specific ISR complexity.

Final solution:
****************
Solution 1 selected for portability.
