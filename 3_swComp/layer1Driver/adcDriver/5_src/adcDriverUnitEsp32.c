// ESP32 variant implementation for AdcDriver. (adcDriverUnitEsp32.c)
// This file provides the ESP32-specific implementation of the AdcDriver interface.
// Selected when L1_VARIANT is set to "Esp32" in the CMake build configuration.

//============================================================================
// Dependencies
//============================================================================
#include "adcDriver.h"
#include "adcDriverCfg.h"
#include "adcDriverUnit.h"
#include "esp_adc/adc_oneshot.h"
#include "esp_adc/adc_cali.h"
#include "esp_adc/adc_cali_scheme.h"
#include "esp_timer.h"
#include <string.h>

//============================================================================
// Internal Types
//============================================================================
typedef struct
{
    bool                           initialized;
    adc_oneshot_unit_handle_t      adcHandle;
    adc_cali_handle_t              caliHandle;
    AdcDriver_Config_t             config;
    bool                           channelEnabled[ADC_MAX_CHANNELS];
    bool                           conversionComplete;
    AdcDriver_ConversionCallback_t callback;
    esp_timer_handle_t             sampleTimer;
    AdcDriver_Channel_t            activeChannel;
    AdcDriver_Status_t             lastStatus;
} AdcDriver_Context_t;

static AdcDriver_Context_t context = {0};

//============================================================================
// Internal Functions
//============================================================================
static void SampleTimerCallback(void *arg)
{
    (void)arg;
    uint16_t value = 0U;
    (void)AdcDriverUnit_ReadValue(context.activeChannel, &value);
    context.conversionComplete = true;
    if (context.callback != NULL)
    {
        context.callback(context.activeChannel, value);
    }
}

//============================================================================
// Public Functions
//============================================================================
AdcDriver_Status_t AdcDriverUnit_Init(const AdcDriver_Config_t *pConfig)
{
    if (pConfig == NULL) { return ADC_STATUS_ERROR; }

    adc_oneshot_unit_init_cfg_t unitCfg = { .unit_id = ADC_UNIT_1 };
    if (adc_oneshot_new_unit(&unitCfg, &context.adcHandle) != ESP_OK)
    {
        return ADC_STATUS_ERROR;
    }
    adc_cali_curve_fitting_config_t caliCfg = {
        .unit_id  = ADC_UNIT_1,
        .atten    = ADC_ATTEN_DB_12,
        .bitwidth = ADC_BITWIDTH_DEFAULT,
    };
    (void)adc_cali_create_scheme_curve_fitting(&caliCfg, &context.caliHandle);

    (void)memcpy(&context.config, pConfig, sizeof(AdcDriver_Config_t));
    context.initialized = true;
    context.lastStatus  = ADC_STATUS_OK;
    return ADC_STATUS_OK;
}

AdcDriver_Status_t AdcDriverUnit_ConfigureChannel(AdcDriver_Channel_t channel, bool enable)
{
    if (!context.initialized) { return ADC_STATUS_NOT_INITIALIZED; }
    if ((uint8_t)channel >= ADC_MAX_CHANNELS) { return ADC_STATUS_INVALID_PARAM; }

    if (enable)
    {
        adc_oneshot_chan_cfg_t chanCfg = {
            .atten    = ADC_ATTEN_DB_12,
            .bitwidth = ADC_BITWIDTH_DEFAULT,
        };
        if (adc_oneshot_config_channel(context.adcHandle, (adc_channel_t)channel, &chanCfg) != ESP_OK)
        {
            return ADC_STATUS_ERROR;
        }
    }
    context.channelEnabled[(uint8_t)channel] = enable;
    return ADC_STATUS_OK;
}

AdcDriver_Status_t AdcDriverUnit_SetResolution(AdcDriver_Resolution_t resolution)
{
    if (!context.initialized) { return ADC_STATUS_NOT_INITIALIZED; }
    context.config.resolution = resolution;
    return ADC_STATUS_OK; /* Fixed at 12-bit on ESP32; stored for external scaling */
}

AdcDriver_Status_t AdcDriverUnit_SetVoltageReference(AdcDriver_VoltageRef_t voltageRef)
{
    (void)voltageRef;
    return ADC_STATUS_OK; /* Not configurable on ESP32 */
}

AdcDriver_Status_t AdcDriverUnit_SetSamplingFrequency(uint32_t frequency)
{
    if (!context.initialized) { return ADC_STATUS_NOT_INITIALIZED; }
    context.config.samplingFrequency = frequency;
    return ADC_STATUS_OK;
}

AdcDriver_Status_t AdcDriverUnit_StartConversion(AdcDriver_Channel_t channel)
{
    if (!context.initialized) { return ADC_STATUS_NOT_INITIALIZED; }
    if ((uint8_t)channel >= ADC_MAX_CHANNELS) { return ADC_STATUS_INVALID_PARAM; }

    context.activeChannel      = channel;
    context.conversionComplete = false;

    if (context.config.conversionMode == ADC_MODE_CONTINUOUS && context.config.samplingFrequency > 0U)
    {
        esp_timer_create_args_t timerArgs = {
            .callback = SampleTimerCallback,
            .name     = "adc_sample",
        };
        if (context.sampleTimer == NULL)
        {
            (void)esp_timer_create(&timerArgs, &context.sampleTimer);
        }
        uint64_t periodUs = 1000000ULL / (uint64_t)context.config.samplingFrequency;
        (void)esp_timer_start_periodic(context.sampleTimer, periodUs);
    }
    else
    {
        int raw = 0;
        if (adc_oneshot_read(context.adcHandle, (adc_channel_t)channel, &raw) != ESP_OK)
        {
            return ADC_STATUS_ERROR;
        }
        context.conversionComplete = true;
        if (context.callback != NULL)
        {
            context.callback(channel, (uint16_t)raw);
        }
    }
    return ADC_STATUS_OK;
}

AdcDriver_Status_t AdcDriverUnit_StopConversion(void)
{
    if (!context.initialized) { return ADC_STATUS_NOT_INITIALIZED; }
    if (context.sampleTimer != NULL)
    {
        (void)esp_timer_stop(context.sampleTimer);
    }
    return ADC_STATUS_OK;
}

AdcDriver_Status_t AdcDriverUnit_ReadValue(AdcDriver_Channel_t channel, uint16_t *pValue)
{
    if (!context.initialized) { return ADC_STATUS_NOT_INITIALIZED; }
    if (pValue == NULL) { return ADC_STATUS_INVALID_PARAM; }

    int raw = 0;
    if (adc_oneshot_read(context.adcHandle, (adc_channel_t)channel, &raw) != ESP_OK)
    {
        return ADC_STATUS_ERROR;
    }
    context.conversionComplete = true;
    *pValue = (uint16_t)raw;
    return ADC_STATUS_OK;
}

AdcDriver_Status_t AdcDriverUnit_IsConversionComplete(AdcDriver_Channel_t channel, bool *pComplete)
{
    (void)channel;
    if (!context.initialized) { return ADC_STATUS_NOT_INITIALIZED; }
    if (pComplete == NULL) { return ADC_STATUS_INVALID_PARAM; }
    *pComplete = context.conversionComplete;
    return ADC_STATUS_OK;
}

AdcDriver_Status_t AdcDriverUnit_RegisterCallback(AdcDriver_ConversionCallback_t callback)
{
    if (!context.initialized) { return ADC_STATUS_NOT_INITIALIZED; }
    context.callback = callback;
    return ADC_STATUS_OK;
}

AdcDriver_Status_t AdcDriverUnit_GetStatus(AdcDriver_Status_t *pStatus)
{
    if (pStatus == NULL) { return ADC_STATUS_INVALID_PARAM; }
    *pStatus = context.lastStatus;
    return ADC_STATUS_OK;
}

AdcDriver_Status_t AdcDriverUnit_DeInit(void)
{
    if (context.sampleTimer != NULL)
    {
        (void)esp_timer_stop(context.sampleTimer);
        (void)esp_timer_delete(context.sampleTimer);
        context.sampleTimer = NULL;
    }
    if (context.caliHandle != NULL)
    {
        (void)adc_cali_delete_scheme_curve_fitting(context.caliHandle);
        context.caliHandle = NULL;
    }
    if (context.adcHandle != NULL)
    {
        (void)adc_oneshot_del_unit(context.adcHandle);
        context.adcHandle = NULL;
    }
    context.initialized = false;
    return ADC_STATUS_OK;
}
