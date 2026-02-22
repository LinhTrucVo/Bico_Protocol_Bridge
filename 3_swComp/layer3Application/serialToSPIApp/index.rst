serialToSPIApp Software Component
###################################

Introduction
************

The Serial-to-SPI Application handles SPI master transfer commands received from the host via the
serial interface. It configures the SPI master driver, executes full-duplex transfers to slave
devices, and returns the received data as a serialized response frame.


References
**********

Other relevant documents, e.g. ISO standards, whitepapers, etc.


Static architecture
*******************

Component
=========

..  swc:: serialToSPIApp
    :provides: serialToSPIApp.h – SPI master full-duplex transfer execution for serial-to-SPI bridging.
    :requires: spiMasterDriver.h, serialize.h, configService.h.

Public interfaces
=================

..  sw-if:: serialToSPIAppUnit.h

    Public interface of serialToSPIAppUnit.

    ..  sw-ifelement:: SerialToSPIAppUnit_Init()
        :arguments:     return: SerialToSPIApp_Status_t;

        Initializes the Serial-to-SPI application and configures the SPI master driver with
        default settings.

        **Arguments:** None.

        **Return values:** SERIAL_TO_SPI_APP_STATUS_OK on success, SERIAL_TO_SPI_APP_STATUS_ERROR on failure.

        **Restrictions:** Must be called before any other Serial-to-SPI function.

    ..  sw-ifelement:: SerialToSPIAppUnit_DeInit()
        :arguments:     return: SerialToSPIApp_Status_t;

        De-initializes the Serial-to-SPI application and releases resources.

        **Arguments:** None.

        **Return values:** SERIAL_TO_SPI_APP_STATUS_OK on success.

        **Restrictions:** None.

    ..  sw-ifelement:: SerialToSPIAppUnit_Run()
        :arguments:     return: SerialToSPIApp_Status_t;

        Executes one cycle of the SPI processing loop (handles asynchronous transfer completion).

        **Arguments:** None.

        **Return values:** SERIAL_TO_SPI_APP_STATUS_OK on success, SERIAL_TO_SPI_APP_STATUS_NOT_INITIALIZED if called before Init.

        **Restrictions:** Must be called periodically from the main loop when asynchronous SPI transfers are in use.

    ..  sw-ifelement:: SerialToSPIAppUnit_ProcessFrame()
        :arguments:     return: SerialToSPIApp_Status_t;    pFrame: const uint8_t*;    frameLength: uint16_t;    pResponse: uint8_t*;    pResponseLength: uint16_t*;

        Processes an incoming SPI transfer command frame and fills the output buffer with the
        serialized response containing the received SPI data.

        **Arguments:**

        - **pFrame**: Pointer to the raw incoming frame bytes.
        - **frameLength**: Length of the incoming frame in bytes.
        - **pResponse**: Pointer to the output buffer for the serialized response.
        - **pResponseLength**: Pointer to receive the number of bytes written to the response buffer.

        **Return values:** SERIAL_TO_SPI_APP_STATUS_OK on success, SERIAL_TO_SPI_APP_STATUS_INVALID_PARAM for NULL pointers or zero length,
        SERIAL_TO_SPI_APP_STATUS_ERROR on SPI transfer or serialization failure.

        **Restrictions:** The response buffer must be large enough to hold the maximum response frame.


Requirements
************

.. toctree::
    :maxdepth: 1

    ./1_swcReq/serialToSPIAppReq.rst


Design documentation
********************

.. toctree::
    :maxdepth: 1

    ./2_design/serialToSPIAppComp.rst


Code documentation
******************

.. toctree::
    :maxdepth: 1

    ./2_design/serialToSPIAppCfg.rst
    ./2_design/serialToSPIAppUnit.rst
