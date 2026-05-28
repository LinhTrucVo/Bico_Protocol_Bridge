// AnalogService Implementation - Typed ADC API

#include <stddef.h>
#include "analogService.h"
#include "analogServiceCfg.h"
#include "adcDriver.h"

typedef struct
{
    bool initialized;
} AnalogService_Context_t;

static AnalogService_Context_t context = {0};

AnalogService_Status_t AnalogServiceUnit_Init(void)
{
    AdcDriver_Config_t adcCfg = {0};
    adcCfg.resolution = ADC_RESOLUTION_12BIT;
    adcCfg.voltageReference = ADC_VREF_3V3;
    adcCfg.conversionMode = ADC_MODE_SINGLE;
    adcCfg.samplingFrequency = ADC_DEFAULT_SAMPLE_HZ;
    adcCfg.enableDMA = false;
    adcCfg.enableInterrupt = false;

    if (AdcDriverUnit_Init(&adcCfg) != ADC_STATUS_OK)
    {
        return ANALOGSERVICE_STATUS_ERROR;
    }

    for (uint8_t ch = 0U; ch < ANALOG_SERVICE_CFG_MAX_CHANNELS; ch++)
    {
        (void)AdcDriverUnit_ConfigureChannel((AdcDriver_Channel_t)ch, true);
    }

    context.initialized = true;
    return ANALOGSERVICE_STATUS_OK;
}

AnalogService_Status_t AnalogServiceUnit_DeInit(void)
{
    if (context.initialized)
    {
        (void)AdcDriverUnit_DeInit();
    }
    context.initialized = false;
    return ANALOGSERVICE_STATUS_OK;
}

AnalogService_Status_t AnalogServiceUnit_ReadAdc(uint8_t channel, uint16_t *pRawValue)
{
    if (!context.initialized)
    {
        return ANALOGSERVICE_STATUS_NOT_INITIALIZED;
    }
    if (pRawValue == NULL || channel >= ANALOG_SERVICE_CFG_MAX_CHANNELS)
    {
        return ANALOGSERVICE_STATUS_INVALID_PARAM;
    }

    AdcDriver_Channel_t adcChannel = (AdcDriver_Channel_t)channel;

    if (AdcDriverUnit_StartConversion(adcChannel) != ADC_STATUS_OK)
    {
        return ANALOGSERVICE_STATUS_ERROR;
    }

    /* Poll for conversion complete */
    bool complete = false;
    if (AdcDriverUnit_IsConversionComplete(adcChannel, &complete) != ADC_STATUS_OK)
    {
        return ANALOGSERVICE_STATUS_ERROR;
    }

    if (AdcDriverUnit_ReadValue(adcChannel, pRawValue) != ADC_STATUS_OK)
    {
        return ANALOGSERVICE_STATUS_ERROR;
    }

    return ANALOGSERVICE_STATUS_OK;
}