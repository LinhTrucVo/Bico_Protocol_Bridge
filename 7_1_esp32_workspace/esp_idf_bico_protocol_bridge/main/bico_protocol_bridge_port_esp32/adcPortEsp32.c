// ESP32 implementation of the ADC port (adcDriverPorting.h).

//============================================================================
// Dependencies
//============================================================================
#include <stddef.h>
#include "adcDriverPorting.h"
#include "adcPortEsp32Cfg.h"
#include "esp_adc/adc_oneshot.h"
#include "esp_timer.h"

//============================================================================
// Variables
//============================================================================
static adc_oneshot_unit_handle_t adcHandle = NULL;
static esp_timer_handle_t sampleTimer = NULL;
static AdcPort_SampleHandler_t sampleHandler = NULL;
static uint8_t activeChannel = 0U;

//============================================================================
// Local Function Prototypes
//============================================================================
static void AdcPort_OnSampleTimer(void *pArg);

//============================================================================
// Public Function Implementations
//============================================================================
bool AdcPort_Init(void)
{
    if (adcHandle != NULL)
    {
        return true;
    }

    const adc_oneshot_unit_init_cfg_t unitCfg = {
        .unit_id = BICO_PROTOCOL_BRIDGE_ADC_UNIT,
    };
    return (adc_oneshot_new_unit(&unitCfg, &adcHandle) == ESP_OK);
}

void AdcPort_DeInit(void)
{
    if (sampleTimer != NULL)
    {
        (void)esp_timer_stop(sampleTimer);
        (void)esp_timer_delete(sampleTimer);
        sampleTimer = NULL;
    }
    if (adcHandle != NULL)
    {
        (void)adc_oneshot_del_unit(adcHandle);
        adcHandle = NULL;
    }
    sampleHandler = NULL;
}

bool AdcPort_ConfigureChannel(uint8_t channel)
{
    if ((adcHandle == NULL) || (channel >= BICO_PROTOCOL_BRIDGE_ADC_NUM_CHANNELS))
    {
        return false;
    }

    const adc_oneshot_chan_cfg_t chanCfg = {
        .atten = BICO_PROTOCOL_BRIDGE_ADC_ATTEN,
        .bitwidth = BICO_PROTOCOL_BRIDGE_ADC_BITWIDTH,
    };
    return (adc_oneshot_config_channel(adcHandle, (adc_channel_t)channel, &chanCfg) == ESP_OK);
}

bool AdcPort_ReadRaw(uint8_t channel, uint16_t *pRawValue)
{
    if ((adcHandle == NULL) || (pRawValue == NULL) || (channel >= BICO_PROTOCOL_BRIDGE_ADC_NUM_CHANNELS))
    {
        return false;
    }

    int raw = 0;
    if (adc_oneshot_read(adcHandle, (adc_channel_t)channel, &raw) != ESP_OK)
    {
        return false;
    }
    *pRawValue = (uint16_t)raw;
    return true;
}

bool AdcPort_StartPeriodicSampling(uint8_t channel, uint32_t frequencyHz)
{
    if ((adcHandle == NULL) || (frequencyHz == 0U) || (channel >= BICO_PROTOCOL_BRIDGE_ADC_NUM_CHANNELS))
    {
        return false;
    }

    if (sampleTimer == NULL)
    {
        const esp_timer_create_args_t timerArgs = {
            .callback = AdcPort_OnSampleTimer,
            .name = "adcSample",
        };
        if (esp_timer_create(&timerArgs, &sampleTimer) != ESP_OK)
        {
            sampleTimer = NULL;
            return false;
        }
    }
    else
    {
        (void)esp_timer_stop(sampleTimer);
    }

    activeChannel = channel;
    uint64_t periodUs = 1000000ULL / (uint64_t)frequencyHz;
    if (periodUs == 0ULL)
    {
        periodUs = 1ULL;
    }
    return (esp_timer_start_periodic(sampleTimer, periodUs) == ESP_OK);
}

void AdcPort_StopPeriodicSampling(void)
{
    if (sampleTimer != NULL)
    {
        (void)esp_timer_stop(sampleTimer);
    }
}

void AdcPort_SetSampleHandler(AdcPort_SampleHandler_t handler)
{
    sampleHandler = handler;
}

//============================================================================
// Local Function Implementations
//============================================================================
static void AdcPort_OnSampleTimer(void *pArg)
{
    (void)pArg;

    uint16_t raw = 0U;
    if (AdcPort_ReadRaw(activeChannel, &raw) && (sampleHandler != NULL))
    {
        sampleHandler(activeChannel, raw);
    }
}
