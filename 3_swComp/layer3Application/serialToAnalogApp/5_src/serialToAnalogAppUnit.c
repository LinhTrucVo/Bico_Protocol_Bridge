// SerialToAnalogApp Implementation - Typed ADC API

#include <stddef.h>
#include "serialToAnalogApp.h"
#include "serialToAnalogAppCfg.h"
#include "adcDriver.h"

typedef struct
{
    bool initialized;
} SerialToAnalogApp_Context_t;

static SerialToAnalogApp_Context_t context = {0};

SerialToAnalogApp_Status_t SerialToAnalogApp_Init(void)
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
        return SERIAL_TO_ANALOG_APP_STATUS_ERROR;
    }

    for (uint8_t ch = 0U; ch < SERIAL_TO_ANALOG_CFG_MAX_CHANNELS; ch++)
    {
        (void)AdcDriverUnit_ConfigureChannel((AdcDriver_Channel_t)ch, true);
    }

    context.initialized = true;
    return SERIAL_TO_ANALOG_APP_STATUS_OK;
}

SerialToAnalogApp_Status_t SerialToAnalogApp_DeInit(void)
{
    if (context.initialized)
    {
        (void)AdcDriverUnit_DeInit();
    }
    context.initialized = false;
    return SERIAL_TO_ANALOG_APP_STATUS_OK;
}

SerialToAnalogApp_Status_t SerialToAnalogApp_ReadAdc(uint8_t channel, uint16_t *pRawValue)
{
    if (!context.initialized)
    {
        return SERIAL_TO_ANALOG_APP_STATUS_NOT_INITIALIZED;
    }
    if (pRawValue == NULL || channel >= SERIAL_TO_ANALOG_CFG_MAX_CHANNELS)
    {
        return SERIAL_TO_ANALOG_APP_STATUS_INVALID_PARAM;
    }

    AdcDriver_Channel_t adcChannel = (AdcDriver_Channel_t)channel;

    if (AdcDriverUnit_StartConversion(adcChannel) != ADC_STATUS_OK)
    {
        return SERIAL_TO_ANALOG_APP_STATUS_ERROR;
    }

    /* Poll for conversion complete */
    bool complete = false;
    if (AdcDriverUnit_IsConversionComplete(adcChannel, &complete) != ADC_STATUS_OK)
    {
        return SERIAL_TO_ANALOG_APP_STATUS_ERROR;
    }

    if (AdcDriverUnit_ReadValue(adcChannel, pRawValue) != ADC_STATUS_OK)
    {
        return SERIAL_TO_ANALOG_APP_STATUS_ERROR;
    }

    return SERIAL_TO_ANALOG_APP_STATUS_OK;
}