#################################
What is this component about?
#################################

The Serial-to-I2C Application provides typed I2C write and read operations. It is called
by the Central Application Controller via RID 0x0400 (I2C Write) and RID 0x0401 (I2C Read).
Receives typed parameters and returns typed results.


#################################
Static structure
#################################

..  uml:: I2cServiceStaticStructure.puml

Public interfaces
#################################

..  sw-if:: I2cServiceUnit.h
    :id: SWIF_I2CSERVICE

    Public interface of I2cServiceUnit.

    ..  sw-ifelement:: I2cServiceUnit_Init()
        :id: SWIFE_I2CSERVICE_INIT
        :arguments:     return: I2cService_Status_t;

        Initializes the I2C Service and configures the I2C master driver with
        default settings.

        **Arguments:** None.

        **Return values:** BPB_I2CSERVICE_STATUS_OK on success, BPB_I2CSERVICE_STATUS_ERROR on failure.

        **Restrictions:** Must be called before any other I2C Service function.

    ..  sw-ifelement:: I2cServiceUnit_DeInit()
        :id: SWIFE_I2CSERVICE_DEINIT
        :arguments:     return: I2cService_Status_t;

        De-initializes the I2C Service and releases resources.

        **Arguments:** None.

        **Return values:** BPB_I2CSERVICE_STATUS_OK on success.

        **Restrictions:** None.

    ..  sw-ifelement:: I2cServiceUnit_Run()
        :id: SWIFE_I2CSERVICE_RUN
        :arguments:     return: I2cService_Status_t;

        Executes one cycle of the I2C processing loop (handles asynchronous transaction completion).

        **Arguments:** None.

        **Return values:** BPB_I2CSERVICE_STATUS_OK on success, BPB_I2CSERVICE_STATUS_NOT_INITIALIZED if called before Init.

        **Restrictions:** Must be called periodically from the main loop when asynchronous I2C transfers are in use.

    ..  sw-ifelement:: I2cServiceUnit_ProcessFrame()
        :id: SWIFE_I2CSERVICE_PROCESSFRAME
        :arguments:     return: I2cService_Status_t;    pFrame: const uint8_t*;    frameLength: uint16_t;    pResponse: uint8_t*;    pResponseLength: uint16_t*;

        Processes an incoming I2C command frame (write, read, or write-read) and fills the output
        buffer with the serialized response.

        **Arguments:**

        - **pFrame**: Pointer to the raw incoming frame bytes.
        - **frameLength**: Length of the incoming frame in bytes.
        - **pResponse**: Pointer to the output buffer for the serialized response.
        - **pResponseLength**: Pointer to receive the number of bytes written to the response buffer.

        **Return values:** BPB_I2CSERVICE_STATUS_OK on success, BPB_I2CSERVICE_STATUS_INVALID_PARAM for NULL pointers or zero length,
        BPB_I2CSERVICE_STATUS_ERROR on I2C transaction or serialization failure.

        **Restrictions:** The response buffer must be large enough to hold the maximum response frame.

#################################


Dynamic behaviour
#################################

* State machine diagram
..  uml:: I2cServiceStateMachine.puml

* Sequence diagram
..  uml:: I2cServiceSequenceDiagram.puml


#################################
Design choices
#################################
Description:
************
Provide hardware-abstracted I2C master read/write for the CAC dispatcher.

Assumptions and influencing factors:
************************************
* I2C master driver is initialized and available.
* Address is 7-bit, data buffer and length provided by caller.

Solutions list:
***************
Solution 1 - Separate Write/Read functions
Expose Write(addr, pData, len) and Read(addr, pData, len).

Solution 2 - Combined transfer function with direction parameter
Single function with read/write flag.

Solution evaluation:
********************
Separate functions match the RID mapping (0x0401=Write, 0x0402=Read) and are more explicit.

Final solution:
****************
Solution 1 selected for clarity and RID alignment.