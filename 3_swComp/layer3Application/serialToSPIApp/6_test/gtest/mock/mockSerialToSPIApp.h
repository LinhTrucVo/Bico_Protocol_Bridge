// This file declares the FFF for functions and MOCK functions for SerialToSPIApp testing

#ifndef MOCKSERIALTOSPIAPP_H
#define MOCKSERIALTOSPIAPP_H

//============================================================================
// Dependencies
//============================================================================
#include "fff.h"

#include "serialToSPIApp.h"
#include "serialToSPIAppUnit.h"

//============================================================================
// Mock function declarations
//============================================================================
// Declare fake functions for external dependencies if any
// DECLARE_FAKE_VALUE_FUNC(int, ExternalFunction, int);

//============================================================================
// Static function wrapper declarations
//============================================================================

SerialToSPIApp_Status_t call_SerialToSPIAppUnit_Init(void);
SerialToSPIApp_Status_t call_SerialToSPIAppUnit_DeInit(void);
SerialToSPIApp_Status_t call_SerialToSPIAppUnit_Run(void);
SerialToSPIApp_Status_t call_SerialToSPIAppUnit_ProcessFrame(const uint8_t *pFrame, uint16_t frameLength, uint8_t *pResponse, uint16_t *pResponseLength);

#endif /* MOCKSERIALTOSPIAPP_H */
