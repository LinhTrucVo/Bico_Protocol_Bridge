// This file is used to define the public interface of the component unit.
// It contains public macros, private variables, and function definitions.

//============================================================================
// Dependencies
//============================================================================
#include "gpioDriver.h"
#include "gpioDriverCfg.h"
#include "gpioDriverUnit.h"

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

//============================================================================
// Public Function Implementations
//============================================================================

GpioDriver_Status_t GpioDriverUnit_Init(void)
{
    // TODO: Add vendor-specific HAL initialization here
    gpioContext.initialized = true;
    for (uint8_t i = 0; i < GPIO_MAX_PINS; i++)
    {
        gpioContext.pinConfig[i].mode = GPIO_CFG_DEFAULT_MODE;
        gpioContext.pinConfig[i].pull = GPIO_CFG_DEFAULT_PULL;
        gpioContext.pinConfig[i].speed = GPIO_CFG_DEFAULT_SPEED;
        gpioContext.pinConfig[i].initialState = GPIO_STATE_LOW;
        gpioContext.pinState[i] = GPIO_STATE_LOW;
        gpioContext.irqCallback[i] = NULL;
    }
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

    // TODO: Add vendor-specific HAL pin configuration here
    gpioContext.pinConfig[pin] = *pConfig;
    gpioContext.pinState[pin] = pConfig->initialState;
    return GPIO_STATUS_OK;
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
    return GPIO_STATUS_OK;
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
    return GPIO_STATUS_OK;
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

    // TODO: Add vendor-specific HAL write here
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

    *pState = gpioContext.pinState[pin];
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

    gpioContext.pinState[pin] = (gpioContext.pinState[pin] == GPIO_STATE_LOW) ? GPIO_STATE_HIGH : GPIO_STATE_LOW;
    return GPIO_STATUS_OK;
}

GpioDriver_Status_t GpioDriverUnit_EnableInterrupt(GpioDriver_Pin_t pin, GpioDriver_InterruptEdge_t edge, GpioDriver_InterruptCallback_t callback)
{
    (void)edge;
    if (!gpioContext.initialized)
    {
        return GPIO_STATUS_NOT_INITIALIZED;
    }
    if (!GpioDriverUnit_IsValidPin(pin) || (callback == NULL))
    {
        return GPIO_STATUS_INVALID_PIN;
    }

    // TODO: Configure vendor interrupt
    gpioContext.irqCallback[pin] = callback;
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

    gpioContext.irqCallback[pin] = NULL;
    return GPIO_STATUS_OK;
}

GpioDriver_Status_t GpioDriverUnit_DeInit(void)
{
    // TODO: Add vendor-specific HAL deinitialization here
    gpioContext.initialized = false;
    return GPIO_STATUS_OK;
}

//============================================================================
// Local Function Implementations
//============================================================================

static bool GpioDriverUnit_IsValidPin(GpioDriver_Pin_t pin)
{
    return (pin < GPIO_MAX_PINS);
}
