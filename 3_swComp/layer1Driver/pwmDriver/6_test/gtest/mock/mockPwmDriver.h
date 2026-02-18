// This file declares the FFF for functions and MOCK functions for PwmDriver testing

#ifndef MOCKPWMDRIVER_H
#define MOCKPWMDRIVER_H

//============================================================================
// Dependencies
//============================================================================
#include "fff.h"

#include "pwmDriver.h"
#include "pwmDriverUnit.h"

//============================================================================
// Mock function declarations
//============================================================================
// Declare fake functions for external dependencies if any
// DECLARE_FAKE_VALUE_FUNC(int, ExternalFunction, int);

//============================================================================
// Static function wrapper declarations
//============================================================================

PwmDriver_Status_t call_PwmDriverUnit_Init(void);
PwmDriver_Status_t call_PwmDriverUnit_ConfigureChannel(PwmDriver_Channel_t channel, const PwmDriver_ChannelConfig_t *pConfig);
PwmDriver_Status_t call_PwmDriverUnit_SetFrequency(PwmDriver_Channel_t channel, uint32_t frequency);
PwmDriver_Status_t call_PwmDriverUnit_SetDutyCycle(PwmDriver_Channel_t channel, uint16_t dutyCycle);
PwmDriver_Status_t call_PwmDriverUnit_SetPolarity(PwmDriver_Channel_t channel, PwmDriver_Polarity_t polarity);
PwmDriver_Status_t call_PwmDriverUnit_StartChannel(PwmDriver_Channel_t channel);
PwmDriver_Status_t call_PwmDriverUnit_StopChannel(PwmDriver_Channel_t channel);
PwmDriver_Status_t call_PwmDriverUnit_GetConfiguration(PwmDriver_Channel_t channel, PwmDriver_ChannelConfig_t *pConfig);
PwmDriver_Status_t call_PwmDriverUnit_IsChannelRunning(PwmDriver_Channel_t channel, bool *pIsRunning);
PwmDriver_Status_t call_PwmDriverUnit_DeInit(void);

#endif /* MOCKPWMDRIVER_H */
