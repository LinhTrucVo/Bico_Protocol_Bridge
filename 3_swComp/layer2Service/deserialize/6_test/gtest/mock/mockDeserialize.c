// This file defines the FFF for functions and MOCK functions for Deserialize testing

//============================================================================
// Dependencies
//============================================================================
#include "mockDeserialize.h"

// Include the .c file to get access to static variables and functions
#include "deserializeUnit.c"

//============================================================================
// Mock function definitions
//============================================================================

// Required for FFF
DEFINE_FFF_GLOBALS;

// DEFINE_FAKE_VALUE_FUNC(int, ExternalFunction, int);

//============================================================================
// Static function wrapper definitions
//============================================================================

Deserialize_Status_t call_DeserializeUnit_Init(void)
{
    return DeserializeUnit_Init();
}

Deserialize_Status_t call_DeserializeUnit_DeInit(void)
{
    return DeserializeUnit_DeInit();
}

Deserialize_Status_t call_DeserializeUnit_ValidateFrame(const Deserialize_Frame_t *pFrame)
{
    return DeserializeUnit_ValidateFrame(pFrame);
}

Deserialize_Status_t call_DeserializeUnit_ParseFrame(const Deserialize_Frame_t *pFrame, Deserialize_Request_t *pRequest)
{
    return DeserializeUnit_ParseFrame(pFrame, pRequest);
}

Deserialize_Status_t call_DeserializeUnit_ComputeCrc(const uint8_t *pData, uint16_t length, uint16_t *pCrc)
{
    return DeserializeUnit_ComputeCrc(pData, length, pCrc);
}
