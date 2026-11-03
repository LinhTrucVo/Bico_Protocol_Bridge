#################################
What is this component about?
#################################

The PWM Driver abstracts PWM channel configuration and control.


#################################
Static structure
#################################

..  uml:: pwmDriverStaticStructure.puml

Public interfaces
#################################

..  sw-if:: pwmDriverUnit.h
    :id: SWIF_PWMDRIVER

    Public interface of pwmDriverUnit.

    ..  sw-ifelement:: PwmDriverUnit_Init()
        :id: SWIFE_PWMDRIVER_INIT
        :arguments:     return: PwmDriver_Status_t;    pConfig: const PwmDriver_Config_t*;

        Initializes the PWM timer peripheral with the provided configuration structure.

        **Arguments:**

        - **pConfig**: Pointer to PWM driver configuration structure (enableDma, enableDeadTime).

        **Return values:** BPB_PWM_STATUS_OK on success, BPB_PWM_STATUS_ERROR for NULL config.

        **Restrictions:** Must be called before any other PWM driver function.

    ..  sw-ifelement:: PwmDriverUnit_ConfigureChannel()
        :id: SWIFE_PWMDRIVER_CONFIGURECHANNEL
        :arguments:     return: PwmDriver_Status_t;    channel: PwmDriver_Channel_t;    pConfig: const PwmDriver_ChannelConfig_t*;

        Configures a PWM channel with frequency, duty cycle, polarity, alignment, and dead-time settings.

        **Arguments:**

        - **channel**: The PWM channel to configure.
        - **pConfig**: Pointer to channel configuration structure (frequency, dutyCycle, polarity, alignment, deadTime).

        **Return values:** BPB_PWM_STATUS_OK on success, BPB_PWM_STATUS_ERROR for NULL pointer or invalid channel.

        **Restrictions:** None.

    ..  sw-ifelement:: PwmDriverUnit_SetFrequency()
        :id: SWIFE_PWMDRIVER_SETFREQUENCY
        :arguments:     return: PwmDriver_Status_t;    channel: PwmDriver_Channel_t;    frequency: uint32_t;

        Sets the output frequency for the specified PWM channel.

        **Arguments:**

        - **channel**: The PWM channel to configure.
        - **frequency**: Desired PWM frequency in Hz.

        **Return values:** BPB_PWM_STATUS_OK on success, BPB_PWM_STATUS_ERROR for an invalid channel or out-of-range frequency.

        **Restrictions:** None.

    ..  sw-ifelement:: PwmDriverUnit_SetDutyCycle()
        :id: SWIFE_PWMDRIVER_SETDUTYCYCLE
        :arguments:     return: PwmDriver_Status_t;    channel: PwmDriver_Channel_t;    dutyCycle: uint16_t;

        Sets the duty cycle for the specified PWM channel (0–10000 representing 0–100%).

        **Arguments:**

        - **channel**: The PWM channel to configure.
        - **dutyCycle**: Duty cycle value in units of 0.01% (0 = 0%, 10000 = 100%).

        **Return values:** BPB_PWM_STATUS_OK on success, BPB_PWM_STATUS_ERROR for an invalid channel or out-of-range value.

        **Restrictions:** None.

    ..  sw-ifelement:: PwmDriverUnit_SetPolarity()
        :id: SWIFE_PWMDRIVER_SETPOLARITY
        :arguments:     return: PwmDriver_Status_t;    channel: PwmDriver_Channel_t;    polarity: PwmDriver_Polarity_t;

        Sets the output polarity (normal or inverted) for a PWM channel.

        **Arguments:**

        - **channel**: The PWM channel to configure.
        - **polarity**: Output polarity (PWM_POLARITY_HIGH or PWM_POLARITY_LOW).

        **Return values:** BPB_PWM_STATUS_OK on success, BPB_PWM_STATUS_ERROR for an invalid channel.

        **Restrictions:** None.

    ..  sw-ifelement:: PwmDriverUnit_StartChannel()
        :id: SWIFE_PWMDRIVER_STARTCHANNEL
        :arguments:     return: PwmDriver_Status_t;    channel: PwmDriver_Channel_t;

        Starts PWM signal generation on the specified channel.

        **Arguments:**

        - **channel**: The PWM channel to start.

        **Return values:** BPB_PWM_STATUS_OK on success, BPB_PWM_STATUS_ERROR for an invalid channel.

        **Restrictions:** PwmDriverUnit_ConfigureChannel() must be called before starting.

    ..  sw-ifelement:: PwmDriverUnit_StopChannel()
        :id: SWIFE_PWMDRIVER_STOPCHANNEL
        :arguments:     return: PwmDriver_Status_t;    channel: PwmDriver_Channel_t;

        Stops PWM signal generation on the specified channel.

        **Arguments:**

        - **channel**: The PWM channel to stop.

        **Return values:** BPB_PWM_STATUS_OK on success, BPB_PWM_STATUS_ERROR for an invalid channel.

        **Restrictions:** None.

    ..  sw-ifelement:: PwmDriverUnit_GetConfiguration()
        :id: SWIFE_PWMDRIVER_GETCONFIGURATION
        :arguments:     return: PwmDriver_Status_t;    channel: PwmDriver_Channel_t;    pConfig: PwmDriver_ChannelConfig_t*;

        Reads back the current configuration of the specified PWM channel.

        **Arguments:**

        - **channel**: The PWM channel to query.
        - **pConfig**: Pointer to a channel configuration structure that receives the current settings.

        **Return values:** BPB_PWM_STATUS_OK on success, BPB_PWM_STATUS_ERROR for an invalid channel or NULL pointer.

        **Restrictions:** None.

    ..  sw-ifelement:: PwmDriverUnit_IsChannelRunning()
        :id: SWIFE_PWMDRIVER_ISCHANNELRUNNING
        :arguments:     return: PwmDriver_Status_t;    channel: PwmDriver_Channel_t;    pIsRunning: bool*;

        Returns whether the specified PWM channel is currently active.

        **Arguments:**

        - **channel**: The PWM channel to check.
        - **pIsRunning**: Pointer to store the result; set to ``true`` if the channel is running.

        **Return values:** BPB_PWM_STATUS_OK on success, BPB_PWM_STATUS_ERROR for an invalid channel or NULL pointer.

        **Restrictions:** None.

    ..  sw-ifelement:: PwmDriverUnit_DeInit()
        :id: SWIFE_PWMDRIVER_DEINIT
        :arguments:     return: PwmDriver_Status_t;

        De-initializes the PWM peripheral and releases resources.

        **Arguments:** None.

        **Return values:** BPB_PWM_STATUS_OK on success.

        **Restrictions:** None.

#################################


Dynamic behaviour
#################################

* State machine diagram
..  uml:: pwmDriverStateMachine.puml

* Sequence diagram
..  uml:: pwmDriverSequenceDiagram.puml


#################################
Design chooices
#################################
Description:
************
Provide a portable PWM abstraction for timer-based outputs.

Assumptions and influencing factors:
************************************
* Vendor HAL provides timer/PWM setup.

Solutions list:
***************
Solution 1 - HAL wrapper
Wrap vendor PWM HAL.

Solution 2 - Direct timer configuration
Implement timer configuration per platform.

Solution evaluation:
********************
HAL wrapper provides portability with minimal effort.

Final solution:
****************
Solution 1 selected for portability.
