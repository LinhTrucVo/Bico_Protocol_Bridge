// SerialToDigitalApp Implementation

#include "serialToDigitalApp.h"
#include "serialToDigitalAppCfg.h"

typedef struct
{
    bool initialized;
    SerialToDigitalApp_State_t currentState;
    SerialToDigitalApp_PinConfig_t pinConfig[SERIAL_TO_DIGITAL_CFG_MAX_PINS];
    SerialToDigitalApp_StateValue_t pinState[SERIAL_TO_DIGITAL_CFG_MAX_PINS];
    SerialToDigitalApp_PwmConfig_t pwmConfig[SERIAL_TO_DIGITAL_CFG_MAX_PWM_CH];
} SerialToDigitalApp_Context_t;

static SerialToDigitalApp_Context_t context = {0};

SerialToDigitalApp_Status_t SerialToDigitalApp_Init(void)
{
    context.initialized = true;
    context.currentState = SerialToDigitalApp_STATE_IDLE;
    for (uint8_t i = 0; i < SERIAL_TO_DIGITAL_CFG_MAX_PINS; i++)
    
    {
        context.pinConfig[i].pinId = i;
        context.pinConfig[i].direction = SERIAL_TO_DIGITAL_DIR_INPUT;
        context.pinConfig[i].initialState = SERIAL_TO_DIGITAL_STATE_LOW;
        context.pinConfig[i].enablePullup = false;
        context.pinState[i] = SERIAL_TO_DIGITAL_STATE_LOW;
    }

    for (uint8_t i = 0; i < SERIAL_TO_DIGITAL_CFG_MAX_PWM_CH; i++)
    {
        context.pwmConfig[i].channelId = i;
        context.pwmConfig[i].frequency = SERIAL_TO_DIGITAL_CFG_DEFAULT_PWM_HZ;
        context.pwmConfig[i].dutyCycle = SERIAL_TO_DIGITAL_CFG_DEFAULT_DUTY;
        context.pwmConfig[i].enable = false;
    }
    return SERIAL_TO_DIGITAL_APP_STATUS_OK;
}

SerialToDigitalApp_Status_t SerialToDigitalApp_DeInit(void)
{
    context.initialized = false;
    context.currentState = SerialToDigitalApp_STATE_IDLE;
    return SERIAL_TO_DIGITAL_APP_STATUS_OK;
}

SerialToDigitalApp_Status_t SerialToDigitalApp_Run(void)
{
    if (!context.initialized)
    {
        return SERIAL_TO_DIGITAL_APP_STATUS_NOT_INITIALIZED;
    }
    return SERIAL_TO_DIGITAL_APP_STATUS_OK;
}

SerialToDigitalApp_Status_t SerialToDigitalApp_GetState(SerialToDigitalApp_State_t *pState)
{
    if (pState == NULL)
    {
        return SERIAL_TO_DIGITAL_APP_STATUS_INVALID_PARAM;
    }
    *pState = context.currentState;
    return SERIAL_TO_DIGITAL_APP_STATUS_OK;
}

SerialToDigitalApp_Status_t SerialToDigitalApp_ConfigurePin(const SerialToDigitalApp_PinConfig_t *pConfig)
{
    if (pConfig == NULL || pConfig->pinId >= SERIAL_TO_DIGITAL_CFG_MAX_PINS)
    {
        return SERIAL_TO_DIGITAL_APP_STATUS_INVALID_PARAM;
    }
    context.pinConfig[pConfig->pinId] = *pConfig;
    context.pinState[pConfig->pinId] = pConfig->initialState;
    return SERIAL_TO_DIGITAL_APP_STATUS_OK;
}

SerialToDigitalApp_Status_t SerialToDigitalApp_ReadPin(uint8_t pinId, SerialToDigitalApp_StateValue_t *pState)
{
    if (pState == NULL || pinId >= SERIAL_TO_DIGITAL_CFG_MAX_PINS)
    {
        return SERIAL_TO_DIGITAL_APP_STATUS_INVALID_PARAM;
    }
    *pState = context.pinState[pinId];
    return SERIAL_TO_DIGITAL_APP_STATUS_OK;
}

SerialToDigitalApp_Status_t SerialToDigitalApp_WritePin(uint8_t pinId, SerialToDigitalApp_StateValue_t state)
{
    if (pinId >= SERIAL_TO_DIGITAL_CFG_MAX_PINS)
    {
        return SERIAL_TO_DIGITAL_APP_STATUS_INVALID_PARAM;
    }
    context.pinState[pinId] = state;
    return SERIAL_TO_DIGITAL_APP_STATUS_OK;
}

SerialToDigitalApp_Status_t SerialToDigitalApp_ConfigurePwm(const SerialToDigitalApp_PwmConfig_t *pConfig)
{
    if (pConfig == NULL || pConfig->channelId >= SERIAL_TO_DIGITAL_CFG_MAX_PWM_CH)
    {
        return SERIAL_TO_DIGITAL_APP_STATUS_INVALID_PARAM;
    }
    context.pwmConfig[pConfig->channelId] = *pConfig;
    return SERIAL_TO_DIGITAL_APP_STATUS_OK;
}

SerialToDigitalApp_Status_t SerialToDigitalApp_StartPwm(uint8_t channelId)
{
    if (channelId >= SERIAL_TO_DIGITAL_CFG_MAX_PWM_CH)
    {
        return SERIAL_TO_DIGITAL_APP_STATUS_INVALID_PARAM;
    }
    context.pwmConfig[channelId].enable = true;
    return SERIAL_TO_DIGITAL_APP_STATUS_OK;
}

SerialToDigitalApp_Status_t SerialToDigitalApp_StopPwm(uint8_t channelId)
{
    if (channelId >= SERIAL_TO_DIGITAL_CFG_MAX_PWM_CH)
    {
        return SERIAL_TO_DIGITAL_APP_STATUS_INVALID_PARAM;
    }
    context.pwmConfig[channelId].enable = false;
    return SERIAL_TO_DIGITAL_APP_STATUS_OK;
}

SerialToDigitalApp_Status_t SerialToDigitalApp_SaveConfig(void)
{
    // TODO: Persist configuration using NvmService
    return SERIAL_TO_DIGITAL_APP_STATUS_OK;
}

SerialToDigitalApp_Status_t SerialToDigitalApp_LoadConfig(void)
{
    // TODO: Load configuration using NvmService
    return SERIAL_TO_DIGITAL_APP_STATUS_OK;
}
