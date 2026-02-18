// This file declares the FFF for functions and MOCK functions for SerialToI2CApp testing

#ifndef MOCKSERIALTOI2CAPP_H
#define MOCKSERIALTOI2CAPP_H

//============================================================================
// Dependencies
//============================================================================
#include "fff.h"

#include "serialToI2CApp.h"
#include "serialToI2CAppUnit.h"

//============================================================================
// Mock function declarations
//============================================================================
// Declare fake functions for external dependencies if any
// DECLARE_FAKE_VALUE_FUNC(int, ExternalFunction, int);

//============================================================================
// Static function wrapper declarations
//============================================================================

SerialToI2CApp_Status_t call_SerialToI2CAppUnit_Init(void);
SerialToI2CApp_Status_t call_SerialToI2CAppUnit_DeInit(void);
SerialToI2CApp_Status_t call_SerialToI2CAppUnit_Run(void);
SerialToI2CApp_Status_t call_SerialToI2CAppUnit_ProcessFrame(const uint8_t *pFrame, uint16_t frameLength, uint8_t *pResponse, uint16_t *pResponseLength);

#endif /* MOCKSERIALTOI2CAPP_H */
