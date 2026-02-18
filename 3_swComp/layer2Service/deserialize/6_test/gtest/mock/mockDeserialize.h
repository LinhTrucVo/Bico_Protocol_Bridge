// This file declares the FFF for functions and MOCK functions for Deserialize testing

#ifndef MOCKDESERIALIZE_H
#define MOCKDESERIALIZE_H

//============================================================================
// Dependencies
//============================================================================
#include "fff.h"

#include "deserialize.h"
#include "deserializeUnit.h"

//============================================================================
// Mock function declarations
//============================================================================
// Declare fake functions for external dependencies if any
// DECLARE_FAKE_VALUE_FUNC(int, ExternalFunction, int);

//============================================================================
// Static function wrapper declarations
//============================================================================

Deserialize_Status_t call_DeserializeUnit_Init(void);
Deserialize_Status_t call_DeserializeUnit_DeInit(void);
Deserialize_Status_t call_DeserializeUnit_ValidateFrame(const Deserialize_Frame_t *pFrame);
Deserialize_Status_t call_DeserializeUnit_ParseFrame(const Deserialize_Frame_t *pFrame, Deserialize_Request_t *pRequest);
Deserialize_Status_t call_DeserializeUnit_ComputeCrc(const uint8_t *pData, uint16_t length, uint16_t *pCrc);

#endif /* MOCKDESERIALIZE_H */
