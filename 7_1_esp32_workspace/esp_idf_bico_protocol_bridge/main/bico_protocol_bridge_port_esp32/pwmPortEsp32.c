// ESP32 implementation of the PWM port (pwmDriverPorting.h).

//============================================================================
// Dependencies
//============================================================================
#include <stddef.h>
#include <string.h>
#include "pwmDriverPorting.h"
#include "pwmPortEsp32Cfg.h"
#include "driver/ledc.h"

//============================================================================
// Local Macros
//============================================================================
#define PWM_PORT_DUTY_STEPS         (1UL << BICO_PROTOCOL_BRIDGE_PWM_DUTY_BITS)
#define PWM_PORT_NUM_CHANNELS       (sizeof(pwmPins) / sizeof(pwmPins[0]))

//============================================================================
// Variables
//============================================================================
static const int pwmPins[] = BICO_PROTOCOL_BRIDGE_PWM_CHANNEL_PINS;
static uint16_t pwmDuty[LEDC_CHANNEL_MAX] = {0};
static bool pwmConfigured[LEDC_CHANNEL_MAX] = {false};

//============================================================================
// Local Function Prototypes
//============================================================================
static bool PwmPort_IsValidChannel(uint8_t channel);
static uint32_t PwmPort_DutyToTicks(uint16_t duty);
static bool PwmPort_ApplyDuty(uint8_t channel);

//============================================================================
// Public Function Implementations
//============================================================================
bool PwmPort_Init(void)
{
    (void)memset(pwmDuty, 0, sizeof(pwmDuty));
    (void)memset(pwmConfigured, 0, sizeof(pwmConfigured));
    return true;
}

void PwmPort_DeInit(void)
{
    for (uint8_t i = 0U; i < (uint8_t)PWM_PORT_NUM_CHANNELS; i++)
    {
        if (pwmConfigured[i])
        {
            (void)ledc_stop(BICO_PROTOCOL_BRIDGE_PWM_SPEED_MODE, (ledc_channel_t)i, 0);
            pwmConfigured[i] = false;
        }
    }
}

bool PwmPort_ConfigureChannel(uint8_t channel, uint32_t frequencyHz, uint16_t duty, bool inverted)
{
    if (!PwmPort_IsValidChannel(channel))
    {
        return false;
    }

    const ledc_timer_config_t timerCfg = {
        .speed_mode = BICO_PROTOCOL_BRIDGE_PWM_SPEED_MODE,
        .timer_num = (ledc_timer_t)channel,
        .duty_resolution = (ledc_timer_bit_t)BICO_PROTOCOL_BRIDGE_PWM_DUTY_BITS,
        .freq_hz = frequencyHz,
        .clk_cfg = LEDC_AUTO_CLK,
    };
    if (ledc_timer_config(&timerCfg) != ESP_OK)
    {
        return false;
    }

    ledc_channel_config_t chanCfg = {
        .speed_mode = BICO_PROTOCOL_BRIDGE_PWM_SPEED_MODE,
        .channel = (ledc_channel_t)channel,
        .timer_sel = (ledc_timer_t)channel,
        .intr_type = LEDC_INTR_DISABLE,
        .gpio_num = pwmPins[channel],
        .duty = PwmPort_DutyToTicks(duty),
        .hpoint = 0,
    };
    chanCfg.flags.output_invert = inverted ? 1U : 0U;
    if (ledc_channel_config(&chanCfg) != ESP_OK)
    {
        return false;
    }

    pwmDuty[channel] = duty;
    pwmConfigured[channel] = true;
    return true;
}

bool PwmPort_SetFrequency(uint8_t channel, uint32_t frequencyHz)
{
    if (!PwmPort_IsValidChannel(channel) || !pwmConfigured[channel])
    {
        return false;
    }
    return (ledc_set_freq(BICO_PROTOCOL_BRIDGE_PWM_SPEED_MODE, (ledc_timer_t)channel, frequencyHz) == ESP_OK);
}

bool PwmPort_SetDuty(uint8_t channel, uint16_t duty)
{
    if (!PwmPort_IsValidChannel(channel) || !pwmConfigured[channel])
    {
        return false;
    }

    pwmDuty[channel] = duty;
    return PwmPort_ApplyDuty(channel);
}

bool PwmPort_Start(uint8_t channel)
{
    if (!PwmPort_IsValidChannel(channel) || !pwmConfigured[channel])
    {
        return false;
    }
    return PwmPort_ApplyDuty(channel);
}

bool PwmPort_Stop(uint8_t channel)
{
    if (!PwmPort_IsValidChannel(channel) || !pwmConfigured[channel])
    {
        return false;
    }
    return (ledc_stop(BICO_PROTOCOL_BRIDGE_PWM_SPEED_MODE, (ledc_channel_t)channel, 0) == ESP_OK);
}

//============================================================================
// Local Function Implementations
//============================================================================
static bool PwmPort_IsValidChannel(uint8_t channel)
{
    return (channel < PWM_PORT_NUM_CHANNELS) && (channel < (uint8_t)LEDC_CHANNEL_MAX) && (channel < (uint8_t)LEDC_TIMER_MAX);
}

static uint32_t PwmPort_DutyToTicks(uint16_t duty)
{
    const uint32_t maxTicks = PWM_PORT_DUTY_STEPS - 1UL;
    return ((uint32_t)duty * maxTicks) / (uint32_t)PWMPORT_DUTY_MAX;
}

static bool PwmPort_ApplyDuty(uint8_t channel)
{
    return (ledc_set_duty(BICO_PROTOCOL_BRIDGE_PWM_SPEED_MODE, (ledc_channel_t)channel, PwmPort_DutyToTicks(pwmDuty[channel])) == ESP_OK) &&
           (ledc_update_duty(BICO_PROTOCOL_BRIDGE_PWM_SPEED_MODE, (ledc_channel_t)channel) == ESP_OK);
}
