// This file defines the FFF for functions and MOCK functions for SerialToDigitalApp testing

//============================================================================
// Dependencies
//============================================================================
#include "mockSerialToDigitalApp.h"

// Include the .c file to get access to static variables and functions
#include "serialToDigitalAppUnit.c"

//============================================================================
// Mock function definitions
//============================================================================

// Required for FFF
DEFINE_FFF_GLOBALS;

// DEFINE_FAKE_VALUE_FUNC(int, ExternalFunction, int);

//============================================================================
// Static function wrapper definitions
//============================================================================

SerialToDigitalApp_Status_t call_SerialToDigitalAppUnit_Init(void)
{
    return SerialToDigitalAppUnit_Init();
}

SerialToDigitalApp_Status_t call_SerialToDigitalAppUnit_DeInit(void)
{
    return SerialToDigitalAppUnit_DeInit();
}

SerialToDigitalApp_Status_t call_SerialToDigitalAppUnit_Run(void)
{
    return SerialToDigitalAppUnit_Run();
}

SerialToDigitalApp_Status_t call_SerialToDigitalAppUnit_ProcessFrame(const uint8_t *pFrame, uint16_t frameLength, uint8_t *pResponse, uint16_t *pResponseLength)
{
    return SerialToDigitalAppUnit_ProcessFrame(pFrame, frameLength, pResponse, pResponseLength);
}
