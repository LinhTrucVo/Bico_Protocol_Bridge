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
    adcCfg.resolution = BPB_ADC_RESOLUTION_12BIT;
    adcCfg.voltageReference = BPB_ADC_VREF_3V3;
    adcCfg.conversionMode = BPB_ADC_MODE_SINGLE;
    adcCfg.samplingFrequency = BPB_ADC_DEFAULT_SAMPLE_HZ;
    adcCfg.enableDMA = false;
    adcCfg.enableInterrupt = false;

    if (AdcDriverUnit_Init(&adcCfg) != BPB_ADC_STATUS_OK)
    {
        return BPB_ANALOGSERVICE_STATUS_ERROR;
    }

    for (uint8_t ch = 0U; ch < BPB_ANALOG_SERVICE_CFG_MAX_CHANNELS; ch++)
    {
        (void)AdcDriverUnit_ConfigureChannel((AdcDriver_Channel_t)ch, true);
    }

    context.initialized = true;
    return BPB_ANALOGSERVICE_STATUS_OK;
}

AnalogService_Status_t AnalogServiceUnit_DeInit(void)
{
    if (context.initialized)
    {
        (void)AdcDriverUnit_DeInit();
    }
    context.initialized = false;
    return BPB_ANALOGSERVICE_STATUS_OK;
}

AnalogService_Status_t AnalogServiceUnit_ReadAdc(uint8_t channel, uint16_t *pRawValue)
{
    if (!context.initialized)
    {
        return BPB_ANALOGSERVICE_STATUS_NOT_INITIALIZED;
    }
    if (pRawValue == NULL || channel >= BPB_ANALOG_SERVICE_CFG_MAX_CHANNELS)
    {
        return BPB_ANALOGSERVICE_STATUS_INVALID_PARAM;
    }

    AdcDriver_Channel_t adcChannel = (AdcDriver_Channel_t)channel;

    if (AdcDriverUnit_StartConversion(adcChannel) != BPB_ADC_STATUS_OK)
    {
        return BPB_ANALOGSERVICE_STATUS_ERROR;
    }

    /* Poll for conversion complete */
    bool complete = false;
    if (AdcDriverUnit_IsConversionComplete(adcChannel, &complete) != BPB_ADC_STATUS_OK)
    {
        return BPB_ANALOGSERVICE_STATUS_ERROR;
    }

    if (AdcDriverUnit_ReadValue(adcChannel, pRawValue) != BPB_ADC_STATUS_OK)
    {
        return BPB_ANALOGSERVICE_STATUS_ERROR;
    }

    return BPB_ANALOGSERVICE_STATUS_OK;
}