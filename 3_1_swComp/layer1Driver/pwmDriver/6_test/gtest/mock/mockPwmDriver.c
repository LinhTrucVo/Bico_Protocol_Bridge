// This file defines the FFF for functions and MOCK functions for PwmDriver testing

//============================================================================
// Dependencies
//============================================================================
#include "mockPwmDriver.h"

// Include the .c file to get access to static variables and functions
#include "pwmDriverUnit.c"

//============================================================================
// Mock function definitions
//============================================================================

// Required for FFF
DEFINE_FFF_GLOBALS;

// DEFINE_FAKE_VALUE_FUNC(int, ExternalFunction, int);

//============================================================================
// Static function wrapper definitions
//============================================================================

PwmDriver_Status_t call_PwmDriverUnit_Init(const PwmDriver_Config_t *pConfig)
{
    return PwmDriverUnit_Init(pConfig);
}

PwmDriver_Status_t call_PwmDriverUnit_ConfigureChannel(PwmDriver_Channel_t channel, const PwmDriver_ChannelConfig_t *pConfig)
{
    return PwmDriverUnit_ConfigureChannel(channel, pConfig);
}

PwmDriver_Status_t call_PwmDriverUnit_SetFrequency(PwmDriver_Channel_t channel, uint32_t frequency)
{
    return PwmDriverUnit_SetFrequency(channel, frequency);
}

PwmDriver_Status_t call_PwmDriverUnit_SetDutyCycle(PwmDriver_Channel_t channel, uint16_t dutyCycle)
{
    return PwmDriverUnit_SetDutyCycle(channel, dutyCycle);
}

PwmDriver_Status_t call_PwmDriverUnit_SetPolarity(PwmDriver_Channel_t channel, PwmDriver_Polarity_t polarity)
{
    return PwmDriverUnit_SetPolarity(channel, polarity);
}

PwmDriver_Status_t call_PwmDriverUnit_StartChannel(PwmDriver_Channel_t channel)
{
    return PwmDriverUnit_StartChannel(channel);
}

PwmDriver_Status_t call_PwmDriverUnit_StopChannel(PwmDriver_Channel_t channel)
{
    return PwmDriverUnit_StopChannel(channel);
}

PwmDriver_Status_t call_PwmDriverUnit_GetConfiguration(PwmDriver_Channel_t channel, PwmDriver_ChannelConfig_t *pConfig)
{
    return PwmDriverUnit_GetConfiguration(channel, pConfig);
}

PwmDriver_Status_t call_PwmDriverUnit_IsChannelRunning(PwmDriver_Channel_t channel, bool *pIsRunning)
{
    return PwmDriverUnit_IsChannelRunning(channel, pIsRunning);
}

PwmDriver_Status_t call_PwmDriverUnit_DeInit(void)
{
    return PwmDriverUnit_DeInit();
}
