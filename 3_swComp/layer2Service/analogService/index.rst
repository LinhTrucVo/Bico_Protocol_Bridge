AnalogService Software Component
######################################

Introduction
************

The Analog Service handles all ADC-related commands received from the host via the
serial interface. It configures ADC channels, triggers sampling, optionally applies averaging and
filtering, and returns the digitized results as a serialized response frame.


References
**********

Other relevant documents, e.g. ISO standards, whitepapers, etc.


Static architecture
*******************

Component
=========

..  swc:: AnalogService
    :provides: AnalogService.h – ADC channel configuration, sampling, and response building for Analog Service bridging.
    :requires: adcDriver.h, serialize.h, configService.h.

Public interfaces
=================

..  sw-if:: AnalogServiceUnit.h

    Public interface of AnalogServiceUnit.

    ..  sw-ifelement:: AnalogServiceUnit_Init()
        :arguments:     return: AnalogService_Status_t;

        Initializes the Analog Service and configures the ADC driver with default settings.

        **Arguments:** None.

        **Return values:** ANALOGSERVICE_STATUS_OK on success, ANALOGSERVICE_STATUS_ERROR on failure.

        **Restrictions:** Must be called before any other Analog Service function.

    ..  sw-ifelement:: AnalogServiceUnit_DeInit()
        :arguments:     return: AnalogService_Status_t;

        De-initializes the Analog Service and releases resources.

        **Arguments:** None.

        **Return values:** ANALOGSERVICE_STATUS_OK on success.

        **Restrictions:** None.

    ..  sw-ifelement:: AnalogServiceUnit_Run()
        :arguments:     return: AnalogService_Status_t;

        Executes one cycle of the analog sampling state machine (used for continuous sampling mode).

        **Arguments:** None.

        **Return values:** ANALOGSERVICE_STATUS_OK on success, ANALOGSERVICE_STATUS_NOT_INITIALIZED if called before Init.

        **Restrictions:** Must be called periodically from the main loop when continuous sampling is active.

    ..  sw-ifelement:: AnalogServiceUnit_ProcessFrame()
        :arguments:     return: AnalogService_Status_t;    pFrame: const uint8_t*;    frameLength: uint16_t;    pResponse: uint8_t*;    pResponseLength: uint16_t*;

        Processes an incoming ADC command frame and fills the output buffer with the serialized
        response (samples or acknowledgement).

        **Arguments:**

        - **pFrame**: Pointer to the raw incoming frame bytes.
        - **frameLength**: Length of the incoming frame in bytes.
        - **pResponse**: Pointer to the output buffer for the serialized response.
        - **pResponseLength**: Pointer to receive the number of bytes written to the response buffer.

        **Return values:** ANALOGSERVICE_STATUS_OK on success, ANALOGSERVICE_STATUS_INVALID_PARAM for NULL pointers or zero length,
        ANALOGSERVICE_STATUS_ERROR on ADC or serialization failure.

        **Restrictions:** The response buffer must be large enough to hold the maximum response frame.


Requirements
************

.. toctree::
    :maxdepth: 1

    ./1_swcReq/AnalogServiceReq.rst


Design documentation
********************

.. toctree::
    :maxdepth: 1

    ./2_design/AnalogServiceComp.rst


Code documentation
******************

.. toctree::
    :maxdepth: 1

    ./2_design/AnalogServiceCfg.rst
    ./2_design/AnalogServiceUnit.rst
