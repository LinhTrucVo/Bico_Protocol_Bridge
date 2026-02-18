// SerialToAnalogApp Implementation

#include <stddef.h>
#include "serialToAnalogApp.h"
#include "serialToAnalogAppCfg.h"

typedef struct
{
    bool initialized;
    SerialToAnalogApp_State_t currentState;
    SerialToAnalogApp_ChannelConfig_t channelCfg[SERIAL_TO_ANALOG_CFG_MAX_CHANNELS];
    SerialToAnalogApp_SampleBuffer_t sampleBuf[SERIAL_TO_ANALOG_CFG_MAX_CHANNELS];
    SerialToAnalogApp_ThresholdCallback_t thresholdCallback;
} SerialToAnalogApp_Context_t;

static SerialToAnalogApp_Context_t context = {0};

SerialToAnalogApp_Status_t SerialToAnalogApp_Init(void)
{
    context.initialized = true;
    context.currentState = SerialToAnalogApp_STATE_IDLE;
    context.thresholdCallback = NULL;
    for (uint8_t i = 0; i < SERIAL_TO_ANALOG_CFG_MAX_CHANNELS; i++)
    {
        context.channelCfg[i].channelId = i;
        context.channelCfg[i].enable = false;
        context.channelCfg[i].resolution = (SerialToAnalogApp_Resolution_t)SERIAL_TO_ANALOG_CFG_DEFAULT_RES;
        context.channelCfg[i].range = (SerialToAnalogApp_Range_t)SERIAL_TO_ANALOG_CFG_DEFAULT_RANGE;
        context.channelCfg[i].samplingFrequency = SERIAL_TO_ANALOG_CFG_MAX_SAMPLE_HZ;
        context.channelCfg[i].averageSamples = SERIAL_TO_ANALOG_CFG_DEFAULT_AVG;
        context.channelCfg[i].thresholdEnable = false;
        context.channelCfg[i].thresholdHigh = 0.0f;
        context.channelCfg[i].thresholdLow = 0.0f;
        context.sampleBuf[i].channelId = i;
        context.sampleBuf[i].sampleCount = 0;
    }
    return SERIAL_TO_ANALOG_APP_STATUS_OK;
}

SerialToAnalogApp_Status_t SerialToAnalogApp_DeInit(void)
{
    context.initialized = false;
    context.currentState = SerialToAnalogApp_STATE_IDLE;
    return SERIAL_TO_ANALOG_APP_STATUS_OK;
}

SerialToAnalogApp_Status_t SerialToAnalogApp_Run(void)
{
    if (!context.initialized)
    {
        return SERIAL_TO_ANALOG_APP_STATUS_NOT_INITIALIZED;
    }
    return SERIAL_TO_ANALOG_APP_STATUS_OK;
}

SerialToAnalogApp_Status_t SerialToAnalogApp_GetState(SerialToAnalogApp_State_t *pState)
{
    if (pState == NULL)
    {
        return SERIAL_TO_ANALOG_APP_STATUS_INVALID_PARAM;
    }
    *pState = context.currentState;
    return SERIAL_TO_ANALOG_APP_STATUS_OK;
}

SerialToAnalogApp_Status_t SerialToAnalogApp_ConfigureChannel(const SerialToAnalogApp_ChannelConfig_t *pConfig)
{
    if (!context.initialized)
    {
        return SERIAL_TO_ANALOG_APP_STATUS_NOT_INITIALIZED;
    }
    if (pConfig == NULL || pConfig->channelId >= SERIAL_TO_ANALOG_CFG_MAX_CHANNELS)
    {
        return SERIAL_TO_ANALOG_APP_STATUS_INVALID_PARAM;
    }
    context.channelCfg[pConfig->channelId] = *pConfig;
    return SERIAL_TO_ANALOG_APP_STATUS_OK;
}

SerialToAnalogApp_Status_t SerialToAnalogApp_GetChannelConfig(uint8_t channelId, SerialToAnalogApp_ChannelConfig_t *pConfig)
{
    if (pConfig == NULL || channelId >= SERIAL_TO_ANALOG_CFG_MAX_CHANNELS)
    {
        return SERIAL_TO_ANALOG_APP_STATUS_INVALID_PARAM;
    }
    *pConfig = context.channelCfg[channelId];
    return SERIAL_TO_ANALOG_APP_STATUS_OK;
}

SerialToAnalogApp_Status_t SerialToAnalogApp_StartSampling(uint8_t channelId)
{
    if (channelId >= SERIAL_TO_ANALOG_CFG_MAX_CHANNELS)
    {
        return SERIAL_TO_ANALOG_APP_STATUS_INVALID_PARAM;
    }
    context.channelCfg[channelId].enable = true;
    context.currentState = SerialToAnalogApp_STATE_SAMPLING;
    return SERIAL_TO_ANALOG_APP_STATUS_OK;
}

SerialToAnalogApp_Status_t SerialToAnalogApp_StopSampling(uint8_t channelId)
{
    if (channelId >= SERIAL_TO_ANALOG_CFG_MAX_CHANNELS)
    {
        return SERIAL_TO_ANALOG_APP_STATUS_INVALID_PARAM;
    }
    context.channelCfg[channelId].enable = false;
    context.currentState = SerialToAnalogApp_STATE_IDLE;
    return SERIAL_TO_ANALOG_APP_STATUS_OK;
}

SerialToAnalogApp_Status_t SerialToAnalogApp_ReadSamples(uint8_t channelId, SerialToAnalogApp_SampleBuffer_t *pBuffer)
{
    if (pBuffer == NULL || channelId >= SERIAL_TO_ANALOG_CFG_MAX_CHANNELS)
    {
        return SERIAL_TO_ANALOG_APP_STATUS_INVALID_PARAM;
    }
    *pBuffer = context.sampleBuf[channelId];
    return SERIAL_TO_ANALOG_APP_STATUS_OK;
}

SerialToAnalogApp_Status_t SerialToAnalogApp_RegisterThresholdCallback(SerialToAnalogApp_ThresholdCallback_t callback)
{
    context.thresholdCallback = callback;
    return SERIAL_TO_ANALOG_APP_STATUS_OK;
}

SerialToAnalogApp_Status_t SerialToAnalogApp_SaveConfig(void)
{
    // TODO: Persist configuration using NvmService
    return SERIAL_TO_ANALOG_APP_STATUS_OK;
}

SerialToAnalogApp_Status_t SerialToAnalogApp_LoadConfig(void)
{
    // TODO: Load configuration using NvmService
    return SERIAL_TO_ANALOG_APP_STATUS_OK;
}

SerialToAnalogApp_Status_t SerialToAnalogApp_ProcessFrame(const uint8_t *pFrame, uint16_t frameLength, uint8_t *pResponse, uint16_t *pResponseLength)
{
    (void)pFrame;
    (void)frameLength;
    (void)pResponse;
    (void)pResponseLength;
    return SERIAL_TO_ANALOG_APP_STATUS_OK;
}
