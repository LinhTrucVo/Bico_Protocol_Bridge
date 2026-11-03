#################################
What is this component about?
#################################

The ADC Driver abstracts ADC configuration and sampling operations.


#################################
Static structure
#################################

..  uml:: adcDriverStaticStructure.puml

Public interfaces
#################################

..  sw-if:: adcDriverUnit.h
    :id: SWIF_ADCDRIVER

    Public interface of adcDriverUnit.

    ..  sw-ifelement:: AdcDriverUnit_Init()
        :id: SWIFE_ADCDRIVER_INIT
        :arguments:     return: AdcDriver_Status_t;    pConfig: const AdcDriver_Config_t*;

        Initializes the ADC peripheral with the provided configuration structure.

        **Arguments:**

        - **pConfig**: Pointer to ADC driver configuration structure.

        **Return values:** BPB_ADC_STATUS_OK on success, BPB_ADC_STATUS_INVALID_PARAM for invalid parameters.

        **Restrictions:** Must be called before any other ADC driver function.

    ..  sw-ifelement:: AdcDriverUnit_ConfigureChannel()
        :id: SWIFE_ADCDRIVER_CONFIGURECHANNEL
        :arguments:     return: AdcDriver_Status_t;    channel: AdcDriver_Channel_t;    enable: bool;

        Enables or disables a specific ADC channel.

        **Arguments:**

        - **channel**: The ADC channel to configure.
        - **enable**: ``true`` to enable the channel; ``false`` to disable it.

        **Return values:** BPB_ADC_STATUS_OK on success, BPB_ADC_STATUS_INVALID_PARAM for an invalid channel.

        **Restrictions:** None.

    ..  sw-ifelement:: AdcDriverUnit_SetResolution()
        :id: SWIFE_ADCDRIVER_SETRESOLUTION
        :arguments:     return: AdcDriver_Status_t;    resolution: AdcDriver_Resolution_t;

        Sets the ADC conversion resolution.

        **Arguments:**

        - **resolution**: Desired ADC resolution (e.g. 8-bit, 10-bit, 12-bit, 16-bit).

        **Return values:** BPB_ADC_STATUS_OK on success, BPB_ADC_STATUS_INVALID_PARAM for an unsupported resolution.

        **Restrictions:** None.

    ..  sw-ifelement:: AdcDriverUnit_SetVoltageReference()
        :id: SWIFE_ADCDRIVER_SETVOLTAGEREFERENCE
        :arguments:     return: AdcDriver_Status_t;    voltageRef: AdcDriver_VoltageRef_t;

        Sets the ADC voltage reference source.

        **Arguments:**

        - **voltageRef**: Voltage reference source selection (internal or external).

        **Return values:** BPB_ADC_STATUS_OK on success, BPB_ADC_STATUS_INVALID_PARAM for an unsupported reference.

        **Restrictions:** None.

    ..  sw-ifelement:: AdcDriverUnit_SetSamplingFrequency()
        :id: SWIFE_ADCDRIVER_SETSAMPLINGFREQUENCY
        :arguments:     return: AdcDriver_Status_t;    frequency: uint32_t;

        Sets the ADC sampling frequency in Hz.

        **Arguments:**

        - **frequency**: Desired sampling frequency in Hz.

        **Return values:** BPB_ADC_STATUS_OK on success, BPB_ADC_STATUS_INVALID_PARAM if the frequency is out of range.

        **Restrictions:** None.

    ..  sw-ifelement:: AdcDriverUnit_StartConversion()
        :id: SWIFE_ADCDRIVER_STARTCONVERSION
        :arguments:     return: AdcDriver_Status_t;    channel: AdcDriver_Channel_t;

        Starts an ADC conversion on the specified channel.

        **Arguments:**

        - **channel**: The ADC channel to start conversion on.

        **Return values:** BPB_ADC_STATUS_OK on success, BPB_ADC_STATUS_INVALID_PARAM for an invalid channel, BPB_ADC_STATUS_ERROR if already running.

        **Restrictions:** The channel must be enabled via AdcDriverUnit_ConfigureChannel() before calling this function.

    ..  sw-ifelement:: AdcDriverUnit_StopConversion()
        :id: SWIFE_ADCDRIVER_STOPCONVERSION
        :arguments:     return: AdcDriver_Status_t;

        Stops an ongoing ADC conversion.

        **Arguments:** None.

        **Return values:** BPB_ADC_STATUS_OK on success.

        **Restrictions:** None.

    ..  sw-ifelement:: AdcDriverUnit_ReadValue()
        :id: SWIFE_ADCDRIVER_READVALUE
        :arguments:     return: AdcDriver_Status_t;    channel: AdcDriver_Channel_t;    pValue: uint16_t*;

        Reads the latest conversion result for the specified channel.

        **Arguments:**

        - **channel**: The ADC channel to read from.
        - **pValue**: Pointer to store the conversion result.

        **Return values:** BPB_ADC_STATUS_OK on success, BPB_ADC_STATUS_INVALID_PARAM for a NULL pointer or invalid channel, BPB_ADC_STATUS_ERROR if conversion is not complete.

        **Restrictions:** AdcDriverUnit_IsConversionComplete() should confirm completion before calling this function.

    ..  sw-ifelement:: AdcDriverUnit_IsConversionComplete()
        :id: SWIFE_ADCDRIVER_ISCONVERSIONCOMPLETE
        :arguments:     return: AdcDriver_Status_t;    channel: AdcDriver_Channel_t;    pComplete: bool*;

        Checks whether the conversion on the specified channel is complete.

        **Arguments:**

        - **channel**: The ADC channel to check.
        - **pComplete**: Pointer to store the result; set to ``true`` when conversion is done.

        **Return values:** BPB_ADC_STATUS_OK on success, BPB_ADC_STATUS_INVALID_PARAM for a NULL pointer or invalid channel.

        **Restrictions:** None.

    ..  sw-ifelement:: AdcDriverUnit_RegisterCallback()
        :id: SWIFE_ADCDRIVER_REGISTERCALLBACK
        :arguments:     return: AdcDriver_Status_t;    callback: AdcDriver_ConversionCallback_t;

        Registers a callback to be invoked on conversion completion.

        **Arguments:**

        - **callback**: Function pointer to the callback. Pass NULL to deregister.

        **Return values:** BPB_ADC_STATUS_OK on success.

        **Restrictions:** Callbacks are invoked from interrupt context; they must be short and non-blocking.

    ..  sw-ifelement:: AdcDriverUnit_GetStatus()
        :id: SWIFE_ADCDRIVER_GETSTATUS
        :arguments:     return: AdcDriver_Status_t;    pStatus: AdcDriver_Status_t*;

        Returns the current status of the ADC driver.

        **Arguments:**

        - **pStatus**: Pointer to store the current driver status code.

        **Return values:** BPB_ADC_STATUS_OK on success, BPB_ADC_STATUS_INVALID_PARAM for a NULL pointer.

        **Restrictions:** None.

    ..  sw-ifelement:: AdcDriverUnit_DeInit()
        :id: SWIFE_ADCDRIVER_DEINIT
        :arguments:     return: AdcDriver_Status_t;

        De-initializes the ADC peripheral and releases resources.

        **Arguments:** None.

        **Return values:** BPB_ADC_STATUS_OK on success.

        **Restrictions:** None.

#################################


Dynamic behaviour
#################################

* State machine diagram
..  uml:: adcDriverStateMachine.puml

* Sequence diagram
..  uml:: adcDriverSequenceDiagram.puml


#################################
Design chooices
#################################
Description:
************
Provide a thin HAL wrapper for ADC access and configuration.

Assumptions and influencing factors:
************************************
* Vendor HAL is used for register access.

Solutions list:
***************
Solution 1 - HAL wrapper
Wrap vendor HAL APIs.

Solution 2 - Direct register access
Implement register operations per platform.

Solution evaluation:
********************
HAL wrapper improves portability and reduces platform-specific code.

Final solution:
****************
Solution 1 selected for portability.
