// This file declares the FFF for functions and MOCK functions for SerialToDigitalApp testing

#ifndef MOCKSERIALTODIGITALAPP_H
#define MOCKSERIALTODIGITALAPP_H

//============================================================================
// Dependencies
//============================================================================
#include "fff.h"

#include "serialToDigitalApp.h"
#include "serialToDigitalAppUnit.h"

//============================================================================
// Mock function declarations
//============================================================================
// Declare fake functions for external dependencies if any
// DECLARE_FAKE_VALUE_FUNC(int, ExternalFunction, int);

//============================================================================
// Static function wrapper declarations
//============================================================================

SerialToDigitalApp_Status_t call_SerialToDigitalAppUnit_Init(void);
SerialToDigitalApp_Status_t call_SerialToDigitalAppUnit_DeInit(void);
SerialToDigitalApp_Status_t call_SerialToDigitalAppUnit_Run(void);
SerialToDigitalApp_Status_t call_SerialToDigitalAppUnit_ProcessFrame(const uint8_t *pFrame, uint16_t frameLength, uint8_t *pResponse, uint16_t *pResponseLength);

#endif /* MOCKSERIALTODIGITALAPP_H */
