#################################
What is this component about?
#################################

The Central Application Controller (CAC) is the sole UDS-aware component in the system.
It owns all DID and RID mapping, dispatches requests to downstream modules via typed APIs,
and builds UDS responses. Downstream modules (peripheral apps, ConfigService) have no
UDS protocol knowledge.


#################################
Static structure
#################################

..  uml:: centralAppControllerStaticStructure.puml

Public interfaces
#################################

..  sw-if:: centralAppControllerUnit.h
    :id: SWIF_CENTRALAPPCONTROLLER

    Public interface of centralAppControllerUnit.

    ..  sw-ifelement:: CentralAppControllerUnit_Init()
        :id: SWIFE_CENTRALAPPCONTROLLER_INIT
        :arguments:     return: CentralAppController_Status_t;

        Initializes the Central App Controller and all sub-components.

        **Arguments:** None.

        **Return values:** BPB_CENTRAL_APP_CONTROLLER_STATUS_OK on success, BPB_CENTRAL_APP_CONTROLLER_STATUS_ERROR on failure.

        **Restrictions:** Must be called before any other Central App Controller function.

    ..  sw-ifelement:: CentralAppControllerUnit_DeInit()
        :id: SWIFE_CENTRALAPPCONTROLLER_DEINIT
        :arguments:     return: CentralAppController_Status_t;

        De-initializes the Central App Controller and releases resources.

        **Arguments:** None.

        **Return values:** BPB_CENTRAL_APP_CONTROLLER_STATUS_OK on success.

        **Restrictions:** None.

    ..  sw-ifelement:: CentralAppControllerUnit_Run()
        :id: SWIFE_CENTRALAPPCONTROLLER_RUN
        :arguments:     return: CentralAppController_Status_t;

        Executes one iteration of the main processing loop: checks for incoming frames, processes
        any pending command, and transmits the response.

        **Arguments:** None.

        **Return values:** BPB_CENTRAL_APP_CONTROLLER_STATUS_OK when the cycle completes without error,
        BPB_CENTRAL_APP_CONTROLLER_STATUS_ERROR on a processing fault,
        BPB_CENTRAL_APP_CONTROLLER_STATUS_NOT_INITIALIZED if called before Init.

        **Restrictions:** Must be called periodically from the main loop or a scheduler task.

    ..  sw-ifelement:: CentralAppControllerUnit_GetState()
        :id: SWIFE_CENTRALAPPCONTROLLER_GETSTATE
        :arguments:     return: CentralAppController_Status_t;    pState: CentralAppController_State_t*;

        Returns the current internal state of the controller (idle, processing, waiting, error).

        **Arguments:**

        - **pState**: Pointer to receive the current state value.

        **Return values:** BPB_CENTRAL_APP_CONTROLLER_STATUS_OK on success, BPB_CENTRAL_APP_CONTROLLER_STATUS_INVALID_PARAM for NULL pointer.

        **Restrictions:** None.

    ..  sw-ifelement:: CentralAppControllerUnit_ProcessFrame()
        :id: SWIFE_CENTRALAPPCONTROLLER_PROCESSFRAME
        :arguments:     return: CentralAppController_Status_t;    pInFrame: const CentralAppController_Frame_t*;    pOutFrame: CentralAppController_OutFrame_t*;    pOutLength: uint16_t*;

        Processes a single incoming frame synchronously: deserializes, dispatches to the correct
        app handler, and fills the output frame buffer with the serialized response.

        **Arguments:**

        - **pInFrame**: Pointer to the incoming frame descriptor (raw bytes and length).
        - **pOutFrame**: Pointer to the output frame descriptor (buffer pointer and buffer size).
        - **pOutLength**: Pointer to receive the number of bytes written to the output buffer.

        **Return values:** BPB_CENTRAL_APP_CONTROLLER_STATUS_OK on success, BPB_CENTRAL_APP_CONTROLLER_STATUS_TIMEOUT if the
        handler did not complete within the configured timeout, BPB_CENTRAL_APP_CONTROLLER_STATUS_INVALID_PARAM for NULL pointers.

        **Restrictions:** The output frame buffer must be at least BPB_CENTRAL_APP_CFG_MAX_FRAME_SIZE bytes.

    ..  sw-ifelement:: CentralAppControllerUnit_RegisterErrorCallback()
        :id: SWIFE_CENTRALAPPCONTROLLER_REGISTERERRORCALLBACK
        :arguments:     return: CentralAppController_Status_t;    callback: CentralAppController_ErrorCallback_t;

        Registers a callback to be invoked when a processing error occurs.

        **Arguments:**

        - **callback**: Function pointer to the error callback; receives the error code as argument.

        **Return values:** BPB_CENTRAL_APP_CONTROLLER_STATUS_OK on success, BPB_CENTRAL_APP_CONTROLLER_STATUS_NOT_INITIALIZED if called before Init.

        **Restrictions:** None.

#################################


Dynamic behaviour
#################################

* State machine diagram
..  uml:: centralAppControllerStateMachine.puml

* Sequence diagram
..  uml:: centralAppControllerSequenceDiagram.puml


#################################
Design choices
#################################
Description:
************
Provide a single centralized UDS command dispatcher that isolates protocol details
from peripheral application logic.

Assumptions and influencing factors:
************************************
* Only SID 0x22, 0x2E, 0x31 are supported.
* Deserialize/Serialize services handle frame parsing/building.
* Peripheral apps expose typed C APIs (no UDS awareness).
* ConfigService handles DID-mapped configuration parameters.

Solutions list:
***************
Solution 1 - Central dispatcher with DID/RID switch
CAC switches on DID/RID to route to correct downstream module.

Solution 2 - Registration-based routing
Downstream modules register handlers at startup.

Solution evaluation:
********************
Central switch is simpler, fully deterministic, and easier to test with known DID/RID set.

Final solution:
****************
Solution 1 selected for deterministic routing and testability.