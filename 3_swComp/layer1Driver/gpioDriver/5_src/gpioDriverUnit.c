// This file is used to define the public interface of the component unit.
// It contains public macros, private variables, and function definitions.

//============================================================================
// Dependencies
//============================================================================
#include <stddef.h>
#include <string.h>
#include "gpioDriver.h"
#include "gpioDriverCfg.h"
#include "gpioDriverPorting.h"

//============================================================================
// Local Macros
//============================================================================

//============================================================================
// Local Types
//============================================================================
typedef struct
{
    bool initialized;
    GpioDriver_PinConfig_t pinConfig[GPIO_MAX_PINS];
    GpioDriver_State_t pinState[GPIO_MAX_PINS];
    GpioDriver_InterruptCallback_t irqCallback[GPIO_MAX_PINS];
} GpioDriver_Context_t;

//============================================================================
// Variables
//============================================================================
static GpioDriver_Context_t gpioContext = {0};

//============================================================================
// Local Function Prototypes
//============================================================================
static bool GpioDriverUnit_IsValidPin(GpioDriver_Pin_t pin);
static GpioDriver_Status_t GpioDriverUnit_ApplyPin(GpioDriver_Pin_t pin);
static void GpioDriverUnit_OnPortInterrupt(uint8_t pin);

//============================================================================
// Public Function Implementations
//============================================================================

GpioDriver_Status_t GpioDriverUnit_Init(const GpioDriver_Config_t *pConfig)
{
    if (pConfig == NULL)
    {
        return GPIO_STATUS_INVALID_PIN;
    }
    if (gpioContext.initialized)
    {
        GpioPort_DeInit();
    }
    if (!GpioPort_Init())
    {
        (void)memset(&gpioContext, 0, sizeof(gpioContext));
        return GPIO_STATUS_ERROR;
    }

    (void)memset(&gpioContext, 0, sizeof(gpioContext));
    gpioContext.initialized = true;
    for (uint8_t i = 0; i < GPIO_MAX_PINS; i++)
    {
        gpioContext.pinConfig[i].mode = GPIO_CFG_DEFAULT_MODE;
        gpioContext.pinConfig[i].pull = GPIO_CFG_DEFAULT_PULL;
        gpioContext.pinConfig[i].speed = GPIO_CFG_DEFAULT_SPEED;
        gpioContext.pinConfig[i].initialState = GPIO_STATE_LOW;
        gpioContext.pinConfig[i].ioCapability = GPIO_CFG_DEFAULT_IO_CAPABILITY;
        gpioContext.pinState[i] = GPIO_STATE_LOW;
        gpioContext.irqCallback[i] = NULL;
    }
    GpioPort_SetInterruptHandler(GpioDriverUnit_OnPortInterrupt);
    return GPIO_STATUS_OK;
}

GpioDriver_Status_t GpioDriverUnit_ConfigurePin(GpioDriver_Pin_t pin, const GpioDriver_PinConfig_t *pConfig)
{
    if (!gpioContext.initialized)
    {
        return GPIO_STATUS_NOT_INITIALIZED;
    }
    if (!GpioDriverUnit_IsValidPin(pin) || (pConfig == NULL))
    {
        return GPIO_STATUS_INVALID_PIN;
    }

    gpioContext.pinConfig[pin] = *pConfig;
    gpioContext.pinState[pin] = pConfig->initialState;
    if (pConfig->ioCapability == 0) {
        gpioContext.pinConfig[pin].ioCapability = GPIO_CFG_DEFAULT_IO_CAPABILITY;
    }
    return GpioDriverUnit_ApplyPin(pin);
}

GpioDriver_Status_t GpioDriverUnit_SetMode(GpioDriver_Pin_t pin, GpioDriver_Mode_t mode)
{
    if (!gpioContext.initialized)
    {
        return GPIO_STATUS_NOT_INITIALIZED;
    }
    if (!GpioDriverUnit_IsValidPin(pin))
    {
        return GPIO_STATUS_INVALID_PIN;
    }

    gpioContext.pinConfig[pin].mode = mode;
    return GpioDriverUnit_ApplyPin(pin);
}

GpioDriver_Status_t GpioDriverUnit_SetPull(GpioDriver_Pin_t pin, GpioDriver_Pull_t pull)
{
    if (!gpioContext.initialized)
    {
        return GPIO_STATUS_NOT_INITIALIZED;
    }
    if (!GpioDriverUnit_IsValidPin(pin))
    {
        return GPIO_STATUS_INVALID_PIN;
    }

    gpioContext.pinConfig[pin].pull = pull;
    return GpioDriverUnit_ApplyPin(pin);
}

GpioDriver_Status_t GpioDriverUnit_SetSpeed(GpioDriver_Pin_t pin, GpioDriver_Speed_t speed)
{
    if (!gpioContext.initialized)
    {
        return GPIO_STATUS_NOT_INITIALIZED;
    }
    if (!GpioDriverUnit_IsValidPin(pin))
    {
        return GPIO_STATUS_INVALID_PIN;
    }

    gpioContext.pinConfig[pin].speed = speed;
    return GPIO_STATUS_OK;
}

GpioDriver_Status_t GpioDriverUnit_SetIOCapability(GpioDriver_Pin_t pin, GpioDriver_IOCapability_t capability)
{
    if (!gpioContext.initialized)
    {
        return GPIO_STATUS_NOT_INITIALIZED;
    }
    if (!GpioDriverUnit_IsValidPin(pin))
    {
        return GPIO_STATUS_INVALID_PIN;
    }

    if (!GpioPort_SetDriveStrength(pin, (uint8_t)capability))
    {
        return GPIO_STATUS_ERROR;
    }
    gpioContext.pinConfig[pin].ioCapability = capability;
    return GPIO_STATUS_OK;
}

GpioDriver_Status_t GpioDriverUnit_WritePin(GpioDriver_Pin_t pin, GpioDriver_State_t state)
{
    if (!gpioContext.initialized)
    {
        return GPIO_STATUS_NOT_INITIALIZED;
    }
    if (!GpioDriverUnit_IsValidPin(pin))
    {
        return GPIO_STATUS_INVALID_PIN;
    }

    if (!GpioPort_Write(pin, state == GPIO_STATE_HIGH))
    {
        return GPIO_STATUS_ERROR;
    }
    gpioContext.pinState[pin] = state;
    return GPIO_STATUS_OK;
}

GpioDriver_Status_t GpioDriverUnit_ReadPin(GpioDriver_Pin_t pin, GpioDriver_State_t *pState)
{
    if (!gpioContext.initialized)
    {
        return GPIO_STATUS_NOT_INITIALIZED;
    }
    if (!GpioDriverUnit_IsValidPin(pin) || (pState == NULL))
    {
        return GPIO_STATUS_INVALID_PIN;
    }

    bool high = false;
    if (!GpioPort_Read(pin, &high))
    {
        return GPIO_STATUS_ERROR;
    }
    *pState = high ? GPIO_STATE_HIGH : GPIO_STATE_LOW;
    return GPIO_STATUS_OK;
}

GpioDriver_Status_t GpioDriverUnit_TogglePin(GpioDriver_Pin_t pin)
{
    if (!gpioContext.initialized)
    {
        return GPIO_STATUS_NOT_INITIALIZED;
    }
    if (!GpioDriverUnit_IsValidPin(pin))
    {
        return GPIO_STATUS_INVALID_PIN;
    }

    bool high = false;
    if (!GpioPort_Read(pin, &high))
    {
        return GPIO_STATUS_ERROR;
    }
    return GpioDriverUnit_WritePin(pin, high ? GPIO_STATE_LOW : GPIO_STATE_HIGH);
}

GpioDriver_Status_t GpioDriverUnit_EnableInterrupt(GpioDriver_Pin_t pin, GpioDriver_InterruptEdge_t edge, GpioDriver_InterruptCallback_t callback)
{
    if (!gpioContext.initialized)
    {
        return GPIO_STATUS_NOT_INITIALIZED;
    }
    if (!GpioDriverUnit_IsValidPin(pin) || (callback == NULL))
    {
        return GPIO_STATUS_INVALID_PIN;
    }

    GpioPort_Edge_t portEdge = GPIOPORT_EDGE_BOTH;
    if (edge == GPIO_INTERRUPT_RISING)
    {
        portEdge = GPIOPORT_EDGE_RISING;
    }
    else if (edge == GPIO_INTERRUPT_FALLING)
    {
        portEdge = GPIOPORT_EDGE_FALLING;
    }

    gpioContext.irqCallback[pin] = callback;
    if (!GpioPort_EnableInterrupt(pin, portEdge))
    {
        gpioContext.irqCallback[pin] = NULL;
        return GPIO_STATUS_ERROR;
    }
    return GPIO_STATUS_OK;
}

GpioDriver_Status_t GpioDriverUnit_DisableInterrupt(GpioDriver_Pin_t pin)
{
    if (!gpioContext.initialized)
    {
        return GPIO_STATUS_NOT_INITIALIZED;
    }
    if (!GpioDriverUnit_IsValidPin(pin))
    {
        return GPIO_STATUS_INVALID_PIN;
    }

    GpioPort_DisableInterrupt(pin);
    gpioContext.irqCallback[pin] = NULL;
    return GPIO_STATUS_OK;
}

GpioDriver_Status_t GpioDriverUnit_DeInit(void)
{
    if (gpioContext.initialized)
    {
        for (uint8_t i = 0; i < GPIO_MAX_PINS; i++)
        {
            if (gpioContext.irqCallback[i] != NULL)
            {
                GpioPort_DisableInterrupt(i);
            }
        }
        GpioPort_DeInit();
    }
    (void)memset(&gpioContext, 0, sizeof(gpioContext));
    return GPIO_STATUS_OK;
}

//============================================================================
// Local Function Implementations
//============================================================================

static bool GpioDriverUnit_IsValidPin(GpioDriver_Pin_t pin)
{
    return (pin < GPIO_MAX_PINS);
}

static GpioDriver_Status_t GpioDriverUnit_ApplyPin(GpioDriver_Pin_t pin)
{
    const GpioDriver_PinConfig_t *pCfg = &gpioContext.pinConfig[pin];

    GpioPort_Mode_t mode = GPIOPORT_MODE_DISABLED;
    if (pCfg->mode == GPIO_MODE_INPUT)
    {
        mode = GPIOPORT_MODE_INPUT;
    }
    else if (pCfg->mode == GPIO_MODE_OUTPUT)
    {
        mode = GPIOPORT_MODE_OUTPUT;
    }

    GpioPort_Pull_t pull = GPIOPORT_PULL_NONE;
    if (pCfg->pull == GPIO_PULL_UP)
    {
        pull = GPIOPORT_PULL_UP;
    }
    else if (pCfg->pull == GPIO_PULL_DOWN)
    {
        pull = GPIOPORT_PULL_DOWN;
    }

    if (!GpioPort_ConfigurePin(pin, mode, pull, (uint8_t)pCfg->ioCapability, gpioContext.pinState[pin] == GPIO_STATE_HIGH))
    {
        return GPIO_STATUS_ERROR;
    }
    return GPIO_STATUS_OK;
}

static void GpioDriverUnit_OnPortInterrupt(uint8_t pin)
{
    if ((pin < GPIO_MAX_PINS) && (gpioContext.irqCallback[pin] != NULL))
    {
        gpioContext.irqCallback[pin]((GpioDriver_Pin_t)pin);
    }
}
