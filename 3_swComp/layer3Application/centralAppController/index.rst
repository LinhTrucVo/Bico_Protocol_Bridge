centralAppController Software Component
########################################

Introduction
************

The Central Application Controller is the top-level dispatcher of the protocol bridge. It receives
raw serial frames from the serial driver, delegates deserialization, routes commands to the
appropriate application handler (analog, digital, I2C, SPI), and serializes the response back to
the host. It manages the overall processing state machine and error reporting.


References
**********

Other relevant documents, e.g. ISO standards, whitepapers, etc.


Static architecture
*******************

Component
=========

..  swc:: centralAppController
    :provides: centralAppController.h – top-level application dispatch, frame routing, and state management.
    :requires: deserialize.h, serialize.h, ANALOGAPP.h, DIGITALAPP.h, I2CAPP.h, SPIAPP.h.

Public interfaces
=================

..  sw-if:: centralAppControllerUnit.h

    Public interface of centralAppControllerUnit.

    ..  sw-ifelement:: CentralAppControllerUnit_Init()
        :arguments:     return: CentralAppController_Status_t;

        Initializes the Central App Controller and all sub-components.

        **Arguments:** None.

        **Return values:** CENTRAL_APP_CONTROLLER_STATUS_OK on success, CENTRAL_APP_CONTROLLER_STATUS_ERROR on failure.

        **Restrictions:** Must be called before any other Central App Controller function.

    ..  sw-ifelement:: CentralAppControllerUnit_DeInit()
        :arguments:     return: CentralAppController_Status_t;

        De-initializes the Central App Controller and releases resources.

        **Arguments:** None.

        **Return values:** CENTRAL_APP_CONTROLLER_STATUS_OK on success.

        **Restrictions:** None.

    ..  sw-ifelement:: CentralAppControllerUnit_Run()
        :arguments:     return: CentralAppController_Status_t;

        Executes one iteration of the main processing loop: checks for incoming frames, processes
        any pending command, and transmits the response.

        **Arguments:** None.

        **Return values:** CENTRAL_APP_CONTROLLER_STATUS_OK when the cycle completes without error,
        CENTRAL_APP_CONTROLLER_STATUS_ERROR on a processing fault,
        CENTRAL_APP_CONTROLLER_STATUS_NOT_INITIALIZED if called before Init.

        **Restrictions:** Must be called periodically from the main loop or a scheduler task.

    ..  sw-ifelement:: CentralAppControllerUnit_GetState()
        :arguments:     return: CentralAppController_Status_t;    pState: CentralAppController_State_t*;

        Returns the current internal state of the controller (idle, processing, waiting, error).

        **Arguments:**

        - **pState**: Pointer to receive the current state value.

        **Return values:** CENTRAL_APP_CONTROLLER_STATUS_OK on success, CENTRAL_APP_CONTROLLER_STATUS_INVALID_PARAM for NULL pointer.

        **Restrictions:** None.

    ..  sw-ifelement:: CentralAppControllerUnit_ProcessFrame()
        :arguments:     return: CentralAppController_Status_t;    pInFrame: const CentralAppController_Frame_t*;    pOutFrame: CentralAppController_OutFrame_t*;    pOutLength: uint16_t*;

        Processes a single incoming frame synchronously: deserializes, dispatches to the correct
        app handler, and fills the output frame buffer with the serialized response.

        **Arguments:**

        - **pInFrame**: Pointer to the incoming frame descriptor (raw bytes and length).
        - **pOutFrame**: Pointer to the output frame descriptor (buffer pointer and buffer size).
        - **pOutLength**: Pointer to receive the number of bytes written to the output buffer.

        **Return values:** CENTRAL_APP_CONTROLLER_STATUS_OK on success, CENTRAL_APP_CONTROLLER_STATUS_TIMEOUT if the
        handler did not complete within the configured timeout, CENTRAL_APP_CONTROLLER_STATUS_INVALID_PARAM for NULL pointers.

        **Restrictions:** The output frame buffer must be at least CENTRAL_APP_CFG_MAX_FRAME_SIZE bytes.

    ..  sw-ifelement:: CentralAppControllerUnit_RegisterErrorCallback()
        :arguments:     return: CentralAppController_Status_t;    callback: CentralAppController_ErrorCallback_t;

        Registers a callback to be invoked when a processing error occurs.

        **Arguments:**

        - **callback**: Function pointer to the error callback; receives the error code as argument.

        **Return values:** CENTRAL_APP_CONTROLLER_STATUS_OK on success, CENTRAL_APP_CONTROLLER_STATUS_NOT_INITIALIZED if called before Init.

        **Restrictions:** None.


Requirements
************

.. toctree::
    :maxdepth: 1

    ./1_swcReq/centralAppControllerReq.rst


Design documentation
********************

.. toctree::
    :maxdepth: 1

    ./2_design/centralAppControllerComp.rst


Code documentation
******************

.. toctree::
    :maxdepth: 1

    ./2_design/centralAppControllerCfg.rst
    ./2_design/centralAppControllerUnit.rst
