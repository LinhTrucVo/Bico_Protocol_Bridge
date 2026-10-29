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

Deserialize_Status_t call_DeserializeUnit_Parse(const Deserialize_Frame_t *pFrame, Deserialize_UdsRequest_t *pRequest)
{
    return DeserializeUnit_Parse(pFrame, pRequest);
}