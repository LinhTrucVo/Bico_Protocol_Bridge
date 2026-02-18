// This file defines the FFF for functions and MOCK functions for AdcDriver testing

//============================================================================
// Dependencies
//============================================================================
#include "mockAdcDriver.h"

// Include the .c file to get access to static variables and functions
#include "adcDriverUnit.c"

//============================================================================
// Mock function definitions
//============================================================================

// Required for FFF
DEFINE_FFF_GLOBALS;

// DEFINE_FAKE_VALUE_FUNC(int, ExternalFunction, int);

//============================================================================
// Static function wrapper definitions
//============================================================================

AdcDriver_Status_t call_AdcDriverUnit_Init(const AdcDriver_Config_t *pConfig)
{
    return AdcDriverUnit_Init(pConfig);
}

AdcDriver_Status_t call_AdcDriverUnit_ConfigureChannel(AdcDriver_Channel_t channel, bool enable)
{
    return AdcDriverUnit_ConfigureChannel(channel, enable);
}

AdcDriver_Status_t call_AdcDriverUnit_StartConversion(AdcDriver_Channel_t channel)
{
    return AdcDriverUnit_StartConversion(channel);
}

AdcDriver_Status_t call_AdcDriverUnit_StopConversion(void)
{
    return AdcDriverUnit_StopConversion();
}

AdcDriver_Status_t call_AdcDriverUnit_ReadValue(AdcDriver_Channel_t channel, uint16_t *pValue)
{
    return AdcDriverUnit_ReadValue(channel, pValue);
}

AdcDriver_Status_t call_AdcDriverUnit_IsConversionComplete(AdcDriver_Channel_t channel, bool *pComplete)
{
    return AdcDriverUnit_IsConversionComplete(channel, pComplete);
}

AdcDriver_Status_t call_AdcDriverUnit_RegisterCallback(AdcDriver_ConversionCallback_t callback)
{
    return AdcDriverUnit_RegisterCallback(callback);
}

AdcDriver_Status_t call_AdcDriverUnit_Calibrate(void)
{
    return AdcDriverUnit_Calibrate();
}

AdcDriver_Status_t call_AdcDriverUnit_GetStatus(AdcDriver_Status_t *pStatus)
{
    return AdcDriverUnit_GetStatus(pStatus);
}

AdcDriver_Status_t call_AdcDriverUnit_DeInit(void)
{
    return AdcDriverUnit_DeInit();
}
