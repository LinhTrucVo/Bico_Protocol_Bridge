#################################
What is this component about?
#################################

The Serial-to-Digital Application provides typed GPIO and PWM operations. It is called
by the Central Application Controller via RID 0x02xx (GPIO) and RID 0x03xx (PWM).
It receives typed parameters and returns typed results.


#################################
Static structure
#################################

..  uml:: DigitalServiceStaticStructure.puml

Public interfaces
#################################

..  sw-if:: DigitalServiceUnit.h
    :id: SWIF_DIGITALSERVICE

    Public interface of DigitalServiceUnit.

    ..  sw-ifelement:: DigitalServiceUnit_Init()
        :id: SWIFE_DIGITALSERVICE_INIT
        :arguments:     return: DigitalService_Status_t;

        Initializes the Digital Service and configures GPIO and PWM drivers with
        default settings.

        **Arguments:** None.

        **Return values:** BPB_DIGITALSERVICE_STATUS_OK on success, BPB_DIGITALSERVICE_STATUS_ERROR on failure.

        **Restrictions:** Must be called before any other Digital Service function.

    ..  sw-ifelement:: DigitalServiceUnit_DeInit()
        :id: SWIFE_DIGITALSERVICE_DEINIT
        :arguments:     return: DigitalService_Status_t;

        De-initializes the Digital Service and releases resources.

        **Arguments:** None.

        **Return values:** BPB_DIGITALSERVICE_STATUS_OK on success.

        **Restrictions:** None.

    ..  sw-ifelement:: DigitalServiceUnit_Run()
        :id: SWIFE_DIGITALSERVICE_RUN
        :arguments:     return: DigitalService_Status_t;

        Executes one cycle of the digital I/O processing loop (used for interrupt-driven events).

        **Arguments:** None.

        **Return values:** BPB_DIGITALSERVICE_STATUS_OK on success, BPB_DIGITALSERVICE_STATUS_NOT_INITIALIZED if called before Init.

        **Restrictions:** Must be called periodically from the main loop.

    ..  sw-ifelement:: DigitalServiceUnit_ProcessFrame()
        :id: SWIFE_DIGITALSERVICE_PROCESSFRAME
        :arguments:     return: DigitalService_Status_t;    pFrame: const uint8_t*;    frameLength: uint16_t;    pResponse: uint8_t*;    pResponseLength: uint16_t*;

        Processes an incoming GPIO or PWM command frame and fills the output buffer with the
        serialized response.

        **Arguments:**

        - **pFrame**: Pointer to the raw incoming frame bytes.
        - **frameLength**: Length of the incoming frame in bytes.
        - **pResponse**: Pointer to the output buffer for the serialized response.
        - **pResponseLength**: Pointer to receive the number of bytes written to the response buffer.

        **Return values:** BPB_DIGITALSERVICE_STATUS_OK on success, BPB_DIGITALSERVICE_STATUS_INVALID_PARAM for NULL pointers or zero length,
        BPB_DIGITALSERVICE_STATUS_ERROR on GPIO/PWM or serialization failure.

        **Restrictions:** The response buffer must be large enough to hold the maximum response frame.

#################################


Dynamic behaviour
#################################

* State machine diagram
..  uml:: DigitalServiceStateMachine.puml

* Sequence diagram
..  uml:: DigitalServiceSequenceDiagram.puml


#################################
Design choices
#################################
Description:
************
Provide hardware-abstracted GPIO read/write and PWM start/stop for the CAC dispatcher.

Assumptions and influencing factors:
************************************
* GPIO and PWM drivers are initialized and available.
* Pin/channel numbers are validated at driver level.

Solutions list:
***************
Solution 1 - Separate functions per operation
Expose WriteGpio, ReadGpio, StartPwm, StopPwm individually.

Solution 2 - Combined GPIO/PWM function with operation parameter
Single function with operation enum.

Solution evaluation:
********************
Separate functions provide clear API semantics and match 1:1 with RID mapping.

Final solution:
****************
Solution 1 selected for API clarity.