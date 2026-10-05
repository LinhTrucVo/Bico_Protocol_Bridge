// This file is used to define the public interface of the component unit.
// It contains public macros, private variables, and function definitions.

//============================================================================
// Dependencies
//============================================================================
#include <string.h>
#include "adcDriver.h"
#include "adcDriverCfg.h"
#include "adcDriverPorting.h"

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
    bool conversionComplete;
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
static void AdcDriverUnit_OnPortSample(uint8_t channel, uint16_t value);

//============================================================================
// Public Function Implementations
//============================================================================

AdcDriver_Status_t AdcDriverUnit_Init(const AdcDriver_Config_t *pConfig)
{
    if (pConfig == NULL)
    {
        return ADC_STATUS_INVALID_PARAM;
    }
    if (adcContext.initialized)
    {
        AdcPort_StopPeriodicSampling();
        AdcPort_DeInit();
    }

    (void)memset(&adcContext, 0, sizeof(adcContext));
    if (!AdcPort_Init())
    {
        return ADC_STATUS_ERROR;
    }

    adcContext.config = *pConfig;
    adcContext.initialized = true;
    AdcPort_SetSampleHandler(AdcDriverUnit_OnPortSample);

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

    if (enable && !AdcPort_ConfigureChannel((uint8_t)channel))
    {
        return ADC_STATUS_ERROR;
    }
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

    adcContext.conversionComplete = false;

    if ((adcContext.config.conversionMode == ADC_MODE_CONTINUOUS) && (adcContext.config.samplingFrequency > 0U))
    {
        if (!AdcPort_StartPeriodicSampling((uint8_t)channel, adcContext.config.samplingFrequency))
        {
            return ADC_STATUS_ERROR;
        }
        adcContext.busy = true;
        return ADC_STATUS_OK;
    }

    uint16_t value = 0U;
    if (!AdcPort_ReadRaw((uint8_t)channel, &value))
    {
        return ADC_STATUS_ERROR;
    }
    adcContext.lastValue[channel] = value;
    adcContext.conversionComplete = true;

    if (adcContext.config.enableInterrupt && adcContext.callback != NULL)
    {
        adcContext.callback(channel, value);
    }

    return ADC_STATUS_OK;
}

AdcDriver_Status_t AdcDriverUnit_StopConversion(void)
{
    if (!adcContext.initialized)
    {
        return ADC_STATUS_NOT_INITIALIZED;
    }

    AdcPort_StopPeriodicSampling();
    adcContext.busy = false;
    return ADC_STATUS_OK;
}

AdcDriver_Status_t AdcDriverUnit_ReadValue(AdcDriver_Channel_t channel, uint16_t *pValue)
{
    if (!adcContext.initialized)
    {
        return ADC_STATUS_NOT_INITIALIZED;
    }
    if (pValue == NULL || !AdcDriverUnit_IsValidChannel(channel) || !adcContext.channelEnabled[channel])
    {
        return ADC_STATUS_INVALID_PARAM;
    }

    uint16_t value = 0U;
    if (!AdcPort_ReadRaw((uint8_t)channel, &value))
    {
        return ADC_STATUS_ERROR;
    }
    adcContext.lastValue[channel] = value;
    *pValue = value;
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

    *pComplete = adcContext.conversionComplete;
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
    if (adcContext.initialized)
    {
        AdcPort_StopPeriodicSampling();
        AdcPort_DeInit();
    }
    (void)memset(&adcContext, 0, sizeof(adcContext));
    return ADC_STATUS_OK;
}

//============================================================================
// Local Function Implementations
//============================================================================

static bool AdcDriverUnit_IsValidChannel(AdcDriver_Channel_t channel)
{
    return (channel < ADC_MAX_CHANNELS);
}

static void AdcDriverUnit_OnPortSample(uint8_t channel, uint16_t value)
{
    if (channel >= ADC_MAX_CHANNELS)
    {
        return;
    }

    adcContext.lastValue[channel] = value;
    adcContext.conversionComplete = true;
    if (adcContext.callback != NULL)
    {
        adcContext.callback((AdcDriver_Channel_t)channel, value);
    }
}
