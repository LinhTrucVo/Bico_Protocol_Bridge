// This file defines the FFF for functions and MOCK functions for Serialize testing

//============================================================================
// Dependencies
//============================================================================
#include "mockSerialize.h"

// Include the .c file to get access to static variables and functions
#include "serializeUnit.c"

//============================================================================
// Mock function definitions
//============================================================================
DEFINE_FFF_GLOBALS;

//============================================================================
// Static function wrapper definitions
//============================================================================

Serialize_Status_t call_SerializeUnit_Init(void)
{
    return SerializeUnit_Init();
}

Serialize_Status_t call_SerializeUnit_DeInit(void)
{
    return SerializeUnit_DeInit();
}

Serialize_Status_t call_SerializeUnit_BuildReadResponse(uint16_t did, const uint8_t *pData, uint16_t dataLength, Serialize_UdsResponse_t *pResponse)
{
    return SerializeUnit_BuildReadResponse(did, pData, dataLength, pResponse);
}

Serialize_Status_t call_SerializeUnit_BuildWriteResponse(uint16_t did, Serialize_UdsResponse_t *pResponse)
{
    return SerializeUnit_BuildWriteResponse(did, pResponse);
}

Serialize_Status_t call_SerializeUnit_BuildRoutineResponse(uint8_t routineControlType, uint16_t rid, const uint8_t *pStatusRecord, uint16_t statusLength, Serialize_UdsResponse_t *pResponse)
{
    return SerializeUnit_BuildRoutineResponse(routineControlType, rid, pStatusRecord, statusLength, pResponse);
}

Serialize_Status_t call_SerializeUnit_BuildNegativeResponse(uint8_t requestSid, uint8_t nrc, Serialize_UdsResponse_t *pResponse)
{
    return SerializeUnit_BuildNegativeResponse(requestSid, nrc, pResponse);
}