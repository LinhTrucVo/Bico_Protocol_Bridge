// ESP32 variant implementation for PwmDriver. (pwmDriverUnitEsp32.c)
// This file provides the ESP32-specific implementation of the PwmDriver interface.
// Selected when L1_VARIANT is set to "Esp32" in the CMake build configuration.

//============================================================================
// Dependencies
//============================================================================
#include "pwmDriver.h"
#include "pwmDriverCfg.h"
#include "pwmDriverUnit.h"
#include "driver/ledc.h"
#include <string.h>

//============================================================================
// Internal Defines
//============================================================================
#define PWM_ESP32_RESOLUTION_BITS   LEDC_TIMER_13_BIT
#define PWM_ESP32_MAX_DUTY          ((1U << 13) - 1U)   /* 8191 */
#define PWM_ESP32_SPEED_MODE        LEDC_LOW_SPEED_MODE

//============================================================================
// Internal Types
//============================================================================
typedef struct
{
    PwmDriver_ChannelConfig_t config;
    bool                      configured;
    bool                      running;
} PwmDriver_ChannelState_t;

typedef struct
{
    bool                    initialized;
    PwmDriver_ChannelState_t channels[PWM_MAX_CHANNELS];
} PwmDriver_Context_t;

static PwmDriver_Context_t context = {0};

//============================================================================
// Internal Functions
//============================================================================
static uint32_t DutyCycleToLedc(uint16_t duty)
{
    /* Map 0-PWM_MAX_DUTY_CYCLE (10000) to 0-PWM_ESP32_MAX_DUTY (8191) */
    return ((uint32_t)duty * PWM_ESP32_MAX_DUTY) / (uint32_t)PWM_MAX_DUTY_CYCLE;
}

//============================================================================
// Public Functions
//============================================================================
PwmDriver_Status_t PwmDriverUnit_Init(const PwmDriver_Config_t *pConfig)
{
    if (pConfig == NULL) { return PWMDRIVER_ERROR; }
    (void)memset(&context, 0, sizeof(context));
    context.initialized = true;
    return PWMDRIVER_OK;
}

PwmDriver_Status_t PwmDriverUnit_ConfigureChannel(PwmDriver_Channel_t channel, const PwmDriver_ChannelConfig_t *pConfig)
{
    if (!context.initialized) { return PWMDRIVER_NOT_INITIALIZED; }
    if ((uint8_t)channel >= PWM_MAX_CHANNELS || pConfig == NULL) { return PWMDRIVER_INVALID_CHANNEL; }
    if (pConfig->frequency < PWM_MIN_FREQUENCY || pConfig->frequency > PWM_MAX_FREQUENCY)
    {
        return PWMDRIVER_INVALID_FREQUENCY;
    }

    ledc_timer_config_t timerCfg = {
        .speed_mode      = PWM_ESP32_SPEED_MODE,
        .timer_num       = (ledc_timer_t)channel,
        .duty_resolution = PWM_ESP32_RESOLUTION_BITS,
        .freq_hz         = pConfig->frequency,
        .clk_cfg         = LEDC_AUTO_CLK,
    };
    if (ledc_timer_config(&timerCfg) != ESP_OK) { return PWMDRIVER_ERROR; }

    ledc_channel_config_t chanCfg = {
        .speed_mode     = PWM_ESP32_SPEED_MODE,
        .channel        = (ledc_channel_t)channel,
        .timer_sel      = (ledc_timer_t)channel,
        .intr_type      = LEDC_INTR_DISABLE,
        .gpio_num       = 0,  /* Pin assignment done separately via GPIO driver */
        .duty           = DutyCycleToLedc(pConfig->dutyCycle),
        .hpoint         = 0,
        .flags.output_invert = (pConfig->polarity == PWM_POLARITY_INVERTED) ? 1U : 0U,
    };
    if (ledc_channel_config(&chanCfg) != ESP_OK) { return PWMDRIVER_ERROR; }

    (void)memcpy(&context.channels[(uint8_t)channel].config, pConfig, sizeof(PwmDriver_ChannelConfig_t));
    context.channels[(uint8_t)channel].configured = true;
    return PWMDRIVER_OK;
}

PwmDriver_Status_t PwmDriverUnit_SetFrequency(PwmDriver_Channel_t channel, uint32_t frequency)
{
    if (!context.initialized) { return PWMDRIVER_NOT_INITIALIZED; }
    if ((uint8_t)channel >= PWM_MAX_CHANNELS) { return PWMDRIVER_INVALID_CHANNEL; }
    if (frequency < PWM_MIN_FREQUENCY || frequency > PWM_MAX_FREQUENCY) { return PWMDRIVER_INVALID_FREQUENCY; }

    if (ledc_set_freq(PWM_ESP32_SPEED_MODE, (ledc_timer_t)channel, frequency) != ESP_OK)
    {
        return PWMDRIVER_ERROR;
    }
    context.channels[(uint8_t)channel].config.frequency = frequency;
    return PWMDRIVER_OK;
}

PwmDriver_Status_t PwmDriverUnit_SetDutyCycle(PwmDriver_Channel_t channel, uint16_t dutyCycle)
{
    if (!context.initialized) { return PWMDRIVER_NOT_INITIALIZED; }
    if ((uint8_t)channel >= PWM_MAX_CHANNELS) { return PWMDRIVER_INVALID_CHANNEL; }
    if (dutyCycle > PWM_MAX_DUTY_CYCLE) { return PWMDRIVER_ERROR; }

    if (ledc_set_duty(PWM_ESP32_SPEED_MODE, (ledc_channel_t)channel, DutyCycleToLedc(dutyCycle)) != ESP_OK ||
        ledc_update_duty(PWM_ESP32_SPEED_MODE, (ledc_channel_t)channel) != ESP_OK)
    {
        return PWMDRIVER_ERROR;
    }
    context.channels[(uint8_t)channel].config.dutyCycle = dutyCycle;
    return PWMDRIVER_OK;
}

PwmDriver_Status_t PwmDriverUnit_SetPolarity(PwmDriver_Channel_t channel, PwmDriver_Polarity_t polarity)
{
    if (!context.initialized) { return PWMDRIVER_NOT_INITIALIZED; }
    if ((uint8_t)channel >= PWM_MAX_CHANNELS) { return PWMDRIVER_INVALID_CHANNEL; }
    /* Polarity requires reconfiguration of the channel */
    context.channels[(uint8_t)channel].config.polarity = polarity;
    return PwmDriverUnit_ConfigureChannel(channel, &context.channels[(uint8_t)channel].config);
}

PwmDriver_Status_t PwmDriverUnit_StartChannel(PwmDriver_Channel_t channel)
{
    if (!context.initialized) { return PWMDRIVER_NOT_INITIALIZED; }
    if ((uint8_t)channel >= PWM_MAX_CHANNELS) { return PWMDRIVER_INVALID_CHANNEL; }

    uint32_t duty = DutyCycleToLedc(context.channels[(uint8_t)channel].config.dutyCycle);
    if (ledc_set_duty(PWM_ESP32_SPEED_MODE, (ledc_channel_t)channel, duty) != ESP_OK ||
        ledc_update_duty(PWM_ESP32_SPEED_MODE, (ledc_channel_t)channel) != ESP_OK)
    {
        return PWMDRIVER_ERROR;
    }
    context.channels[(uint8_t)channel].running = true;
    return PWMDRIVER_OK;
}

PwmDriver_Status_t PwmDriverUnit_StopChannel(PwmDriver_Channel_t channel)
{
    if (!context.initialized) { return PWMDRIVER_NOT_INITIALIZED; }
    if ((uint8_t)channel >= PWM_MAX_CHANNELS) { return PWMDRIVER_INVALID_CHANNEL; }

    if (ledc_stop(PWM_ESP32_SPEED_MODE, (ledc_channel_t)channel, 0) != ESP_OK) { return PWMDRIVER_ERROR; }
    context.channels[(uint8_t)channel].running = false;
    return PWMDRIVER_OK;
}

PwmDriver_Status_t PwmDriverUnit_GetConfiguration(PwmDriver_Channel_t channel, PwmDriver_ChannelConfig_t *pConfig)
{
    if (!context.initialized) { return PWMDRIVER_NOT_INITIALIZED; }
    if ((uint8_t)channel >= PWM_MAX_CHANNELS || pConfig == NULL) { return PWMDRIVER_INVALID_CHANNEL; }
    (void)memcpy(pConfig, &context.channels[(uint8_t)channel].config, sizeof(PwmDriver_ChannelConfig_t));
    return PWMDRIVER_OK;
}

PwmDriver_Status_t PwmDriverUnit_IsChannelRunning(PwmDriver_Channel_t channel, bool *pIsRunning)
{
    if (!context.initialized) { return PWMDRIVER_NOT_INITIALIZED; }
    if ((uint8_t)channel >= PWM_MAX_CHANNELS || pIsRunning == NULL) { return PWMDRIVER_INVALID_CHANNEL; }
    *pIsRunning = context.channels[(uint8_t)channel].running;
    return PWMDRIVER_OK;
}

PwmDriver_Status_t PwmDriverUnit_DeInit(void)
{
    for (uint8_t i = 0U; i < PWM_MAX_CHANNELS; i++)
    {
        if (context.channels[i].configured)
        {
            (void)ledc_stop(PWM_ESP32_SPEED_MODE, (ledc_channel_t)i, 0);
        }
    }
    (void)memset(&context, 0, sizeof(context));
    return PWMDRIVER_OK;
}
