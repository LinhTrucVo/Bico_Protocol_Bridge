// This file defines the FFF for functions and MOCK functions for SerialToAnalogApp testing

//============================================================================
// Dependencies
//============================================================================
#include "mockSerialToAnalogApp.h"

// Include the .c file to get access to static variables and functions
#include "serialToAnalogAppUnit.c"

//============================================================================
// Mock function definitions
//============================================================================

// Required for FFF
DEFINE_FFF_GLOBALS;

// DEFINE_FAKE_VALUE_FUNC(int, ExternalFunction, int);

//============================================================================
// Static function wrapper definitions
//============================================================================

SerialToAnalogApp_Status_t call_SerialToAnalogAppUnit_Init(void)
{
    return SerialToAnalogAppUnit_Init();
}

SerialToAnalogApp_Status_t call_SerialToAnalogAppUnit_DeInit(void)
{
    return SerialToAnalogAppUnit_DeInit();
}

SerialToAnalogApp_Status_t call_SerialToAnalogAppUnit_Run(void)
{
    return SerialToAnalogAppUnit_Run();
}

SerialToAnalogApp_Status_t call_SerialToAnalogAppUnit_ProcessFrame(const uint8_t *pFrame, uint16_t frameLength, uint8_t *pResponse, uint16_t *pResponseLength)
{
    return SerialToAnalogAppUnit_ProcessFrame(pFrame, frameLength, pResponse, pResponseLength);
}
