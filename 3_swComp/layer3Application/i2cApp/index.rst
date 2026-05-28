I2CAPP Software Component
###################################

Introduction
************

The Serial-to-I2C Application handles I2C master transaction commands received from the host via
the serial interface. It configures the I2C master driver, executes write, read, and combined
write-read transactions to slave devices, and returns the result as a serialized response frame.


References
**********

Other relevant documents, e.g. ISO standards, whitepapers, etc.


Static architecture
*******************

Component
=========

..  swc:: I2CAPP
    :provides: I2CAPP.h – I2C master transaction execution for serial-to-I2C bridging.
    :requires: i2cMasterDriver.h, serialize.h, configService.h.

Public interfaces
=================

..  sw-if:: I2CAPPUnit.h

    Public interface of I2CAPPUnit.

    ..  sw-ifelement:: I2CAPPUnit_Init()
        :arguments:     return: I2CAPP_Status_t;

        Initializes the Serial-to-I2C application and configures the I2C master driver with
        default settings.

        **Arguments:** None.

        **Return values:** I2C_APP_STATUS_OK on success, I2C_APP_STATUS_ERROR on failure.

        **Restrictions:** Must be called before any other Serial-to-I2C function.

    ..  sw-ifelement:: I2CAPPUnit_DeInit()
        :arguments:     return: I2CAPP_Status_t;

        De-initializes the Serial-to-I2C application and releases resources.

        **Arguments:** None.

        **Return values:** I2C_APP_STATUS_OK on success.

        **Restrictions:** None.

    ..  sw-ifelement:: I2CAPPUnit_Run()
        :arguments:     return: I2CAPP_Status_t;

        Executes one cycle of the I2C processing loop (handles asynchronous transaction completion).

        **Arguments:** None.

        **Return values:** I2C_APP_STATUS_OK on success, I2C_APP_STATUS_NOT_INITIALIZED if called before Init.

        **Restrictions:** Must be called periodically from the main loop when asynchronous I2C transfers are in use.

    ..  sw-ifelement:: I2CAPPUnit_ProcessFrame()
        :arguments:     return: I2CAPP_Status_t;    pFrame: const uint8_t*;    frameLength: uint16_t;    pResponse: uint8_t*;    pResponseLength: uint16_t*;

        Processes an incoming I2C command frame (write, read, or write-read) and fills the output
        buffer with the serialized response.

        **Arguments:**

        - **pFrame**: Pointer to the raw incoming frame bytes.
        - **frameLength**: Length of the incoming frame in bytes.
        - **pResponse**: Pointer to the output buffer for the serialized response.
        - **pResponseLength**: Pointer to receive the number of bytes written to the response buffer.

        **Return values:** I2C_APP_STATUS_OK on success, I2C_APP_STATUS_INVALID_PARAM for NULL pointers or zero length,
        I2C_APP_STATUS_ERROR on I2C transaction or serialization failure.

        **Restrictions:** The response buffer must be large enough to hold the maximum response frame.


Requirements
************

.. toctree::
    :maxdepth: 1

    ./1_swcReq/I2CAPPReq.rst


Design documentation
********************

.. toctree::
    :maxdepth: 1

    ./2_design/I2CAPPComp.rst


Code documentation
******************

.. toctree::
    :maxdepth: 1

    ./2_design/I2CAPPCfg.rst
    ./2_design/I2CAPPUnit.rst
