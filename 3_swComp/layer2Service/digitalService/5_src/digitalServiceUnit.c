// DigitalService Implementation - Typed GPIO/PWM API

#include <stddef.h>
#include "digitalService.h"
#include "digitalServiceCfg.h"
#include "gpioDriver.h"
#include "pwmDriver.h"

typedef struct
{
    bool initialized;
    bool pwmRunning[DIGITAL_SERVICE_CFG_MAX_PWM_CH];
} DigitalService_Context_t;

static DigitalService_Context_t context = {0};

DigitalService_Status_t DigitalServiceUnit_Init(void)
{
    GpioDriver_Config_t gpioCfg = {0};
    gpioCfg.enableInterrupts = false;
    gpioCfg.enableCallbacks = false;

    if (GpioDriverUnit_Init(&gpioCfg) != GPIO_STATUS_OK)
    {
        return DIGITALSERVICE_STATUS_ERROR;
    }

    PwmDriver_Config_t pwmCfg = {0};
    if (PwmDriverUnit_Init(&pwmCfg) != PWMDRIVER_OK)
    {
        return DIGITALSERVICE_STATUS_ERROR;
    }

    for (uint8_t i = 0U; i < DIGITAL_SERVICE_CFG_MAX_PWM_CH; i++)
    {
        context.pwmRunning[i] = false;
    }

    context.initialized = true;
    return DIGITALSERVICE_STATUS_OK;
}

DigitalService_Status_t DigitalServiceUnit_DeInit(void)
{
    if (context.initialized)
    {
        (void)GpioDriverUnit_DeInit();
        (void)PwmDriverUnit_DeInit();
    }
    context.initialized = false;
    return DIGITALSERVICE_STATUS_OK;
}

DigitalService_Status_t DigitalServiceUnit_WriteGpio(uint8_t pin, uint8_t state)
{
    if (!context.initialized)
    {
        return DIGITALSERVICE_STATUS_NOT_INITIALIZED;
    }
    if (pin >= DIGITAL_SERVICE_CFG_MAX_PINS)
    {
        return DIGITALSERVICE_STATUS_INVALID_PARAM;
    }

    GpioDriver_State_t gpioState = (state != 0U) ? GPIO_STATE_HIGH : GPIO_STATE_LOW;
    GpioDriver_Status_t drvStatus = GpioDriverUnit_WritePin((GpioDriver_Pin_t)pin, gpioState);
    if (drvStatus != GPIO_STATUS_OK)
    {
        return DIGITALSERVICE_STATUS_ERROR;
    }

    return DIGITALSERVICE_STATUS_OK;
}

DigitalService_Status_t DigitalServiceUnit_ReadGpio(uint8_t pin, uint8_t *pState)
{
    if (!context.initialized)
    {
        return DIGITALSERVICE_STATUS_NOT_INITIALIZED;
    }
    if (pState == NULL || pin >= DIGITAL_SERVICE_CFG_MAX_PINS)
    {
        return DIGITALSERVICE_STATUS_INVALID_PARAM;
    }

    GpioDriver_State_t gpioState = GPIO_STATE_LOW;
    GpioDriver_Status_t drvStatus = GpioDriverUnit_ReadPin((GpioDriver_Pin_t)pin, &gpioState);
    if (drvStatus != GPIO_STATUS_OK)
    {
        return DIGITALSERVICE_STATUS_ERROR;
    }

    *pState = (gpioState == GPIO_STATE_HIGH) ? 1U : 0U;
    return DIGITALSERVICE_STATUS_OK;
}

DigitalService_Status_t DigitalServiceUnit_StartPwm(uint8_t channel)
{
    if (!context.initialized)
    {
        return DIGITALSERVICE_STATUS_NOT_INITIALIZED;
    }
    if (channel >= DIGITAL_SERVICE_CFG_MAX_PWM_CH)
    {
        return DIGITALSERVICE_STATUS_INVALID_PARAM;
    }

    PwmDriver_Status_t drvStatus = PwmDriverUnit_StartChannel((PwmDriver_Channel_t)channel);
    if (drvStatus != PWMDRIVER_OK)
    {
        return DIGITALSERVICE_STATUS_ERROR;
    }

    context.pwmRunning[channel] = true;
    return DIGITALSERVICE_STATUS_OK;
}

DigitalService_Status_t DigitalServiceUnit_StopPwm(uint8_t channel)
{
    if (!context.initialized)
    {
        return DIGITALSERVICE_STATUS_NOT_INITIALIZED;
    }
    if (channel >= DIGITAL_SERVICE_CFG_MAX_PWM_CH)
    {
        return DIGITALSERVICE_STATUS_INVALID_PARAM;
    }

    PwmDriver_Status_t drvStatus = PwmDriverUnit_StopChannel((PwmDriver_Channel_t)channel);
    if (drvStatus != PWMDRIVER_OK)
    {
        return DIGITALSERVICE_STATUS_ERROR;
    }

    context.pwmRunning[channel] = false;
    return DIGITALSERVICE_STATUS_OK;
}