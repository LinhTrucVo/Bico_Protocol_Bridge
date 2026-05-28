// DIGITALAPP Implementation - Typed GPIO/PWM API

#include <stddef.h>
#include "DIGITALAPP.h"
#include "DIGITALAPPCfg.h"
#include "gpioDriver.h"
#include "pwmDriver.h"

typedef struct
{
    bool initialized;
    bool pwmRunning[SERIAL_TO_DIGITAL_CFG_MAX_PWM_CH];
} DIGITALAPP_Context_t;

static DIGITALAPP_Context_t context = {0};

DIGITALAPP_Status_t DIGITALAPP_Init(void)
{
    GpioDriver_Config_t gpioCfg = {0};
    gpioCfg.enableInterrupts = false;
    gpioCfg.enableCallbacks = false;

    if (GpioDriverUnit_Init(&gpioCfg) != GPIO_STATUS_OK)
    {
        return DIGITAL_APP_STATUS_ERROR;
    }

    PwmDriver_Config_t pwmCfg = {0};
    if (PwmDriverUnit_Init(&pwmCfg) != PWMDRIVER_OK)
    {
        return DIGITAL_APP_STATUS_ERROR;
    }

    for (uint8_t i = 0U; i < SERIAL_TO_DIGITAL_CFG_MAX_PWM_CH; i++)
    {
        context.pwmRunning[i] = false;
    }

    context.initialized = true;
    return DIGITAL_APP_STATUS_OK;
}

DIGITALAPP_Status_t DIGITALAPP_DeInit(void)
{
    if (context.initialized)
    {
        (void)GpioDriverUnit_DeInit();
        (void)PwmDriverUnit_DeInit();
    }
    context.initialized = false;
    return DIGITAL_APP_STATUS_OK;
}

DIGITALAPP_Status_t DIGITALAPP_WriteGpio(uint8_t pin, uint8_t state)
{
    if (!context.initialized)
    {
        return DIGITAL_APP_STATUS_NOT_INITIALIZED;
    }
    if (pin >= SERIAL_TO_DIGITAL_CFG_MAX_PINS)
    {
        return DIGITAL_APP_STATUS_INVALID_PARAM;
    }

    GpioDriver_State_t gpioState = (state != 0U) ? GPIO_STATE_HIGH : GPIO_STATE_LOW;
    GpioDriver_Status_t drvStatus = GpioDriverUnit_WritePin((GpioDriver_Pin_t)pin, gpioState);
    if (drvStatus != GPIO_STATUS_OK)
    {
        return DIGITAL_APP_STATUS_ERROR;
    }

    return DIGITAL_APP_STATUS_OK;
}

DIGITALAPP_Status_t DIGITALAPP_ReadGpio(uint8_t pin, uint8_t *pState)
{
    if (!context.initialized)
    {
        return DIGITAL_APP_STATUS_NOT_INITIALIZED;
    }
    if (pState == NULL || pin >= SERIAL_TO_DIGITAL_CFG_MAX_PINS)
    {
        return DIGITAL_APP_STATUS_INVALID_PARAM;
    }

    GpioDriver_State_t gpioState = GPIO_STATE_LOW;
    GpioDriver_Status_t drvStatus = GpioDriverUnit_ReadPin((GpioDriver_Pin_t)pin, &gpioState);
    if (drvStatus != GPIO_STATUS_OK)
    {
        return DIGITAL_APP_STATUS_ERROR;
    }

    *pState = (gpioState == GPIO_STATE_HIGH) ? 1U : 0U;
    return DIGITAL_APP_STATUS_OK;
}

DIGITALAPP_Status_t DIGITALAPP_StartPwm(uint8_t channel)
{
    if (!context.initialized)
    {
        return DIGITAL_APP_STATUS_NOT_INITIALIZED;
    }
    if (channel >= SERIAL_TO_DIGITAL_CFG_MAX_PWM_CH)
    {
        return DIGITAL_APP_STATUS_INVALID_PARAM;
    }

    PwmDriver_Status_t drvStatus = PwmDriverUnit_StartChannel((PwmDriver_Channel_t)channel);
    if (drvStatus != PWMDRIVER_OK)
    {
        return DIGITAL_APP_STATUS_ERROR;
    }

    context.pwmRunning[channel] = true;
    return DIGITAL_APP_STATUS_OK;
}

DIGITALAPP_Status_t DIGITALAPP_StopPwm(uint8_t channel)
{
    if (!context.initialized)
    {
        return DIGITAL_APP_STATUS_NOT_INITIALIZED;
    }
    if (channel >= SERIAL_TO_DIGITAL_CFG_MAX_PWM_CH)
    {
        return DIGITAL_APP_STATUS_INVALID_PARAM;
    }

    PwmDriver_Status_t drvStatus = PwmDriverUnit_StopChannel((PwmDriver_Channel_t)channel);
    if (drvStatus != PWMDRIVER_OK)
    {
        return DIGITAL_APP_STATUS_ERROR;
    }

    context.pwmRunning[channel] = false;
    return DIGITAL_APP_STATUS_OK;
}