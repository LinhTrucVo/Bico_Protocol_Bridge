DIGITALAPP Software Component
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

..  swc:: DIGITALAPP
    :provides: DIGITALAPP.h – GPIO pin and PWM channel control for serial-to-digital bridging.
    :requires: gpioDriver.h, pwmDriver.h, serialize.h, configService.h.

Public interfaces
=================

..  sw-if:: DIGITALAPPUnit.h

    Public interface of DIGITALAPPUnit.

    ..  sw-ifelement:: DIGITALAPPUnit_Init()
        :arguments:     return: DIGITALAPP_Status_t;

        Initializes the Serial-to-Digital application and configures GPIO and PWM drivers with
        default settings.

        **Arguments:** None.

        **Return values:** DIGITAL_APP_STATUS_OK on success, DIGITAL_APP_STATUS_ERROR on failure.

        **Restrictions:** Must be called before any other Serial-to-Digital function.

    ..  sw-ifelement:: DIGITALAPPUnit_DeInit()
        :arguments:     return: DIGITALAPP_Status_t;

        De-initializes the Serial-to-Digital application and releases resources.

        **Arguments:** None.

        **Return values:** DIGITAL_APP_STATUS_OK on success.

        **Restrictions:** None.

    ..  sw-ifelement:: DIGITALAPPUnit_Run()
        :arguments:     return: DIGITALAPP_Status_t;

        Executes one cycle of the digital I/O processing loop (used for interrupt-driven events).

        **Arguments:** None.

        **Return values:** DIGITAL_APP_STATUS_OK on success, DIGITAL_APP_STATUS_NOT_INITIALIZED if called before Init.

        **Restrictions:** Must be called periodically from the main loop.

    ..  sw-ifelement:: DIGITALAPPUnit_ProcessFrame()
        :arguments:     return: DIGITALAPP_Status_t;    pFrame: const uint8_t*;    frameLength: uint16_t;    pResponse: uint8_t*;    pResponseLength: uint16_t*;

        Processes an incoming GPIO or PWM command frame and fills the output buffer with the
        serialized response.

        **Arguments:**

        - **pFrame**: Pointer to the raw incoming frame bytes.
        - **frameLength**: Length of the incoming frame in bytes.
        - **pResponse**: Pointer to the output buffer for the serialized response.
        - **pResponseLength**: Pointer to receive the number of bytes written to the response buffer.

        **Return values:** DIGITAL_APP_STATUS_OK on success, DIGITAL_APP_STATUS_INVALID_PARAM for NULL pointers or zero length,
        DIGITAL_APP_STATUS_ERROR on GPIO/PWM or serialization failure.

        **Restrictions:** The response buffer must be large enough to hold the maximum response frame.


Requirements
************

.. toctree::
    :maxdepth: 1

    ./1_swcReq/DIGITALAPPReq.rst


Design documentation
********************

.. toctree::
    :maxdepth: 1

    ./2_design/DIGITALAPPComp.rst


Code documentation
******************

.. toctree::
    :maxdepth: 1

    ./2_design/DIGITALAPPCfg.rst
    ./2_design/DIGITALAPPUnit.rst
