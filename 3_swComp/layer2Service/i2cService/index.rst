I2cService Software Component
###################################

Introduction
************

The I2C Service handles I2C master transaction commands received from the host via
the serial interface. It configures the I2C master driver, executes write, read, and combined
write-read transactions to slave devices, and returns the result as a serialized response frame.


References
**********

Other relevant documents, e.g. ISO standards, whitepapers, etc.


Static architecture
*******************

Component
=========

..  swc:: I2cService
    :provides: I2cService.h – I2C master transaction execution for I2C Service bridging.
    :requires: i2cMasterDriver.h, serialize.h, configService.h.

Public interfaces
=================

..  sw-if:: I2cServiceUnit.h

    Public interface of I2cServiceUnit.

    ..  sw-ifelement:: I2cServiceUnit_Init()
        :arguments:     return: I2cService_Status_t;

        Initializes the I2C Service and configures the I2C master driver with
        default settings.

        **Arguments:** None.

        **Return values:** I2CSERVICE_STATUS_OK on success, I2CSERVICE_STATUS_ERROR on failure.

        **Restrictions:** Must be called before any other I2C Service function.

    ..  sw-ifelement:: I2cServiceUnit_DeInit()
        :arguments:     return: I2cService_Status_t;

        De-initializes the I2C Service and releases resources.

        **Arguments:** None.

        **Return values:** I2CSERVICE_STATUS_OK on success.

        **Restrictions:** None.

    ..  sw-ifelement:: I2cServiceUnit_Run()
        :arguments:     return: I2cService_Status_t;

        Executes one cycle of the I2C processing loop (handles asynchronous transaction completion).

        **Arguments:** None.

        **Return values:** I2CSERVICE_STATUS_OK on success, I2CSERVICE_STATUS_NOT_INITIALIZED if called before Init.

        **Restrictions:** Must be called periodically from the main loop when asynchronous I2C transfers are in use.

    ..  sw-ifelement:: I2cServiceUnit_ProcessFrame()
        :arguments:     return: I2cService_Status_t;    pFrame: const uint8_t*;    frameLength: uint16_t;    pResponse: uint8_t*;    pResponseLength: uint16_t*;

        Processes an incoming I2C command frame (write, read, or write-read) and fills the output
        buffer with the serialized response.

        **Arguments:**

        - **pFrame**: Pointer to the raw incoming frame bytes.
        - **frameLength**: Length of the incoming frame in bytes.
        - **pResponse**: Pointer to the output buffer for the serialized response.
        - **pResponseLength**: Pointer to receive the number of bytes written to the response buffer.

        **Return values:** I2CSERVICE_STATUS_OK on success, I2CSERVICE_STATUS_INVALID_PARAM for NULL pointers or zero length,
        I2CSERVICE_STATUS_ERROR on I2C transaction or serialization failure.

        **Restrictions:** The response buffer must be large enough to hold the maximum response frame.


Requirements
************

.. toctree::
    :maxdepth: 1

    ./1_swcReq/I2cServiceReq.rst


Design documentation
********************

.. toctree::
    :maxdepth: 1

    ./2_design/I2cServiceComp.rst


Code documentation
******************

.. toctree::
    :maxdepth: 1

    ./2_design/I2cServiceCfg.rst
    ./2_design/I2cServiceUnit.rst
