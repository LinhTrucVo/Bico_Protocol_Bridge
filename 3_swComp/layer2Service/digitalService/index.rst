DigitalService Software Component
#######################################

Introduction
************

The Digital Service handles GPIO and PWM commands received from the host via the
serial interface. It configures digital pins and PWM channels, executes read/write/toggle
operations, and returns the result as a serialized response frame.


References
**********

Other relevant documents, e.g. ISO standards, whitepapers, etc.


Static architecture
*******************

Component
=========

..  swc:: DigitalService
    :provides: DigitalService.h – GPIO pin and PWM channel control for Digital Service bridging.
    :requires: gpioDriver.h, pwmDriver.h, serialize.h, configService.h.

Public interfaces
=================

..  sw-if:: DigitalServiceUnit.h

    Public interface of DigitalServiceUnit.

    ..  sw-ifelement:: DigitalServiceUnit_Init()
        :arguments:     return: DigitalService_Status_t;

        Initializes the Digital Service and configures GPIO and PWM drivers with
        default settings.

        **Arguments:** None.

        **Return values:** DIGITALSERVICE_STATUS_OK on success, DIGITALSERVICE_STATUS_ERROR on failure.

        **Restrictions:** Must be called before any other Digital Service function.

    ..  sw-ifelement:: DigitalServiceUnit_DeInit()
        :arguments:     return: DigitalService_Status_t;

        De-initializes the Digital Service and releases resources.

        **Arguments:** None.

        **Return values:** DIGITALSERVICE_STATUS_OK on success.

        **Restrictions:** None.

    ..  sw-ifelement:: DigitalServiceUnit_Run()
        :arguments:     return: DigitalService_Status_t;

        Executes one cycle of the digital I/O processing loop (used for interrupt-driven events).

        **Arguments:** None.

        **Return values:** DIGITALSERVICE_STATUS_OK on success, DIGITALSERVICE_STATUS_NOT_INITIALIZED if called before Init.

        **Restrictions:** Must be called periodically from the main loop.

    ..  sw-ifelement:: DigitalServiceUnit_ProcessFrame()
        :arguments:     return: DigitalService_Status_t;    pFrame: const uint8_t*;    frameLength: uint16_t;    pResponse: uint8_t*;    pResponseLength: uint16_t*;

        Processes an incoming GPIO or PWM command frame and fills the output buffer with the
        serialized response.

        **Arguments:**

        - **pFrame**: Pointer to the raw incoming frame bytes.
        - **frameLength**: Length of the incoming frame in bytes.
        - **pResponse**: Pointer to the output buffer for the serialized response.
        - **pResponseLength**: Pointer to receive the number of bytes written to the response buffer.

        **Return values:** DIGITALSERVICE_STATUS_OK on success, DIGITALSERVICE_STATUS_INVALID_PARAM for NULL pointers or zero length,
        DIGITALSERVICE_STATUS_ERROR on GPIO/PWM or serialization failure.

        **Restrictions:** The response buffer must be large enough to hold the maximum response frame.


Requirements
************

.. toctree::
    :maxdepth: 1

    ./1_swcReq/DigitalServiceReq.rst


Design documentation
********************

.. toctree::
    :maxdepth: 1

    ./2_design/DigitalServiceComp.rst


Code documentation
******************

.. toctree::
    :maxdepth: 1

    ./2_design/DigitalServiceCfg.rst
    ./2_design/DigitalServiceUnit.rst
