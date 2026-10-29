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
    GpioDriver_PinConfig_t pinConfig[BPB_GPIO_MAX_PINS];
    GpioDriver_State_t pinState[BPB_GPIO_MAX_PINS];
    GpioDriver_InterruptCallback_t irqCallback[BPB_GPIO_MAX_PINS];
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
        return BPB_GPIO_STATUS_INVALID_PIN;
    }
    if (gpioContext.initialized)
    {
        // GpioPort_DeInit();
    }
    // if (!GpioPort_Init())
    {
        (void)memset(&gpioContext, 0, sizeof(gpioContext));
        return BPB_GPIO_STATUS_ERROR;
    }

    (void)memset(&gpioContext, 0, sizeof(gpioContext));
    gpioContext.initialized = true;
    for (uint8_t i = 0; i < BPB_GPIO_MAX_PINS; i++)
    {
        gpioContext.pinConfig[i].mode = BPB_GPIO_CFG_DEFAULT_MODE;
        gpioContext.pinConfig[i].pull = BPB_GPIO_CFG_DEFAULT_PULL;
        gpioContext.pinConfig[i].speed = BPB_GPIO_CFG_DEFAULT_SPEED;
        gpioContext.pinConfig[i].initialState = BPB_GPIO_STATE_LOW;
        gpioContext.pinConfig[i].ioCapability = BPB_GPIO_CFG_DEFAULT_IO_CAPABILITY;
        gpioContext.pinState[i] = BPB_GPIO_STATE_LOW;
        gpioContext.irqCallback[i] = NULL;
    }
    // GpioPort_SetInterruptHandler(GpioDriverUnit_OnPortInterrupt);
    return BPB_GPIO_STATUS_OK;
}

GpioDriver_Status_t GpioDriverUnit_ConfigurePin(GpioDriver_Pin_t pin, const GpioDriver_PinConfig_t *pConfig)
{
    if (!gpioContext.initialized)
    {
        return BPB_GPIO_STATUS_NOT_INITIALIZED;
    }
    if (!GpioDriverUnit_IsValidPin(pin) || (pConfig == NULL))
    {
        return BPB_GPIO_STATUS_INVALID_PIN;
    }

    gpioContext.pinConfig[pin] = *pConfig;
    gpioContext.pinState[pin] = pConfig->initialState;
    if (pConfig->ioCapability == 0) {
        gpioContext.pinConfig[pin].ioCapability = BPB_GPIO_CFG_DEFAULT_IO_CAPABILITY;
    }
    return GpioDriverUnit_ApplyPin(pin);
}

GpioDriver_Status_t GpioDriverUnit_SetMode(GpioDriver_Pin_t pin, GpioDriver_Mode_t mode)
{
    if (!gpioContext.initialized)
    {
        return BPB_GPIO_STATUS_NOT_INITIALIZED;
    }
    if (!GpioDriverUnit_IsValidPin(pin))
    {
        return BPB_GPIO_STATUS_INVALID_PIN;
    }

    gpioContext.pinConfig[pin].mode = mode;
    return GpioDriverUnit_ApplyPin(pin);
}

GpioDriver_Status_t GpioDriverUnit_SetPull(GpioDriver_Pin_t pin, GpioDriver_Pull_t pull)
{
    if (!gpioContext.initialized)
    {
        return BPB_GPIO_STATUS_NOT_INITIALIZED;
    }
    if (!GpioDriverUnit_IsValidPin(pin))
    {
        return BPB_GPIO_STATUS_INVALID_PIN;
    }

    gpioContext.pinConfig[pin].pull = pull;
    return GpioDriverUnit_ApplyPin(pin);
}

GpioDriver_Status_t GpioDriverUnit_SetSpeed(GpioDriver_Pin_t pin, GpioDriver_Speed_t speed)
{
    if (!gpioContext.initialized)
    {
        return BPB_GPIO_STATUS_NOT_INITIALIZED;
    }
    if (!GpioDriverUnit_IsValidPin(pin))
    {
        return BPB_GPIO_STATUS_INVALID_PIN;
    }

    gpioContext.pinConfig[pin].speed = speed;
    return BPB_GPIO_STATUS_OK;
}

GpioDriver_Status_t GpioDriverUnit_SetIOCapability(GpioDriver_Pin_t pin, GpioDriver_IOCapability_t capability)
{
    if (!gpioContext.initialized)
    {
        return BPB_GPIO_STATUS_NOT_INITIALIZED;
    }
    if (!GpioDriverUnit_IsValidPin(pin))
    {
        return BPB_GPIO_STATUS_INVALID_PIN;
    }

    // if (!GpioPort_SetDriveStrength(pin, (uint8_t)capability))
    {
        return BPB_GPIO_STATUS_ERROR;
    }
    gpioContext.pinConfig[pin].ioCapability = capability;
    return BPB_GPIO_STATUS_OK;
}

GpioDriver_Status_t GpioDriverUnit_WritePin(GpioDriver_Pin_t pin, GpioDriver_State_t state)
{
    if (!gpioContext.initialized)
    {
        return BPB_GPIO_STATUS_NOT_INITIALIZED;
    }
    if (!GpioDriverUnit_IsValidPin(pin))
    {
        return BPB_GPIO_STATUS_INVALID_PIN;
    }

    // if (!GpioPort_Write(pin, state == BPB_GPIO_STATE_HIGH))
    {
        return BPB_GPIO_STATUS_ERROR;
    }
    gpioContext.pinState[pin] = state;
    return BPB_GPIO_STATUS_OK;
}

GpioDriver_Status_t GpioDriverUnit_ReadPin(GpioDriver_Pin_t pin, GpioDriver_State_t *pState)
{
    if (!gpioContext.initialized)
    {
        return BPB_GPIO_STATUS_NOT_INITIALIZED;
    }
    if (!GpioDriverUnit_IsValidPin(pin) || (pState == NULL))
    {
        return BPB_GPIO_STATUS_INVALID_PIN;
    }

    bool high = false;
    // if (!GpioPort_Read(pin, &high))
    {
        return BPB_GPIO_STATUS_ERROR;
    }
    *pState = high ? BPB_GPIO_STATE_HIGH : BPB_GPIO_STATE_LOW;
    return BPB_GPIO_STATUS_OK;
}

GpioDriver_Status_t GpioDriverUnit_TogglePin(GpioDriver_Pin_t pin)
{
    if (!gpioContext.initialized)
    {
        return BPB_GPIO_STATUS_NOT_INITIALIZED;
    }
    if (!GpioDriverUnit_IsValidPin(pin))
    {
        return BPB_GPIO_STATUS_INVALID_PIN;
    }

    bool high = false;
    // if (!GpioPort_Read(pin, &high))
    {
        return BPB_GPIO_STATUS_ERROR;
    }
    return GpioDriverUnit_WritePin(pin, high ? BPB_GPIO_STATE_LOW : BPB_GPIO_STATE_HIGH);
}

GpioDriver_Status_t GpioDriverUnit_EnableInterrupt(GpioDriver_Pin_t pin, GpioDriver_InterruptEdge_t edge, GpioDriver_InterruptCallback_t callback)
{
    if (!gpioContext.initialized)
    {
        return BPB_GPIO_STATUS_NOT_INITIALIZED;
    }
    if (!GpioDriverUnit_IsValidPin(pin) || (callback == NULL))
    {
        return BPB_GPIO_STATUS_INVALID_PIN;
    }

    GpioPort_Edge_t portEdge = BPB_GPIOPORT_EDGE_BOTH;
    if (edge == BPB_GPIO_INTERRUPT_RISING)
    {
        portEdge = BPB_GPIOPORT_EDGE_RISING;
    }
    else if (edge == BPB_GPIO_INTERRUPT_FALLING)
    {
        portEdge = BPB_GPIOPORT_EDGE_FALLING;
    }

    gpioContext.irqCallback[pin] = callback;
    // if (!GpioPort_EnableInterrupt(pin, portEdge))
    {
        gpioContext.irqCallback[pin] = NULL;
        return BPB_GPIO_STATUS_ERROR;
    }
    return BPB_GPIO_STATUS_OK;
}

GpioDriver_Status_t GpioDriverUnit_DisableInterrupt(GpioDriver_Pin_t pin)
{
    if (!gpioContext.initialized)
    {
        return BPB_GPIO_STATUS_NOT_INITIALIZED;
    }
    if (!GpioDriverUnit_IsValidPin(pin))
    {
        return BPB_GPIO_STATUS_INVALID_PIN;
    }

    // GpioPort_DisableInterrupt(pin);
    gpioContext.irqCallback[pin] = NULL;
    return BPB_GPIO_STATUS_OK;
}

GpioDriver_Status_t GpioDriverUnit_DeInit(void)
{
    if (gpioContext.initialized)
    {
        for (uint8_t i = 0; i < BPB_GPIO_MAX_PINS; i++)
        {
            if (gpioContext.irqCallback[i] != NULL)
            {
                // GpioPort_DisableInterrupt(i);
            }
        }
        // GpioPort_DeInit();
    }
    (void)memset(&gpioContext, 0, sizeof(gpioContext));
    return BPB_GPIO_STATUS_OK;
}

//============================================================================
// Local Function Implementations
//============================================================================

static bool GpioDriverUnit_IsValidPin(GpioDriver_Pin_t pin)
{
    return (pin < BPB_GPIO_MAX_PINS);
}

static GpioDriver_Status_t GpioDriverUnit_ApplyPin(GpioDriver_Pin_t pin)
{
    const GpioDriver_PinConfig_t *pCfg = &gpioContext.pinConfig[pin];

    GpioPort_Mode_t mode = BPB_GPIOPORT_MODE_DISABLED;
    if (pCfg->mode == BPB_GPIO_MODE_INPUT)
    {
        mode = BPB_GPIOPORT_MODE_INPUT;
    }
    else if (pCfg->mode == BPB_GPIO_MODE_OUTPUT)
    {
        mode = BPB_GPIOPORT_MODE_OUTPUT;
    }

    GpioPort_Pull_t pull = BPB_GPIOPORT_PULL_NONE;
    if (pCfg->pull == BPB_GPIO_PULL_UP)
    {
        pull = BPB_GPIOPORT_PULL_UP;
    }
    else if (pCfg->pull == BPB_GPIO_PULL_DOWN)
    {
        pull = BPB_GPIOPORT_PULL_DOWN;
    }

    // if (!GpioPort_ConfigurePin(pin, mode, pull, (uint8_t)pCfg->ioCapability, gpioContext.pinState[pin] == BPB_GPIO_STATE_HIGH))
    {
        return BPB_GPIO_STATUS_ERROR;
    }
    return BPB_GPIO_STATUS_OK;
}

static void GpioDriverUnit_OnPortInterrupt(uint8_t pin)
{
    if ((pin < BPB_GPIO_MAX_PINS) && (gpioContext.irqCallback[pin] != NULL))
    {
        gpioContext.irqCallback[pin]((GpioDriver_Pin_t)pin);
    }
}
