pwmDriver Software Component
#############################

Introduction
************

The PWM Driver provides hardware abstraction for Pulse Width Modulation signal generation.
It handles timer initialization, duty cycle configuration, frequency control, and channel enable/disable.


References
**********

Other relevant documents, e.g. ISO standards, whitepapers, etc.


Static architecture
*******************

Component
=========

..  swc:: pwmDriver
    :provides: pwmDriver.h – PWM initialization, duty cycle configuration, frequency control, and channel management.
    :requires: Vendor HAL or register-level timer/PWM peripheral access.

Public interfaces
=================

..  sw-if:: pwmDriverUnit.h

    Public interface of pwmDriverUnit.

    ..  sw-ifelement:: PwmDriverUnit_Init()
        :arguments:     return: PwmDriver_Status_t;    pConfig: const PwmDriver_Config_t*;

        Initializes the PWM timer peripheral with the provided configuration structure.

        **Arguments:**

        - **pConfig**: Pointer to PWM driver configuration structure (enableDma, enableDeadTime).

        **Return values:** PWM_STATUS_OK on success, PWM_STATUS_ERROR for NULL config.

        **Restrictions:** Must be called before any other PWM driver function.

    ..  sw-ifelement:: PwmDriverUnit_ConfigureChannel()
        :arguments:     return: PwmDriver_Status_t;    channel: PwmDriver_Channel_t;    pConfig: const PwmDriver_ChannelConfig_t*;

        Configures a PWM channel with frequency, duty cycle, polarity, alignment, and dead-time settings.

        **Arguments:**

        - **channel**: The PWM channel to configure.
        - **pConfig**: Pointer to channel configuration structure (frequency, dutyCycle, polarity, alignment, deadTime).

        **Return values:** PWM_STATUS_OK on success, PWM_STATUS_ERROR for NULL pointer or invalid channel.

        **Restrictions:** None.

    ..  sw-ifelement:: PwmDriverUnit_SetFrequency()
        :arguments:     return: PwmDriver_Status_t;    channel: PwmDriver_Channel_t;    frequency: uint32_t;

        Sets the output frequency for the specified PWM channel.

        **Arguments:**

        - **channel**: The PWM channel to configure.
        - **frequency**: Desired PWM frequency in Hz.

        **Return values:** PWM_STATUS_OK on success, PWM_STATUS_ERROR for an invalid channel or out-of-range frequency.

        **Restrictions:** None.

    ..  sw-ifelement:: PwmDriverUnit_SetDutyCycle()
        :arguments:     return: PwmDriver_Status_t;    channel: PwmDriver_Channel_t;    dutyCycle: uint16_t;

        Sets the duty cycle for the specified PWM channel (0–10000 representing 0–100%).

        **Arguments:**

        - **channel**: The PWM channel to configure.
        - **dutyCycle**: Duty cycle value in units of 0.01% (0 = 0%, 10000 = 100%).

        **Return values:** PWM_STATUS_OK on success, PWM_STATUS_ERROR for an invalid channel or out-of-range value.

        **Restrictions:** None.

    ..  sw-ifelement:: PwmDriverUnit_SetPolarity()
        :arguments:     return: PwmDriver_Status_t;    channel: PwmDriver_Channel_t;    polarity: PwmDriver_Polarity_t;

        Sets the output polarity (normal or inverted) for a PWM channel.

        **Arguments:**

        - **channel**: The PWM channel to configure.
        - **polarity**: Output polarity (PWM_POLARITY_HIGH or PWM_POLARITY_LOW).

        **Return values:** PWM_STATUS_OK on success, PWM_STATUS_ERROR for an invalid channel.

        **Restrictions:** None.

    ..  sw-ifelement:: PwmDriverUnit_StartChannel()
        :arguments:     return: PwmDriver_Status_t;    channel: PwmDriver_Channel_t;

        Starts PWM signal generation on the specified channel.

        **Arguments:**

        - **channel**: The PWM channel to start.

        **Return values:** PWM_STATUS_OK on success, PWM_STATUS_ERROR for an invalid channel.

        **Restrictions:** PwmDriverUnit_ConfigureChannel() must be called before starting.

    ..  sw-ifelement:: PwmDriverUnit_StopChannel()
        :arguments:     return: PwmDriver_Status_t;    channel: PwmDriver_Channel_t;

        Stops PWM signal generation on the specified channel.

        **Arguments:**

        - **channel**: The PWM channel to stop.

        **Return values:** PWM_STATUS_OK on success, PWM_STATUS_ERROR for an invalid channel.

        **Restrictions:** None.

    ..  sw-ifelement:: PwmDriverUnit_GetConfiguration()
        :arguments:     return: PwmDriver_Status_t;    channel: PwmDriver_Channel_t;    pConfig: PwmDriver_ChannelConfig_t*;

        Reads back the current configuration of the specified PWM channel.

        **Arguments:**

        - **channel**: The PWM channel to query.
        - **pConfig**: Pointer to a channel configuration structure that receives the current settings.

        **Return values:** PWM_STATUS_OK on success, PWM_STATUS_ERROR for an invalid channel or NULL pointer.

        **Restrictions:** None.

    ..  sw-ifelement:: PwmDriverUnit_IsChannelRunning()
        :arguments:     return: PwmDriver_Status_t;    channel: PwmDriver_Channel_t;    pIsRunning: bool*;

        Returns whether the specified PWM channel is currently active.

        **Arguments:**

        - **channel**: The PWM channel to check.
        - **pIsRunning**: Pointer to store the result; set to ``true`` if the channel is running.

        **Return values:** PWM_STATUS_OK on success, PWM_STATUS_ERROR for an invalid channel or NULL pointer.

        **Restrictions:** None.

    ..  sw-ifelement:: PwmDriverUnit_DeInit()
        :arguments:     return: PwmDriver_Status_t;

        De-initializes the PWM peripheral and releases resources.

        **Arguments:** None.

        **Return values:** PWM_STATUS_OK on success.

        **Restrictions:** None.


Requirements
************

.. toctree::
    :maxdepth: 1

    ./1_swcReq/pwmDriverReq.rst


Design documentation
********************

.. toctree::
    :maxdepth: 1

    ./2_design/pwmDriverComp.rst


Code documentation
******************

.. toctree::
    :maxdepth: 1

    ./2_design/pwmDriverCfg.rst
    ./2_design/pwmDriverUnit.rst
