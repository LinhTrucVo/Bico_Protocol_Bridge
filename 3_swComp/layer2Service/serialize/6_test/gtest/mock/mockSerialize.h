// This file declares the FFF for functions and MOCK functions for Serialize testing

#ifndef MOCKSERIALIZE_H
#define MOCKSERIALIZE_H

//============================================================================
// Dependencies
//============================================================================
#include "fff.h"

#include "serialize.h"
#include "serializeUnit.h"

//============================================================================
// Static function wrapper declarations
//============================================================================

Serialize_Status_t call_SerializeUnit_Init(void);
Serialize_Status_t call_SerializeUnit_DeInit(void);
Serialize_Status_t call_SerializeUnit_BuildReadResponse(uint16_t did, const uint8_t *pData, uint16_t dataLength, Serialize_UdsResponse_t *pResponse);
Serialize_Status_t call_SerializeUnit_BuildWriteResponse(uint16_t did, Serialize_UdsResponse_t *pResponse);
Serialize_Status_t call_SerializeUnit_BuildRoutineResponse(uint8_t routineControlType, uint16_t rid, const uint8_t *pStatusRecord, uint16_t statusLength, Serialize_UdsResponse_t *pResponse);
Serialize_Status_t call_SerializeUnit_BuildNegativeResponse(uint8_t requestSid, uint8_t nrc, Serialize_UdsResponse_t *pResponse);

#endif /* MOCKSERIALIZE_H */