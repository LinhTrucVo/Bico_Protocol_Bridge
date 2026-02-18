// PwmDriver Implementation
#include "pwmDriver.h"

typedef struct
{
    bool initialized;
    PwmDriver_ChannelConfig_t channelConfig[PWM_MAX_CHANNELS];
    bool channelRunning[PWM_MAX_CHANNELS];
} PwmDriver_Context_t;

static PwmDriver_Context_t context = {0};

PwmDriver_Status_t PwmDriverUnit_Init(void)
{
    // TODO: Add vendor-specific HAL initialization here
    context.initialized = true;
    for (uint8_t i = 0; i < PWM_MAX_CHANNELS; i++)
    {
        context.channelConfig[i].frequency = PWM_CFG_DEFAULT_FREQ_HZ;
        context.channelConfig[i].dutyCycle = PWM_CFG_DEFAULT_DUTY;
        context.channelConfig[i].polarity = PWM_POLARITY_NORMAL;
        context.channelConfig[i].alignment = PWM_ALIGNMENT_EDGE;
        context.channelConfig[i].enableDeadTime = false;
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

    context.channelConfig[channel] = *pConfig;
    return PWM_STATUS_OK;
}

PwmDriver_Status_t PwmDriverUnit_SetFrequency(PwmDriver_Channel_t channel, uint32_t frequency)
{
    if (!context.initialized)
    {
        return PWM_STATUS_NOT_INITIALIZED;
    }
    if (channel >= PWM_MAX_CHANNELS || frequency < PWM_MIN_FREQUENCY || frequency > PWM_MAX_FREQUENCY)
    {
        return PWM_STATUS_INVALID_PARAM;
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

    context.channelConfig[channel].polarity = polarity;
    return PWM_STATUS_OK;
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

    // TODO: Add vendor-specific HAL start here
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

    // TODO: Add vendor-specific HAL stop here
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
    // TODO: Add vendor-specific HAL deinitialization here
    context.initialized = false;
    return PWM_STATUS_OK;
}
