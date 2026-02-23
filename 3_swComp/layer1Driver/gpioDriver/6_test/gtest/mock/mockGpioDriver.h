// This file declares the FFF for functions and MOCK functions for GpioDriver testing

#ifndef MOCKGPIODRIVER_H
#define MOCKGPIODRIVER_H

//============================================================================
// Dependencies
//============================================================================
#include "fff.h"

#include "gpioDriver.h"
#include "gpioDriverUnit.h"

//============================================================================
// Mock function declarations
//============================================================================
// Declare fake functions for external dependencies if any
// DECLARE_FAKE_VALUE_FUNC(int, ExternalFunction, int);

//============================================================================
// Static function wrapper declarations
//============================================================================

GpioDriver_Status_t call_GpioDriverUnit_Init(const GpioDriver_Config_t *pConfig);
GpioDriver_Status_t call_GpioDriverUnit_ConfigurePin(GpioDriver_Pin_t pin, const GpioDriver_PinConfig_t *pConfig);
GpioDriver_Status_t call_GpioDriverUnit_SetMode(GpioDriver_Pin_t pin, GpioDriver_Mode_t mode);
GpioDriver_Status_t call_GpioDriverUnit_SetPull(GpioDriver_Pin_t pin, GpioDriver_Pull_t pull);
GpioDriver_Status_t call_GpioDriverUnit_SetSpeed(GpioDriver_Pin_t pin, GpioDriver_Speed_t speed);
GpioDriver_Status_t call_GpioDriverUnit_SetIOCapability(GpioDriver_Pin_t pin, GpioDriver_IOCapability_t capability);
GpioDriver_Status_t call_GpioDriverUnit_WritePin(GpioDriver_Pin_t pin, GpioDriver_State_t state);
GpioDriver_Status_t call_GpioDriverUnit_ReadPin(GpioDriver_Pin_t pin, GpioDriver_State_t *pState);
GpioDriver_Status_t call_GpioDriverUnit_TogglePin(GpioDriver_Pin_t pin);
GpioDriver_Status_t call_GpioDriverUnit_EnableInterrupt(GpioDriver_Pin_t pin, GpioDriver_InterruptEdge_t edge, GpioDriver_InterruptCallback_t callback);
GpioDriver_Status_t call_GpioDriverUnit_DisableInterrupt(GpioDriver_Pin_t pin);
GpioDriver_Status_t call_GpioDriverUnit_DeInit(void);

#endif /* MOCKGPIODRIVER_H */
