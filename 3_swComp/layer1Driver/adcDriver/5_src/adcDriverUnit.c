// This file is used to define the public interface of the component unit.
// It contains public macros, private variables, and function definitions.

//============================================================================
// Dependencies
//============================================================================
#include "adcDriver.h"
#include "adcDriverCfg.h"
#include "adcDriverUnit.h"

//============================================================================
// Local Macros
//============================================================================

//============================================================================
// Local Types
//============================================================================
typedef struct
{
    bool initialized;
    bool busy;
    AdcDriver_Config_t config;
    bool channelEnabled[ADC_MAX_CHANNELS];
    uint16_t lastValue[ADC_MAX_CHANNELS];
    AdcDriver_ConversionCallback_t callback;
} AdcDriver_Context_t;

//============================================================================
// Variables
//============================================================================
static AdcDriver_Context_t adcContext = {0};

//============================================================================
// Local Function Prototypes
//============================================================================
static bool AdcDriverUnit_IsValidChannel(AdcDriver_Channel_t channel);

//============================================================================
// Public Function Implementations
//============================================================================

AdcDriver_Status_t AdcDriverUnit_Init(const AdcDriver_Config_t *pConfig)
{
    if (pConfig == NULL)
    {
        return ADC_STATUS_INVALID_PARAM;
    }

    // TODO: Add vendor-specific HAL initialization here

    adcContext.config = *pConfig;
    adcContext.initialized = true;
    adcContext.busy = false;
    for (uint8_t i = 0; i < ADC_MAX_CHANNELS; i++)
    {
        adcContext.channelEnabled[i] = false;
        adcContext.lastValue[i] = 0;
    }
    adcContext.callback = NULL;

    return ADC_STATUS_OK;
}

AdcDriver_Status_t AdcDriverUnit_ConfigureChannel(AdcDriver_Channel_t channel, bool enable)
{
    if (!adcContext.initialized)
    {
        return ADC_STATUS_NOT_INITIALIZED;
    }
    if (!AdcDriverUnit_IsValidChannel(channel))
    {
        return ADC_STATUS_INVALID_PARAM;
    }

    // TODO: Configure channel in vendor HAL
    adcContext.channelEnabled[channel] = enable;

    return ADC_STATUS_OK;
}

AdcDriver_Status_t AdcDriverUnit_SetResolution(AdcDriver_Resolution_t resolution)
{
    if (!adcContext.initialized)
    {
        return ADC_STATUS_NOT_INITIALIZED;
    }

    adcContext.config.resolution = resolution;
    return ADC_STATUS_OK;
}

AdcDriver_Status_t AdcDriverUnit_SetVoltageReference(AdcDriver_VoltageRef_t voltageRef)
{
    if (!adcContext.initialized)
    {
        return ADC_STATUS_NOT_INITIALIZED;
    }

    adcContext.config.voltageReference = voltageRef;
    return ADC_STATUS_OK;
}

AdcDriver_Status_t AdcDriverUnit_SetSamplingFrequency(uint32_t frequency)
{
    if (!adcContext.initialized)
    {
        return ADC_STATUS_NOT_INITIALIZED;
    }
    if (frequency == 0)
    {
        return ADC_STATUS_INVALID_PARAM;
    }

    adcContext.config.samplingFrequency = frequency;
    return ADC_STATUS_OK;
}

AdcDriver_Status_t AdcDriverUnit_StartConversion(AdcDriver_Channel_t channel)
{
    if (!adcContext.initialized)
    {
        return ADC_STATUS_NOT_INITIALIZED;
    }
    if (!AdcDriverUnit_IsValidChannel(channel) || !adcContext.channelEnabled[channel])
    {
        return ADC_STATUS_INVALID_PARAM;
    }
    if (adcContext.busy)
    {
        return ADC_STATUS_BUSY;
    }

    // TODO: Start conversion in vendor HAL
    adcContext.busy = true;
    adcContext.lastValue[channel] = 0;

    if (adcContext.config.enableInterrupt && adcContext.callback != NULL)
    {
        adcContext.callback(channel, adcContext.lastValue[channel]);
    }

    adcContext.busy = false;
    return ADC_STATUS_OK;
}

AdcDriver_Status_t AdcDriverUnit_StopConversion(void)
{
    if (!adcContext.initialized)
    {
        return ADC_STATUS_NOT_INITIALIZED;
    }

    // TODO: Stop conversion in vendor HAL
    adcContext.busy = false;
    return ADC_STATUS_OK;
}

AdcDriver_Status_t AdcDriverUnit_ReadValue(AdcDriver_Channel_t channel, uint16_t *pValue)
{
    if (!adcContext.initialized)
    {
        return ADC_STATUS_NOT_INITIALIZED;
    }
    if (pValue == NULL || !AdcDriverUnit_IsValidChannel(channel))
    {
        return ADC_STATUS_INVALID_PARAM;
    }

    *pValue = adcContext.lastValue[channel];
    return ADC_STATUS_OK;
}

AdcDriver_Status_t AdcDriverUnit_IsConversionComplete(AdcDriver_Channel_t channel, bool *pComplete)
{
    if (!adcContext.initialized)
    {
        return ADC_STATUS_NOT_INITIALIZED;
    }
    if (pComplete == NULL || !AdcDriverUnit_IsValidChannel(channel))
    {
        return ADC_STATUS_INVALID_PARAM;
    }

    *pComplete = !adcContext.busy;
    return ADC_STATUS_OK;
}

AdcDriver_Status_t AdcDriverUnit_RegisterCallback(AdcDriver_ConversionCallback_t callback)
{
    if (!adcContext.initialized)
    {
        return ADC_STATUS_NOT_INITIALIZED;
    }

    adcContext.callback = callback;
    return ADC_STATUS_OK;
}

AdcDriver_Status_t AdcDriverUnit_Calibrate(void)
{
    if (!adcContext.initialized)
    {
        return ADC_STATUS_NOT_INITIALIZED;
    }

    // TODO: Perform vendor-specific calibration
    return ADC_STATUS_OK;
}

AdcDriver_Status_t AdcDriverUnit_GetStatus(AdcDriver_Status_t *pStatus)
{
    if (pStatus == NULL)
    {
        return ADC_STATUS_INVALID_PARAM;
    }

    if (!adcContext.initialized)
    {
        *pStatus = ADC_STATUS_NOT_INITIALIZED;
    }
    else if (adcContext.busy)
    {
        *pStatus = ADC_STATUS_BUSY;
    }
    else
    {
        *pStatus = ADC_STATUS_OK;
    }

    return ADC_STATUS_OK;
}

AdcDriver_Status_t AdcDriverUnit_DeInit(void)
{
    // TODO: Add vendor-specific HAL deinitialization here
    adcContext.initialized = false;
    adcContext.busy = false;
    adcContext.callback = NULL;
    return ADC_STATUS_OK;
}

//============================================================================
// Local Function Implementations
//============================================================================

static bool AdcDriverUnit_IsValidChannel(AdcDriver_Channel_t channel)
{
    return (channel < ADC_MAX_CHANNELS);
}
