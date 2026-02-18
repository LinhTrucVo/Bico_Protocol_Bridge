// This file declares the FFF for functions and MOCK functions for SerialToAnalogApp testing

#ifndef MOCKSERIALTOANALOGAPP_H
#define MOCKSERIALTOANALOGAPP_H

//============================================================================
// Dependencies
//============================================================================
#include "fff.h"

#include "serialToAnalogApp.h"
#include "serialToAnalogAppUnit.h"

//============================================================================
// Mock function declarations
//============================================================================
// Declare fake functions for external dependencies if any
// DECLARE_FAKE_VALUE_FUNC(int, ExternalFunction, int);

//============================================================================
// Static function wrapper declarations
//============================================================================

SerialToAnalogApp_Status_t call_SerialToAnalogAppUnit_Init(void);
SerialToAnalogApp_Status_t call_SerialToAnalogAppUnit_DeInit(void);
SerialToAnalogApp_Status_t call_SerialToAnalogAppUnit_Run(void);
SerialToAnalogApp_Status_t call_SerialToAnalogAppUnit_ProcessFrame(const uint8_t *pFrame, uint16_t frameLength, uint8_t *pResponse, uint16_t *pResponseLength);

#endif /* MOCKSERIALTOANALOGAPP_H */
