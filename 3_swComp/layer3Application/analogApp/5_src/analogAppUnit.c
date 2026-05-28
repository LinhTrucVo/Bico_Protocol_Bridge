// ANALOGAPP Implementation - Typed ADC API

#include <stddef.h>
#include "ANALOGAPP.h"
#include "ANALOGAPPCfg.h"
#include "adcDriver.h"

typedef struct
{
    bool initialized;
} ANALOGAPP_Context_t;

static ANALOGAPP_Context_t context = {0};

ANALOGAPP_Status_t ANALOGAPP_Init(void)
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
        return ANALOG_APP_STATUS_ERROR;
    }

    for (uint8_t ch = 0U; ch < SERIAL_TO_ANALOG_CFG_MAX_CHANNELS; ch++)
    {
        (void)AdcDriverUnit_ConfigureChannel((AdcDriver_Channel_t)ch, true);
    }

    context.initialized = true;
    return ANALOG_APP_STATUS_OK;
}

ANALOGAPP_Status_t ANALOGAPP_DeInit(void)
{
    if (context.initialized)
    {
        (void)AdcDriverUnit_DeInit();
    }
    context.initialized = false;
    return ANALOG_APP_STATUS_OK;
}

ANALOGAPP_Status_t ANALOGAPP_ReadAdc(uint8_t channel, uint16_t *pRawValue)
{
    if (!context.initialized)
    {
        return ANALOG_APP_STATUS_NOT_INITIALIZED;
    }
    if (pRawValue == NULL || channel >= SERIAL_TO_ANALOG_CFG_MAX_CHANNELS)
    {
        return ANALOG_APP_STATUS_INVALID_PARAM;
    }

    AdcDriver_Channel_t adcChannel = (AdcDriver_Channel_t)channel;

    if (AdcDriverUnit_StartConversion(adcChannel) != ADC_STATUS_OK)
    {
        return ANALOG_APP_STATUS_ERROR;
    }

    /* Poll for conversion complete */
    bool complete = false;
    if (AdcDriverUnit_IsConversionComplete(adcChannel, &complete) != ADC_STATUS_OK)
    {
        return ANALOG_APP_STATUS_ERROR;
    }

    if (AdcDriverUnit_ReadValue(adcChannel, pRawValue) != ADC_STATUS_OK)
    {
        return ANALOG_APP_STATUS_ERROR;
    }

    return ANALOG_APP_STATUS_OK;
}