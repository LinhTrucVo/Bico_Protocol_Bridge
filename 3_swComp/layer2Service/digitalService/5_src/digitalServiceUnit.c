// DigitalService Implementation - Typed GPIO/PWM API

#include <stddef.h>
#include "digitalService.h"
#include "digitalServiceCfg.h"
#include "gpioDriver.h"
#include "pwmDriver.h"

typedef struct
{
    bool initialized;
    bool pwmRunning[BPB_DIGITAL_SERVICE_CFG_MAX_PWM_CH];
} DigitalService_Context_t;

static DigitalService_Context_t context = {0};

DigitalService_Status_t DigitalServiceUnit_Init(void)
{
    GpioDriver_Config_t gpioCfg = {0};
    gpioCfg.enableInterrupts = false;
    gpioCfg.enableCallbacks = false;

    if (GpioDriverUnit_Init(&gpioCfg) != BPB_GPIO_STATUS_OK)
    {
        return BPB_DIGITALSERVICE_STATUS_ERROR;
    }

    PwmDriver_Config_t pwmCfg = {0};
    if (PwmDriverUnit_Init(&pwmCfg) != BPB_PWMDRIVER_OK)
    {
        return BPB_DIGITALSERVICE_STATUS_ERROR;
    }

    for (uint8_t i = 0U; i < BPB_DIGITAL_SERVICE_CFG_MAX_PWM_CH; i++)
    {
        context.pwmRunning[i] = false;
    }

    context.initialized = true;
    return BPB_DIGITALSERVICE_STATUS_OK;
}

DigitalService_Status_t DigitalServiceUnit_DeInit(void)
{
    if (context.initialized)
    {
        (void)GpioDriverUnit_DeInit();
        (void)PwmDriverUnit_DeInit();
    }
    context.initialized = false;
    return BPB_DIGITALSERVICE_STATUS_OK;
}

DigitalService_Status_t DigitalServiceUnit_WriteGpio(uint8_t pin, uint8_t state)
{
    if (!context.initialized)
    {
        return BPB_DIGITALSERVICE_STATUS_NOT_INITIALIZED;
    }
    if (pin >= BPB_DIGITAL_SERVICE_CFG_MAX_PINS)
    {
        return BPB_DIGITALSERVICE_STATUS_INVALID_PARAM;
    }

    GpioDriver_State_t gpioState = (state != 0U) ? BPB_GPIO_STATE_HIGH : BPB_GPIO_STATE_LOW;
    GpioDriver_Status_t drvStatus = GpioDriverUnit_WritePin((GpioDriver_Pin_t)pin, gpioState);
    if (drvStatus != BPB_GPIO_STATUS_OK)
    {
        return BPB_DIGITALSERVICE_STATUS_ERROR;
    }

    return BPB_DIGITALSERVICE_STATUS_OK;
}

DigitalService_Status_t DigitalServiceUnit_ReadGpio(uint8_t pin, uint8_t *pState)
{
    if (!context.initialized)
    {
        return BPB_DIGITALSERVICE_STATUS_NOT_INITIALIZED;
    }
    if (pState == NULL || pin >= BPB_DIGITAL_SERVICE_CFG_MAX_PINS)
    {
        return BPB_DIGITALSERVICE_STATUS_INVALID_PARAM;
    }

    GpioDriver_State_t gpioState = BPB_GPIO_STATE_LOW;
    GpioDriver_Status_t drvStatus = GpioDriverUnit_ReadPin((GpioDriver_Pin_t)pin, &gpioState);
    if (drvStatus != BPB_GPIO_STATUS_OK)
    {
        return BPB_DIGITALSERVICE_STATUS_ERROR;
    }

    *pState = (gpioState == BPB_GPIO_STATE_HIGH) ? 1U : 0U;
    return BPB_DIGITALSERVICE_STATUS_OK;
}

DigitalService_Status_t DigitalServiceUnit_StartPwm(uint8_t channel)
{
    if (!context.initialized)
    {
        return BPB_DIGITALSERVICE_STATUS_NOT_INITIALIZED;
    }
    if (channel >= BPB_DIGITAL_SERVICE_CFG_MAX_PWM_CH)
    {
        return BPB_DIGITALSERVICE_STATUS_INVALID_PARAM;
    }

    PwmDriver_Status_t drvStatus = PwmDriverUnit_StartChannel((PwmDriver_Channel_t)channel);
    if (drvStatus != BPB_PWMDRIVER_OK)
    {
        return BPB_DIGITALSERVICE_STATUS_ERROR;
    }

    context.pwmRunning[channel] = true;
    return BPB_DIGITALSERVICE_STATUS_OK;
}

DigitalService_Status_t DigitalServiceUnit_StopPwm(uint8_t channel)
{
    if (!context.initialized)
    {
        return BPB_DIGITALSERVICE_STATUS_NOT_INITIALIZED;
    }
    if (channel >= BPB_DIGITAL_SERVICE_CFG_MAX_PWM_CH)
    {
        return BPB_DIGITALSERVICE_STATUS_INVALID_PARAM;
    }

    PwmDriver_Status_t drvStatus = PwmDriverUnit_StopChannel((PwmDriver_Channel_t)channel);
    if (drvStatus != BPB_PWMDRIVER_OK)
    {
        return BPB_DIGITALSERVICE_STATUS_ERROR;
    }

    context.pwmRunning[channel] = false;
    return BPB_DIGITALSERVICE_STATUS_OK;
}