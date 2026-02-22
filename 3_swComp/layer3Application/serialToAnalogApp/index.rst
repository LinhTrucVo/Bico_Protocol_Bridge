serialToAnalogApp Software Component
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

..  swc:: serialToAnalogApp
    :provides: serialToAnalogApp.h – ADC channel configuration, sampling, and response building for serial-to-analog bridging.
    :requires: adcDriver.h, serialize.h, configService.h.

Public interfaces
=================

..  sw-if:: serialToAnalogAppUnit.h

    Public interface of serialToAnalogAppUnit.

    ..  sw-ifelement:: SerialToAnalogAppUnit_Init()
        :arguments:     return: SerialToAnalogApp_Status_t;

        Initializes the Serial-to-Analog application and configures the ADC driver with default settings.

        **Arguments:** None.

        **Return values:** SERIAL_TO_ANALOG_APP_STATUS_OK on success, SERIAL_TO_ANALOG_APP_STATUS_ERROR on failure.

        **Restrictions:** Must be called before any other Serial-to-Analog function.

    ..  sw-ifelement:: SerialToAnalogAppUnit_DeInit()
        :arguments:     return: SerialToAnalogApp_Status_t;

        De-initializes the Serial-to-Analog application and releases resources.

        **Arguments:** None.

        **Return values:** SERIAL_TO_ANALOG_APP_STATUS_OK on success.

        **Restrictions:** None.

    ..  sw-ifelement:: SerialToAnalogAppUnit_Run()
        :arguments:     return: SerialToAnalogApp_Status_t;

        Executes one cycle of the analog sampling state machine (used for continuous sampling mode).

        **Arguments:** None.

        **Return values:** SERIAL_TO_ANALOG_APP_STATUS_OK on success, SERIAL_TO_ANALOG_APP_STATUS_NOT_INITIALIZED if called before Init.

        **Restrictions:** Must be called periodically from the main loop when continuous sampling is active.

    ..  sw-ifelement:: SerialToAnalogAppUnit_ProcessFrame()
        :arguments:     return: SerialToAnalogApp_Status_t;    pFrame: const uint8_t*;    frameLength: uint16_t;    pResponse: uint8_t*;    pResponseLength: uint16_t*;

        Processes an incoming ADC command frame and fills the output buffer with the serialized
        response (samples or acknowledgement).

        **Arguments:**

        - **pFrame**: Pointer to the raw incoming frame bytes.
        - **frameLength**: Length of the incoming frame in bytes.
        - **pResponse**: Pointer to the output buffer for the serialized response.
        - **pResponseLength**: Pointer to receive the number of bytes written to the response buffer.

        **Return values:** SERIAL_TO_ANALOG_APP_STATUS_OK on success, SERIAL_TO_ANALOG_APP_STATUS_INVALID_PARAM for NULL pointers or zero length,
        SERIAL_TO_ANALOG_APP_STATUS_ERROR on ADC or serialization failure.

        **Restrictions:** The response buffer must be large enough to hold the maximum response frame.


Requirements
************

.. toctree::
    :maxdepth: 1

    ./1_swcReq/serialToAnalogAppReq.rst


Design documentation
********************

.. toctree::
    :maxdepth: 1

    ./2_design/serialToAnalogAppComp.rst


Code documentation
******************

.. toctree::
    :maxdepth: 1

    ./2_design/serialToAnalogAppCfg.rst
    ./2_design/serialToAnalogAppUnit.rst
