// This file defines the FFF for functions and MOCK functions for SerialToSPIApp testing

//============================================================================
// Dependencies
//============================================================================
#include "mockSerialToSPIApp.h"

// Include the .c file to get access to static variables and functions
#include "../../../5_src/serialToSPIAppUnit.c"

//============================================================================
// Mock function definitions
//============================================================================

// Required for FFF
DEFINE_FFF_GLOBALS;

// DEFINE_FAKE_VALUE_FUNC(int, ExternalFunction, int);

//============================================================================
// Static function wrapper definitions
//============================================================================

SerialToSPIApp_Status_t call_SerialToSPIAppUnit_Init(void)
{
    return SerialToSPIAppUnit_Init();
}

SerialToSPIApp_Status_t call_SerialToSPIAppUnit_DeInit(void)
{
    return SerialToSPIAppUnit_DeInit();
}

SerialToSPIApp_Status_t call_SerialToSPIAppUnit_Run(void)
{
    return SerialToSPIAppUnit_Run();
}

SerialToSPIApp_Status_t call_SerialToSPIAppUnit_ProcessFrame(const uint8_t *pFrame, uint16_t frameLength, uint8_t *pResponse, uint16_t *pResponseLength)
{
    return SerialToSPIAppUnit_ProcessFrame(pFrame, frameLength, pResponse, pResponseLength);
}
