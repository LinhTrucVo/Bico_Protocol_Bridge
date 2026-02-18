// This file defines the FFF for functions and MOCK functions for SerialToI2CApp testing

//============================================================================
// Dependencies
//============================================================================
#include "mockSerialToI2CApp.h"

// Include the .c file to get access to static variables and functions
#include "serialToI2CAppUnit.c"

//============================================================================
// Mock function definitions
//============================================================================

// Required for FFF
DEFINE_FFF_GLOBALS;

// DEFINE_FAKE_VALUE_FUNC(int, ExternalFunction, int);

//============================================================================
// Static function wrapper definitions
//============================================================================

SerialToI2CApp_Status_t call_SerialToI2CAppUnit_Init(void)
{
    return SerialToI2CAppUnit_Init();
}

SerialToI2CApp_Status_t call_SerialToI2CAppUnit_DeInit(void)
{
    return SerialToI2CAppUnit_DeInit();
}

SerialToI2CApp_Status_t call_SerialToI2CAppUnit_Run(void)
{
    return SerialToI2CAppUnit_Run();
}

SerialToI2CApp_Status_t call_SerialToI2CAppUnit_ProcessFrame(const uint8_t *pFrame, uint16_t frameLength, uint8_t *pResponse, uint16_t *pResponseLength)
{
    return SerialToI2CAppUnit_ProcessFrame(pFrame, frameLength, pResponse, pResponseLength);
}
