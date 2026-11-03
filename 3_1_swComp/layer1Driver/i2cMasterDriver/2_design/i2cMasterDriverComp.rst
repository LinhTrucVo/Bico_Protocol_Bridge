#################################
What is this component about?
#################################

The I2C Master Driver abstracts I2C master transactions and configuration.


#################################
Static structure
#################################

..  uml:: i2cMasterDriverStaticStructure.puml

Public interfaces
#################################

..  sw-if:: i2cMasterDriverUnit.h
    :id: SWIF_I2CMASTERDRIVER

    Public interface of i2cMasterDriverUnit.

    ..  sw-ifelement:: I2cMasterDriverUnit_Init()
        :id: SWIFE_I2CMASTERDRIVER_INIT
        :arguments:     return: I2cMasterDriver_Status_t;    pConfig: const I2cMasterDriver_Config_t*;

        Initializes the I2C master peripheral with the provided configuration structure.

        **Arguments:**

        - **pConfig**: Pointer to I2C master driver configuration structure (bus speed, address mode, timeout).

        **Return values:** BPB_I2C_MASTER_STATUS_OK on success, BPB_I2C_MASTER_STATUS_INVALID_PARAM for a NULL pointer.

        **Restrictions:** Must be called before any other I2C master driver function.

    ..  sw-ifelement:: I2cMasterDriverUnit_SetSpeed()
        :id: SWIFE_I2CMASTERDRIVER_SETSPEED
        :arguments:     return: I2cMasterDriver_Status_t;    speed: I2cMasterDriver_Speed_t;

        Sets the I2C bus clock speed (standard, fast, fast-plus, high-speed).

        **Arguments:**

        - **speed**: Desired bus speed (BPB_I2C_SPEED_STANDARD, BPB_I2C_SPEED_FAST, BPB_I2C_SPEED_FAST_PLUS, I2C_SPEED_HIGH).

        **Return values:** BPB_I2C_MASTER_STATUS_OK on success, BPB_I2C_MASTER_STATUS_INVALID_PARAM for an unsupported speed value.

        **Restrictions:** None.

    ..  sw-ifelement:: I2cMasterDriverUnit_Write()
        :id: SWIFE_I2CMASTERDRIVER_WRITE
        :arguments:     return: I2cMasterDriver_Status_t;    address: I2cMasterDriver_Address_t;    pData: const uint8_t*;    length: uint16_t;

        Transmits data to a slave device using the default timeout.

        **Arguments:**

        - **address**: 7-bit or 10-bit I2C slave device address.
        - **pData**: Pointer to the data buffer to transmit.
        - **length**: Number of bytes to transmit.

        **Return values:** BPB_I2C_MASTER_STATUS_OK on success, BPB_I2C_MASTER_STATUS_INVALID_PARAM for a NULL pointer or zero length, BPB_I2C_MASTER_STATUS_NACK if the slave did not acknowledge, BPB_I2C_MASTER_STATUS_TIMEOUT on timeout.

        **Restrictions:** None.

    ..  sw-ifelement:: I2cMasterDriverUnit_WriteWithTimeout()
        :id: SWIFE_I2CMASTERDRIVER_WRITEWITHTIMEOUT
        :arguments:     return: I2cMasterDriver_Status_t;    address: I2cMasterDriver_Address_t;    pData: const uint8_t*;    length: uint16_t;    timeoutMs: uint32_t;

        Transmits data to a slave device with an explicit timeout.

        **Arguments:**

        - **address**: 7-bit or 10-bit I2C slave device address.
        - **pData**: Pointer to the data buffer to transmit.
        - **length**: Number of bytes to transmit.
        - **timeoutMs**: Maximum time in milliseconds to wait for completion.

        **Return values:** BPB_I2C_MASTER_STATUS_OK on success, BPB_I2C_MASTER_STATUS_INVALID_PARAM for a NULL pointer or zero length, BPB_I2C_MASTER_STATUS_NACK if the slave did not acknowledge, BPB_I2C_MASTER_STATUS_TIMEOUT if the operation exceeded the timeout.

        **Restrictions:** None.

    ..  sw-ifelement:: I2cMasterDriverUnit_Read()
        :id: SWIFE_I2CMASTERDRIVER_READ
        :arguments:     return: I2cMasterDriver_Status_t;    address: I2cMasterDriver_Address_t;    pData: uint8_t*;    length: uint16_t;

        Receives data from a slave device using the default timeout.

        **Arguments:**

        - **address**: 7-bit or 10-bit I2C slave device address.
        - **pData**: Pointer to the buffer for received data.
        - **length**: Number of bytes to receive.

        **Return values:** BPB_I2C_MASTER_STATUS_OK on success, BPB_I2C_MASTER_STATUS_INVALID_PARAM for a NULL pointer or zero length, BPB_I2C_MASTER_STATUS_NACK if no slave acknowledged, BPB_I2C_MASTER_STATUS_TIMEOUT on timeout.

        **Restrictions:** None.

    ..  sw-ifelement:: I2cMasterDriverUnit_ReadWithTimeout()
        :id: SWIFE_I2CMASTERDRIVER_READWITHTIMEOUT
        :arguments:     return: I2cMasterDriver_Status_t;    address: I2cMasterDriver_Address_t;    pData: uint8_t*;    length: uint16_t;    timeoutMs: uint32_t;

        Receives data from a slave device with an explicit timeout.

        **Arguments:**

        - **address**: 7-bit or 10-bit I2C slave device address.
        - **pData**: Pointer to the buffer for received data.
        - **length**: Number of bytes to receive.
        - **timeoutMs**: Maximum time in milliseconds to wait for completion.

        **Return values:** BPB_I2C_MASTER_STATUS_OK on success, BPB_I2C_MASTER_STATUS_INVALID_PARAM for a NULL pointer or zero length, BPB_I2C_MASTER_STATUS_NACK if no slave acknowledged, BPB_I2C_MASTER_STATUS_TIMEOUT if the operation exceeded the timeout.

        **Restrictions:** None.

    ..  sw-ifelement:: I2cMasterDriverUnit_WriteRead()
        :id: SWIFE_I2CMASTERDRIVER_WRITEREAD
        :arguments:     return: I2cMasterDriver_Status_t;    address: I2cMasterDriver_Address_t;    pWriteData: const uint8_t*;    writeLength: uint16_t;    pReadData: uint8_t*;    readLength: uint16_t;

        Performs a combined write-then-read transaction (repeated start).

        **Arguments:**

        - **address**: 7-bit or 10-bit I2C slave device address.
        - **pWriteData**: Pointer to the data buffer to write (e.g. register address).
        - **writeLength**: Number of bytes to write.
        - **pReadData**: Pointer to the buffer for received data.
        - **readLength**: Number of bytes to read.

        **Return values:** BPB_I2C_MASTER_STATUS_OK on success, BPB_I2C_MASTER_STATUS_INVALID_PARAM for NULL pointers or zero lengths, BPB_I2C_MASTER_STATUS_NACK if no acknowledge was received.

        **Restrictions:** None.

    ..  sw-ifelement:: I2cMasterDriverUnit_WriteRegister()
        :id: SWIFE_I2CMASTERDRIVER_WRITEREGISTER
        :arguments:     return: I2cMasterDriver_Status_t;    address: I2cMasterDriver_Address_t;    regAddress: uint8_t;    pData: const uint8_t*;    length: uint16_t;

        Writes data to a specific register address of a slave device.

        **Arguments:**

        - **address**: 7-bit or 10-bit I2C slave device address.
        - **regAddress**: Register address byte sent before the data payload.
        - **pData**: Pointer to the data buffer to write.
        - **length**: Number of data bytes to write.

        **Return values:** BPB_I2C_MASTER_STATUS_OK on success, BPB_I2C_MASTER_STATUS_INVALID_PARAM for a NULL pointer or zero length, BPB_I2C_MASTER_STATUS_NACK if no acknowledge was received.

        **Restrictions:** None.

    ..  sw-ifelement:: I2cMasterDriverUnit_ReadRegister()
        :id: SWIFE_I2CMASTERDRIVER_READREGISTER
        :arguments:     return: I2cMasterDriver_Status_t;    address: I2cMasterDriver_Address_t;    regAddress: uint8_t;    pData: uint8_t*;    length: uint16_t;

        Reads data from a specific register address of a slave device.

        **Arguments:**

        - **address**: 7-bit or 10-bit I2C slave device address.
        - **regAddress**: Register address byte sent before switching to read.
        - **pData**: Pointer to the buffer for received data.
        - **length**: Number of data bytes to read.

        **Return values:** BPB_I2C_MASTER_STATUS_OK on success, BPB_I2C_MASTER_STATUS_INVALID_PARAM for a NULL pointer or zero length, BPB_I2C_MASTER_STATUS_NACK if no acknowledge was received.

        **Restrictions:** None.

    ..  sw-ifelement:: I2cMasterDriverUnit_ScanBus()
        :id: SWIFE_I2CMASTERDRIVER_SCANBUS
        :arguments:     return: I2cMasterDriver_Status_t;    pFoundAddresses: I2cMasterDriver_Address_t*;    maxAddresses: uint8_t;    pNumFound: uint8_t*;

        Scans the I2C bus and returns addresses of responding slave devices.

        **Arguments:**

        - **pFoundAddresses**: Pointer to an array that receives discovered device addresses.
        - **maxAddresses**: Maximum number of addresses the array can hold.
        - **pNumFound**: Pointer to store the actual number of responding devices found.

        **Return values:** BPB_I2C_MASTER_STATUS_OK on success, BPB_I2C_MASTER_STATUS_INVALID_PARAM for NULL pointers or zero maxAddresses.

        **Restrictions:** May take significant time proportional to the address range scanned.

    ..  sw-ifelement:: I2cMasterDriverUnit_IsBusy()
        :id: SWIFE_I2CMASTERDRIVER_ISBUSY
        :arguments:     return: I2cMasterDriver_Status_t;    pIsBusy: bool*;

        Returns whether the I2C bus is currently busy.

        **Arguments:**

        - **pIsBusy**: Pointer to store the result; set to ``true`` if the bus is busy.

        **Return values:** BPB_I2C_MASTER_STATUS_OK on success, BPB_I2C_MASTER_STATUS_INVALID_PARAM for a NULL pointer.

        **Restrictions:** None.

    ..  sw-ifelement:: I2cMasterDriverUnit_RegisterCallback()
        :id: SWIFE_I2CMASTERDRIVER_REGISTERCALLBACK
        :arguments:     return: I2cMasterDriver_Status_t;    callback: I2cMasterDriver_Callback_t;

        Registers a callback invoked on transfer completion.

        **Arguments:**

        - **callback**: Function pointer to the callback. Pass NULL to deregister.

        **Return values:** BPB_I2C_MASTER_STATUS_OK on success.

        **Restrictions:** Callbacks are invoked from interrupt context; they must be short and non-blocking.

    ..  sw-ifelement:: I2cMasterDriverUnit_DeInit()
        :id: SWIFE_I2CMASTERDRIVER_DEINIT
        :arguments:     return: I2cMasterDriver_Status_t;

        De-initializes the I2C master peripheral and releases resources.

        **Arguments:** None.

        **Return values:** BPB_I2C_MASTER_STATUS_OK on success.

        **Restrictions:** None.

#################################


Dynamic behaviour
#################################

* State machine diagram
..  uml:: i2cMasterDriverStateMachine.puml

* Sequence diagram
..  uml:: i2cMasterDriverSequenceDiagram.puml


#################################
Design chooices
#################################
Description:
************
Provide a portable I2C master abstraction layer.

Assumptions and influencing factors:
************************************
* Vendor HAL handles low-level timing.

Solutions list:
***************
Solution 1 - HAL wrapper
Wrap vendor I2C HAL.

Solution 2 - Bit-banging
Implement software I2C for portability.

Solution evaluation:
********************
HAL wrapper offers better performance and timing accuracy.

Final solution:
****************
Solution 1 selected for performance and portability.
