serialToDigitalApp Software Component
#######################################

Introduction
************

The Serial-to-Digital Application handles GPIO and PWM commands received from the host via the
serial interface. It configures digital pins and PWM channels, executes read/write/toggle
operations, and returns the result as a serialized response frame.


References
**********

Other relevant documents, e.g. ISO standards, whitepapers, etc.


Static architecture
*******************

Component
=========

..  swc:: serialToDigitalApp
    :provides: serialToDigitalApp.h – GPIO pin and PWM channel control for serial-to-digital bridging.
    :requires: gpioDriver.h, pwmDriver.h, serialize.h, configService.h.

Public interfaces
=================

..  sw-if:: serialToDigitalAppUnit.h

    Public interface of serialToDigitalAppUnit.

    ..  sw-ifelement:: SerialToDigitalAppUnit_Init()
        :arguments:     return: SerialToDigitalApp_Status_t;

        Initializes the Serial-to-Digital application and configures GPIO and PWM drivers with
        default settings.

        **Arguments:** None.

        **Return values:** SERIAL_TO_DIGITAL_APP_STATUS_OK on success, SERIAL_TO_DIGITAL_APP_STATUS_ERROR on failure.

        **Restrictions:** Must be called before any other Serial-to-Digital function.

    ..  sw-ifelement:: SerialToDigitalAppUnit_DeInit()
        :arguments:     return: SerialToDigitalApp_Status_t;

        De-initializes the Serial-to-Digital application and releases resources.

        **Arguments:** None.

        **Return values:** SERIAL_TO_DIGITAL_APP_STATUS_OK on success.

        **Restrictions:** None.

    ..  sw-ifelement:: SerialToDigitalAppUnit_Run()
        :arguments:     return: SerialToDigitalApp_Status_t;

        Executes one cycle of the digital I/O processing loop (used for interrupt-driven events).

        **Arguments:** None.

        **Return values:** SERIAL_TO_DIGITAL_APP_STATUS_OK on success, SERIAL_TO_DIGITAL_APP_STATUS_NOT_INITIALIZED if called before Init.

        **Restrictions:** Must be called periodically from the main loop.

    ..  sw-ifelement:: SerialToDigitalAppUnit_ProcessFrame()
        :arguments:     return: SerialToDigitalApp_Status_t;    pFrame: const uint8_t*;    frameLength: uint16_t;    pResponse: uint8_t*;    pResponseLength: uint16_t*;

        Processes an incoming GPIO or PWM command frame and fills the output buffer with the
        serialized response.

        **Arguments:**

        - **pFrame**: Pointer to the raw incoming frame bytes.
        - **frameLength**: Length of the incoming frame in bytes.
        - **pResponse**: Pointer to the output buffer for the serialized response.
        - **pResponseLength**: Pointer to receive the number of bytes written to the response buffer.

        **Return values:** SERIAL_TO_DIGITAL_APP_STATUS_OK on success, SERIAL_TO_DIGITAL_APP_STATUS_INVALID_PARAM for NULL pointers or zero length,
        SERIAL_TO_DIGITAL_APP_STATUS_ERROR on GPIO/PWM or serialization failure.

        **Restrictions:** The response buffer must be large enough to hold the maximum response frame.


Requirements
************

.. toctree::
    :maxdepth: 1

    ./1_swcReq/serialToDigitalAppReq.rst


Design documentation
********************

.. toctree::
    :maxdepth: 1

    ./2_design/serialToDigitalAppComp.rst


Code documentation
******************

.. toctree::
    :maxdepth: 1

    ./2_design/serialToDigitalAppCfg.rst
    ./2_design/serialToDigitalAppUnit.rst
