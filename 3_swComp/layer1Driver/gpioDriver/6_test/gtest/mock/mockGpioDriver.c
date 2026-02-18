// This file defines the FFF for functions and MOCK functions for GpioDriver testing

//============================================================================
// Dependencies
//============================================================================
#include "mockGpioDriver.h"

// Include the .c file to get access to static variables and functions
#include "gpioDriverUnit.c"

//============================================================================
// Mock function definitions
//============================================================================

// Required for FFF
DEFINE_FFF_GLOBALS;

// DEFINE_FAKE_VALUE_FUNC(int, ExternalFunction, int);

//============================================================================
// Static function wrapper definitions
//============================================================================

GpioDriver_Status_t call_GpioDriverUnit_Init(void)
{
    return GpioDriverUnit_Init();
}

GpioDriver_Status_t call_GpioDriverUnit_ConfigurePin(GpioDriver_Pin_t pin, const GpioDriver_PinConfig_t *pConfig)
{
    return GpioDriverUnit_ConfigurePin(pin, pConfig);
}

GpioDriver_Status_t call_GpioDriverUnit_SetMode(GpioDriver_Pin_t pin, GpioDriver_Mode_t mode)
{
    return GpioDriverUnit_SetMode(pin, mode);
}

GpioDriver_Status_t call_GpioDriverUnit_SetPull(GpioDriver_Pin_t pin, GpioDriver_Pull_t pull)
{
    return GpioDriverUnit_SetPull(pin, pull);
}

GpioDriver_Status_t call_GpioDriverUnit_SetSpeed(GpioDriver_Pin_t pin, GpioDriver_Speed_t speed)
{
    return GpioDriverUnit_SetSpeed(pin, speed);
}

GpioDriver_Status_t call_GpioDriverUnit_SetIOCapability(GpioDriver_Pin_t pin, GpioDriver_IOCapability_t capability)
{
    return GpioDriverUnit_SetIOCapability(pin, capability);
}

GpioDriver_Status_t call_GpioDriverUnit_WritePin(GpioDriver_Pin_t pin, GpioDriver_State_t state)
{
    return GpioDriverUnit_WritePin(pin, state);
}

GpioDriver_Status_t call_GpioDriverUnit_ReadPin(GpioDriver_Pin_t pin, GpioDriver_State_t *pState)
{
    return GpioDriverUnit_ReadPin(pin, pState);
}

GpioDriver_Status_t call_GpioDriverUnit_TogglePin(GpioDriver_Pin_t pin)
{
    return GpioDriverUnit_TogglePin(pin);
}

GpioDriver_Status_t call_GpioDriverUnit_EnableInterrupt(GpioDriver_Pin_t pin, GpioDriver_InterruptEdge_t edge, GpioDriver_InterruptCallback_t callback)
{
    return GpioDriverUnit_EnableInterrupt(pin, edge, callback);
}

GpioDriver_Status_t call_GpioDriverUnit_DisableInterrupt(GpioDriver_Pin_t pin)
{
    return GpioDriverUnit_DisableInterrupt(pin);
}

GpioDriver_Status_t call_GpioDriverUnit_DeInit(void)
{
    return GpioDriverUnit_DeInit();
}
