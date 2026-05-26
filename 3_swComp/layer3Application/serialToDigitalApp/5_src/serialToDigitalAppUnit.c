// SerialToDigitalApp Implementation - Typed GPIO/PWM API

#include <stddef.h>
#include "serialToDigitalApp.h"
#include "serialToDigitalAppCfg.h"

typedef struct
{
    bool initialized;
    uint8_t pinState[SERIAL_TO_DIGITAL_CFG_MAX_PINS];
    bool pwmRunning[SERIAL_TO_DIGITAL_CFG_MAX_PWM_CH];
} SerialToDigitalApp_Context_t;

static SerialToDigitalApp_Context_t context = {0};

SerialToDigitalApp_Status_t SerialToDigitalApp_Init(void)
{
    context.initialized = true;
    /* TODO: Initialize GPIO/PWM drivers from ConfigService */
    for (uint8_t i = 0U; i < SERIAL_TO_DIGITAL_CFG_MAX_PINS; i++)
    {
        context.pinState[i] = 0U;
    }
    for (uint8_t i = 0U; i < SERIAL_TO_DIGITAL_CFG_MAX_PWM_CH; i++)
    {
        context.pwmRunning[i] = false;
    }
    return SERIAL_TO_DIGITAL_APP_STATUS_OK;
}

SerialToDigitalApp_Status_t SerialToDigitalApp_DeInit(void)
{
    context.initialized = false;
    return SERIAL_TO_DIGITAL_APP_STATUS_OK;
}

SerialToDigitalApp_Status_t SerialToDigitalApp_WriteGpio(uint8_t pin, uint8_t state)
{
    if (!context.initialized)
    {
        return SERIAL_TO_DIGITAL_APP_STATUS_NOT_INITIALIZED;
    }
    if (pin >= SERIAL_TO_DIGITAL_CFG_MAX_PINS)
    {
        return SERIAL_TO_DIGITAL_APP_STATUS_INVALID_PARAM;
    }

    /* TODO: Call GPIO_WritePin(pin, state) via driver */
    context.pinState[pin] = state;
    return SERIAL_TO_DIGITAL_APP_STATUS_OK;
}

SerialToDigitalApp_Status_t SerialToDigitalApp_ReadGpio(uint8_t pin, uint8_t *pState)
{
    if (!context.initialized)
    {
        return SERIAL_TO_DIGITAL_APP_STATUS_NOT_INITIALIZED;
    }
    if (pState == NULL || pin >= SERIAL_TO_DIGITAL_CFG_MAX_PINS)
    {
        return SERIAL_TO_DIGITAL_APP_STATUS_INVALID_PARAM;
    }

    /* TODO: Call GPIO_ReadPin(pin) via driver */
    *pState = context.pinState[pin];
    return SERIAL_TO_DIGITAL_APP_STATUS_OK;
}

SerialToDigitalApp_Status_t SerialToDigitalApp_StartPwm(uint8_t channel)
{
    if (!context.initialized)
    {
        return SERIAL_TO_DIGITAL_APP_STATUS_NOT_INITIALIZED;
    }
    if (channel >= SERIAL_TO_DIGITAL_CFG_MAX_PWM_CH)
    {
        return SERIAL_TO_DIGITAL_APP_STATUS_INVALID_PARAM;
    }

    /* TODO: Call PWM_Start(channel) via driver */
    context.pwmRunning[channel] = true;
    return SERIAL_TO_DIGITAL_APP_STATUS_OK;
}

SerialToDigitalApp_Status_t SerialToDigitalApp_StopPwm(uint8_t channel)
{
    if (!context.initialized)
    {
        return SERIAL_TO_DIGITAL_APP_STATUS_NOT_INITIALIZED;
    }
    if (channel >= SERIAL_TO_DIGITAL_CFG_MAX_PWM_CH)
    {
        return SERIAL_TO_DIGITAL_APP_STATUS_INVALID_PARAM;
    }

    /* TODO: Call PWM_Stop(channel) via driver */
    context.pwmRunning[channel] = false;
    return SERIAL_TO_DIGITAL_APP_STATUS_OK;
}