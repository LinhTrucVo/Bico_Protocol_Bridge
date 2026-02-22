adcDriver Software Component
#############################

Introduction
************

The ADC Driver provides hardware abstraction for Analog-to-Digital Converter peripherals.
It handles ADC initialization, channel configuration, start/stop conversion, and value reading.


References
**********

Other relevant documents, e.g. ISO standards, whitepapers, etc.


Static architecture
*******************

Component
=========

..  swc:: adcDriver
    :provides: adcDriver.h – ADC initialization, channel configuration, start/stop conversion, and value reading.
    :requires: Vendor HAL or register-level ADC peripheral access.

Public interfaces
=================

..  sw-if:: adcDriverUnit.h

    Public interface of adcDriverUnit.

    ..  sw-ifelement:: AdcDriverUnit_Init()
        :arguments:     return: AdcDriver_Status_t;    pConfig: const AdcDriver_Config_t*;

        Initializes the ADC peripheral with the provided configuration structure.

        **Arguments:**

        - **pConfig**: Pointer to ADC driver configuration structure.

        **Return values:** ADC_STATUS_OK on success, ADC_STATUS_INVALID_PARAM for invalid parameters.

        **Restrictions:** Must be called before any other ADC driver function.

    ..  sw-ifelement:: AdcDriverUnit_ConfigureChannel()
        :arguments:     return: AdcDriver_Status_t;    channel: AdcDriver_Channel_t;    enable: bool;

        Enables or disables a specific ADC channel.

        **Arguments:**

        - **channel**: The ADC channel to configure.
        - **enable**: ``true`` to enable the channel; ``false`` to disable it.

        **Return values:** ADC_STATUS_OK on success, ADC_STATUS_INVALID_PARAM for an invalid channel.

        **Restrictions:** None.

    ..  sw-ifelement:: AdcDriverUnit_SetResolution()
        :arguments:     return: AdcDriver_Status_t;    resolution: AdcDriver_Resolution_t;

        Sets the ADC conversion resolution.

        **Arguments:**

        - **resolution**: Desired ADC resolution (e.g. 8-bit, 10-bit, 12-bit, 16-bit).

        **Return values:** ADC_STATUS_OK on success, ADC_STATUS_INVALID_PARAM for an unsupported resolution.

        **Restrictions:** None.

    ..  sw-ifelement:: AdcDriverUnit_SetVoltageReference()
        :arguments:     return: AdcDriver_Status_t;    voltageRef: AdcDriver_VoltageRef_t;

        Sets the ADC voltage reference source.

        **Arguments:**

        - **voltageRef**: Voltage reference source selection (internal or external).

        **Return values:** ADC_STATUS_OK on success, ADC_STATUS_INVALID_PARAM for an unsupported reference.

        **Restrictions:** None.

    ..  sw-ifelement:: AdcDriverUnit_SetSamplingFrequency()
        :arguments:     return: AdcDriver_Status_t;    frequency: uint32_t;

        Sets the ADC sampling frequency in Hz.

        **Arguments:**

        - **frequency**: Desired sampling frequency in Hz.

        **Return values:** ADC_STATUS_OK on success, ADC_STATUS_INVALID_PARAM if the frequency is out of range.

        **Restrictions:** None.

    ..  sw-ifelement:: AdcDriverUnit_StartConversion()
        :arguments:     return: AdcDriver_Status_t;    channel: AdcDriver_Channel_t;

        Starts an ADC conversion on the specified channel.

        **Arguments:**

        - **channel**: The ADC channel to start conversion on.

        **Return values:** ADC_STATUS_OK on success, ADC_STATUS_INVALID_PARAM for an invalid channel, ADC_STATUS_ERROR if already running.

        **Restrictions:** The channel must be enabled via AdcDriverUnit_ConfigureChannel() before calling this function.

    ..  sw-ifelement:: AdcDriverUnit_StopConversion()
        :arguments:     return: AdcDriver_Status_t;

        Stops an ongoing ADC conversion.

        **Arguments:** None.

        **Return values:** ADC_STATUS_OK on success.

        **Restrictions:** None.

    ..  sw-ifelement:: AdcDriverUnit_ReadValue()
        :arguments:     return: AdcDriver_Status_t;    channel: AdcDriver_Channel_t;    pValue: uint16_t*;

        Reads the latest conversion result for the specified channel.

        **Arguments:**

        - **channel**: The ADC channel to read from.
        - **pValue**: Pointer to store the conversion result.

        **Return values:** ADC_STATUS_OK on success, ADC_STATUS_INVALID_PARAM for a NULL pointer or invalid channel, ADC_STATUS_ERROR if conversion is not complete.

        **Restrictions:** AdcDriverUnit_IsConversionComplete() should confirm completion before calling this function.

    ..  sw-ifelement:: AdcDriverUnit_IsConversionComplete()
        :arguments:     return: AdcDriver_Status_t;    channel: AdcDriver_Channel_t;    pComplete: bool*;

        Checks whether the conversion on the specified channel is complete.

        **Arguments:**

        - **channel**: The ADC channel to check.
        - **pComplete**: Pointer to store the result; set to ``true`` when conversion is done.

        **Return values:** ADC_STATUS_OK on success, ADC_STATUS_INVALID_PARAM for a NULL pointer or invalid channel.

        **Restrictions:** None.

    ..  sw-ifelement:: AdcDriverUnit_RegisterCallback()
        :arguments:     return: AdcDriver_Status_t;    callback: AdcDriver_ConversionCallback_t;

        Registers a callback to be invoked on conversion completion.

        **Arguments:**

        - **callback**: Function pointer to the callback. Pass NULL to deregister.

        **Return values:** ADC_STATUS_OK on success.

        **Restrictions:** Callbacks are invoked from interrupt context; they must be short and non-blocking.

    ..  sw-ifelement:: AdcDriverUnit_GetStatus()
        :arguments:     return: AdcDriver_Status_t;    pStatus: AdcDriver_Status_t*;

        Returns the current status of the ADC driver.

        **Arguments:**

        - **pStatus**: Pointer to store the current driver status code.

        **Return values:** ADC_STATUS_OK on success, ADC_STATUS_INVALID_PARAM for a NULL pointer.

        **Restrictions:** None.

    ..  sw-ifelement:: AdcDriverUnit_DeInit()
        :arguments:     return: AdcDriver_Status_t;

        De-initializes the ADC peripheral and releases resources.

        **Arguments:** None.

        **Return values:** ADC_STATUS_OK on success.

        **Restrictions:** None.


Requirements
************

.. toctree::
    :maxdepth: 1

    ./1_swcReq/adcDriverReq.rst


Design documentation
********************

.. toctree::
    :maxdepth: 1

    ./2_design/adcDriverComp.rst


Code documentation
******************

.. toctree::
    :maxdepth: 1

    ./2_design/adcDriverCfg.rst
    ./2_design/adcDriverUnit.rst
