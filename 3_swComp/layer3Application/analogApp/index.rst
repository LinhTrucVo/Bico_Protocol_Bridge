ANALOGAPP Software Component
######################################

Introduction
************

The Serial-to-Analog Application handles all ADC-related commands received from the host via the
serial interface. It configures ADC channels, triggers sampling, optionally applies averaging and
filtering, and returns the digitized results as a serialized response frame.


References
**********

Other relevant documents, e.g. ISO standards, whitepapers, etc.


Static architecture
*******************

Component
=========

..  swc:: ANALOGAPP
    :provides: ANALOGAPP.h – ADC channel configuration, sampling, and response building for serial-to-analog bridging.
    :requires: adcDriver.h, serialize.h, configService.h.

Public interfaces
=================

..  sw-if:: ANALOGAPPUnit.h

    Public interface of ANALOGAPPUnit.

    ..  sw-ifelement:: ANALOGAPPUnit_Init()
        :arguments:     return: ANALOGAPP_Status_t;

        Initializes the Serial-to-Analog application and configures the ADC driver with default settings.

        **Arguments:** None.

        **Return values:** ANALOG_APP_STATUS_OK on success, ANALOG_APP_STATUS_ERROR on failure.

        **Restrictions:** Must be called before any other Serial-to-Analog function.

    ..  sw-ifelement:: ANALOGAPPUnit_DeInit()
        :arguments:     return: ANALOGAPP_Status_t;

        De-initializes the Serial-to-Analog application and releases resources.

        **Arguments:** None.

        **Return values:** ANALOG_APP_STATUS_OK on success.

        **Restrictions:** None.

    ..  sw-ifelement:: ANALOGAPPUnit_Run()
        :arguments:     return: ANALOGAPP_Status_t;

        Executes one cycle of the analog sampling state machine (used for continuous sampling mode).

        **Arguments:** None.

        **Return values:** ANALOG_APP_STATUS_OK on success, ANALOG_APP_STATUS_NOT_INITIALIZED if called before Init.

        **Restrictions:** Must be called periodically from the main loop when continuous sampling is active.

    ..  sw-ifelement:: ANALOGAPPUnit_ProcessFrame()
        :arguments:     return: ANALOGAPP_Status_t;    pFrame: const uint8_t*;    frameLength: uint16_t;    pResponse: uint8_t*;    pResponseLength: uint16_t*;

        Processes an incoming ADC command frame and fills the output buffer with the serialized
        response (samples or acknowledgement).

        **Arguments:**

        - **pFrame**: Pointer to the raw incoming frame bytes.
        - **frameLength**: Length of the incoming frame in bytes.
        - **pResponse**: Pointer to the output buffer for the serialized response.
        - **pResponseLength**: Pointer to receive the number of bytes written to the response buffer.

        **Return values:** ANALOG_APP_STATUS_OK on success, ANALOG_APP_STATUS_INVALID_PARAM for NULL pointers or zero length,
        ANALOG_APP_STATUS_ERROR on ADC or serialization failure.

        **Restrictions:** The response buffer must be large enough to hold the maximum response frame.


Requirements
************

.. toctree::
    :maxdepth: 1

    ./1_swcReq/ANALOGAPPReq.rst


Design documentation
********************

.. toctree::
    :maxdepth: 1

    ./2_design/ANALOGAPPComp.rst


Code documentation
******************

.. toctree::
    :maxdepth: 1

    ./2_design/ANALOGAPPCfg.rst
    ./2_design/ANALOGAPPUnit.rst
