SpiService Software Component
###################################

Introduction
************

The SPI Service handles SPI master transfer commands received from the host via the
serial interface. It configures the SPI master driver, executes full-duplex transfers to slave
devices, and returns the received data as a serialized response frame.


References
**********

Other relevant documents, e.g. ISO standards, whitepapers, etc.


Static architecture
*******************

Component
=========

..  swc:: SpiService
    :provides: SpiService.h – SPI master full-duplex transfer execution for SPI Service bridging.
    :requires: spiMasterDriver.h, serialize.h, configService.h.

Public interfaces
=================

..  sw-if:: SpiServiceUnit.h

    Public interface of SpiServiceUnit.

    ..  sw-ifelement:: SpiServiceUnit_Init()
        :arguments:     return: SpiService_Status_t;

        Initializes the SPI Service and configures the SPI master driver with
        default settings.

        **Arguments:** None.

        **Return values:** SPISERVICE_STATUS_OK on success, SPISERVICE_STATUS_ERROR on failure.

        **Restrictions:** Must be called before any other SPI Service function.

    ..  sw-ifelement:: SpiServiceUnit_DeInit()
        :arguments:     return: SpiService_Status_t;

        De-initializes the SPI Service and releases resources.

        **Arguments:** None.

        **Return values:** SPISERVICE_STATUS_OK on success.

        **Restrictions:** None.

    ..  sw-ifelement:: SpiServiceUnit_Run()
        :arguments:     return: SpiService_Status_t;

        Executes one cycle of the SPI processing loop (handles asynchronous transfer completion).

        **Arguments:** None.

        **Return values:** SPISERVICE_STATUS_OK on success, SPISERVICE_STATUS_NOT_INITIALIZED if called before Init.

        **Restrictions:** Must be called periodically from the main loop when asynchronous SPI transfers are in use.

    ..  sw-ifelement:: SpiServiceUnit_ProcessFrame()
        :arguments:     return: SpiService_Status_t;    pFrame: const uint8_t*;    frameLength: uint16_t;    pResponse: uint8_t*;    pResponseLength: uint16_t*;

        Processes an incoming SPI transfer command frame and fills the output buffer with the
        serialized response containing the received SPI data.

        **Arguments:**

        - **pFrame**: Pointer to the raw incoming frame bytes.
        - **frameLength**: Length of the incoming frame in bytes.
        - **pResponse**: Pointer to the output buffer for the serialized response.
        - **pResponseLength**: Pointer to receive the number of bytes written to the response buffer.

        **Return values:** SPISERVICE_STATUS_OK on success, SPISERVICE_STATUS_INVALID_PARAM for NULL pointers or zero length,
        SPISERVICE_STATUS_ERROR on SPI transfer or serialization failure.

        **Restrictions:** The response buffer must be large enough to hold the maximum response frame.


Requirements
************

.. toctree::
    :maxdepth: 1

    ./1_swcReq/SpiServiceReq.rst


Design documentation
********************

.. toctree::
    :maxdepth: 1

    ./2_design/SpiServiceComp.rst


Code documentation
******************

.. toctree::
    :maxdepth: 1

    ./2_design/SpiServiceCfg.rst
    ./2_design/SpiServiceUnit.rst
