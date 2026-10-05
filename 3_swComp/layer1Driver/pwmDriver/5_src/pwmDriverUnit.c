// PwmDriver Implementation
#include <stddef.h>
#include <string.h>
#include "pwmDriver.h"
#include "pwmDriverPorting.h"

typedef struct
{
    bool initialized;
    PwmDriver_ChannelConfig_t channelConfig[PWM_MAX_CHANNELS];
    bool channelRunning[PWM_MAX_CHANNELS];
} PwmDriver_Context_t;

static PwmDriver_Context_t context = {0};

static bool PwmDriverUnit_IsValidFrequency(uint32_t frequency);

PwmDriver_Status_t PwmDriverUnit_Init(const PwmDriver_Config_t *pConfig)
{
    if (pConfig == NULL)
    {
        return PWM_STATUS_ERROR;
    }
    if (context.initialized)
    {
        PwmPort_DeInit();
    }

    (void)memset(&context, 0, sizeof(context));
    if (!PwmPort_Init())
    {
        return PWM_STATUS_ERROR;
    }

    context.initialized = true;
    for (uint8_t i = 0; i < PWM_MAX_CHANNELS; i++)
    {
        context.channelConfig[i].frequency = PWM_CFG_DEFAULT_FREQ_HZ;
        context.channelConfig[i].dutyCycle = PWM_CFG_DEFAULT_DUTY;
        context.channelConfig[i].polarity = PWM_POLARITY_NORMAL;
        context.channelConfig[i].alignment = PWM_ALIGNMENT_EDGE;
        context.channelConfig[i].dmaEnabled = pConfig->enableDma;
        context.channelConfig[i].enableDeadTime = pConfig->enableDeadTime;
        context.channelConfig[i].deadTimeNs = 0;
        context.channelRunning[i] = false;
    }
    return PWM_STATUS_OK;
}

PwmDriver_Status_t PwmDriverUnit_ConfigureChannel(PwmDriver_Channel_t channel, const PwmDriver_ChannelConfig_t *pConfig)
{
    if (!context.initialized)
    {
        return PWM_STATUS_NOT_INITIALIZED;
    }
    if (pConfig == NULL || channel >= PWM_MAX_CHANNELS)
    {
        return PWM_STATUS_INVALID_CHANNEL;
    }
    if (!PwmDriverUnit_IsValidFrequency(pConfig->frequency))
    {
        return PWM_STATUS_INVALID_FREQUENCY;
    }
    if (pConfig->dutyCycle > PWM_MAX_DUTY_CYCLE)
    {
        return PWM_STATUS_INVALID_PARAM;
    }

    if (!PwmPort_ConfigureChannel((uint8_t)channel, pConfig->frequency, pConfig->dutyCycle,
                                  pConfig->polarity == PWM_POLARITY_INVERTED))
    {
        return PWM_STATUS_ERROR;
    }
    context.channelConfig[channel] = *pConfig;
    context.channelRunning[channel] = true;
    return PWM_STATUS_OK;
}

PwmDriver_Status_t PwmDriverUnit_SetFrequency(PwmDriver_Channel_t channel, uint32_t frequency)
{
    if (!context.initialized)
    {
        return PWM_STATUS_NOT_INITIALIZED;
    }
    if (channel >= PWM_MAX_CHANNELS || !PwmDriverUnit_IsValidFrequency(frequency))
    {
        return PWM_STATUS_INVALID_PARAM;
    }

    if (!PwmPort_SetFrequency((uint8_t)channel, frequency))
    {
        return PWM_STATUS_ERROR;
    }
    context.channelConfig[channel].frequency = frequency;
    return PWM_STATUS_OK;
}

PwmDriver_Status_t PwmDriverUnit_SetDutyCycle(PwmDriver_Channel_t channel, uint16_t dutyCycle)
{
    if (!context.initialized)
    {
        return PWM_STATUS_NOT_INITIALIZED;
    }
    if (channel >= PWM_MAX_CHANNELS || dutyCycle > PWM_MAX_DUTY_CYCLE)
    {
        return PWM_STATUS_INVALID_PARAM;
    }

    if (!PwmPort_SetDuty((uint8_t)channel, dutyCycle))
    {
        return PWM_STATUS_ERROR;
    }
    context.channelConfig[channel].dutyCycle = dutyCycle;
    return PWM_STATUS_OK;
}

PwmDriver_Status_t PwmDriverUnit_SetPolarity(PwmDriver_Channel_t channel, PwmDriver_Polarity_t polarity)
{
    if (!context.initialized)
    {
        return PWM_STATUS_NOT_INITIALIZED;
    }
    if (channel >= PWM_MAX_CHANNELS)
    {
        return PWM_STATUS_INVALID_CHANNEL;
    }

    // The polarity is part of the channel setup, so the channel is configured again.
    PwmDriver_ChannelConfig_t updated = context.channelConfig[channel];
    updated.polarity = polarity;
    return PwmDriverUnit_ConfigureChannel(channel, &updated);
}

PwmDriver_Status_t PwmDriverUnit_StartChannel(PwmDriver_Channel_t channel)
{
    if (!context.initialized)
    {
        return PWM_STATUS_NOT_INITIALIZED;
    }
    if (channel >= PWM_MAX_CHANNELS)
    {
        return PWM_STATUS_INVALID_CHANNEL;
    }

    if (!PwmPort_Start((uint8_t)channel))
    {
        return PWM_STATUS_ERROR;
    }
    context.channelRunning[channel] = true;
    return PWM_STATUS_OK;
}

PwmDriver_Status_t PwmDriverUnit_StopChannel(PwmDriver_Channel_t channel)
{
    if (!context.initialized)
    {
        return PWM_STATUS_NOT_INITIALIZED;
    }
    if (channel >= PWM_MAX_CHANNELS)
    {
        return PWM_STATUS_INVALID_CHANNEL;
    }

    if (!PwmPort_Stop((uint8_t)channel))
    {
        return PWM_STATUS_ERROR;
    }
    context.channelRunning[channel] = false;
    return PWM_STATUS_OK;
}

PwmDriver_Status_t PwmDriverUnit_GetConfiguration(PwmDriver_Channel_t channel, PwmDriver_ChannelConfig_t *pConfig)
{
    if (!context.initialized)
    {
        return PWM_STATUS_NOT_INITIALIZED;
    }
    if (pConfig == NULL || channel >= PWM_MAX_CHANNELS)
    {
        return PWM_STATUS_INVALID_CHANNEL;
    }

    *pConfig = context.channelConfig[channel];
    return PWM_STATUS_OK;
}

PwmDriver_Status_t PwmDriverUnit_IsChannelRunning(PwmDriver_Channel_t channel, bool *pIsRunning)
{
    if (!context.initialized)
    {
        return PWM_STATUS_NOT_INITIALIZED;
    }
    if (pIsRunning == NULL || channel >= PWM_MAX_CHANNELS)
    {
        return PWM_STATUS_INVALID_CHANNEL;
    }

    *pIsRunning = context.channelRunning[channel];
    return PWM_STATUS_OK;
}

PwmDriver_Status_t PwmDriverUnit_DeInit(void)
{
    if (context.initialized)
    {
        PwmPort_DeInit();
    }
    (void)memset(&context, 0, sizeof(context));
    return PWM_STATUS_OK;
}

static bool PwmDriverUnit_IsValidFrequency(uint32_t frequency)
{
    return (frequency >= PWM_MIN_FREQUENCY) && (frequency <= PWM_MAX_FREQUENCY);
}
