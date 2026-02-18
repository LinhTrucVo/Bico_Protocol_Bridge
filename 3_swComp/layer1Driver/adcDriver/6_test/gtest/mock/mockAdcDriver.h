// This file declares the FFF for functions and MOCK functions for AdcDriver testing

#ifndef MOCKADCDRIVER_H
#define MOCKADCDRIVER_H

//============================================================================
// Dependencies
//============================================================================
#include "fff.h"

#include "adcDriver.h"
#include "adcDriverUnit.h"

//============================================================================
// Mock function declarations
//============================================================================
// Declare fake functions for external dependencies if any
// DECLARE_FAKE_VALUE_FUNC(int, ExternalFunction, int);

//============================================================================
// Static function wrapper declarations
//============================================================================

AdcDriver_Status_t call_AdcDriverUnit_Init(const AdcDriver_Config_t *pConfig);
AdcDriver_Status_t call_AdcDriverUnit_ConfigureChannel(AdcDriver_Channel_t channel, bool enable);
AdcDriver_Status_t call_AdcDriverUnit_StartConversion(AdcDriver_Channel_t channel);
AdcDriver_Status_t call_AdcDriverUnit_StopConversion(void);
AdcDriver_Status_t call_AdcDriverUnit_ReadValue(AdcDriver_Channel_t channel, uint16_t *pValue);
AdcDriver_Status_t call_AdcDriverUnit_IsConversionComplete(AdcDriver_Channel_t channel, bool *pComplete);
AdcDriver_Status_t call_AdcDriverUnit_RegisterCallback(AdcDriver_ConversionCallback_t callback);
AdcDriver_Status_t call_AdcDriverUnit_Calibrate(void);
AdcDriver_Status_t call_AdcDriverUnit_GetStatus(AdcDriver_Status_t *pStatus);
AdcDriver_Status_t call_AdcDriverUnit_DeInit(void);

#endif /* MOCKADCDRIVER_H */
