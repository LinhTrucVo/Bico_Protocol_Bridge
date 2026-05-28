SPIAPP Software Component
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

..  swc:: SPIAPP
    :provides: SPIAPP.h – SPI master full-duplex transfer execution for serial-to-SPI bridging.
    :requires: spiMasterDriver.h, serialize.h, configService.h.

Public interfaces
=================

..  sw-if:: SPIAPPUnit.h

    Public interface of SPIAPPUnit.

    ..  sw-ifelement:: SPIAPPUnit_Init()
        :arguments:     return: SPIAPP_Status_t;

        Initializes the Serial-to-SPI application and configures the SPI master driver with
        default settings.

        **Arguments:** None.

        **Return values:** SPI_APP_STATUS_OK on success, SPI_APP_STATUS_ERROR on failure.

        **Restrictions:** Must be called before any other Serial-to-SPI function.

    ..  sw-ifelement:: SPIAPPUnit_DeInit()
        :arguments:     return: SPIAPP_Status_t;

        De-initializes the Serial-to-SPI application and releases resources.

        **Arguments:** None.

        **Return values:** SPI_APP_STATUS_OK on success.

        **Restrictions:** None.

    ..  sw-ifelement:: SPIAPPUnit_Run()
        :arguments:     return: SPIAPP_Status_t;

        Executes one cycle of the SPI processing loop (handles asynchronous transfer completion).

        **Arguments:** None.

        **Return values:** SPI_APP_STATUS_OK on success, SPI_APP_STATUS_NOT_INITIALIZED if called before Init.

        **Restrictions:** Must be called periodically from the main loop when asynchronous SPI transfers are in use.

    ..  sw-ifelement:: SPIAPPUnit_ProcessFrame()
        :arguments:     return: SPIAPP_Status_t;    pFrame: const uint8_t*;    frameLength: uint16_t;    pResponse: uint8_t*;    pResponseLength: uint16_t*;

        Processes an incoming SPI transfer command frame and fills the output buffer with the
        serialized response containing the received SPI data.

        **Arguments:**

        - **pFrame**: Pointer to the raw incoming frame bytes.
        - **frameLength**: Length of the incoming frame in bytes.
        - **pResponse**: Pointer to the output buffer for the serialized response.
        - **pResponseLength**: Pointer to receive the number of bytes written to the response buffer.

        **Return values:** SPI_APP_STATUS_OK on success, SPI_APP_STATUS_INVALID_PARAM for NULL pointers or zero length,
        SPI_APP_STATUS_ERROR on SPI transfer or serialization failure.

        **Restrictions:** The response buffer must be large enough to hold the maximum response frame.


Requirements
************

.. toctree::
    :maxdepth: 1

    ./1_swcReq/SPIAPPReq.rst


Design documentation
********************

.. toctree::
    :maxdepth: 1

    ./2_design/SPIAPPComp.rst


Code documentation
******************

.. toctree::
    :maxdepth: 1

    ./2_design/SPIAPPCfg.rst
    ./2_design/SPIAPPUnit.rst
