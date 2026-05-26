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
// Static function wrapper declarations
//============================================================================

Deserialize_Status_t call_DeserializeUnit_Init(void);
Deserialize_Status_t call_DeserializeUnit_DeInit(void);
Deserialize_Status_t call_DeserializeUnit_Parse(const Deserialize_Frame_t *pFrame, Deserialize_UdsRequest_t *pRequest);

#endif /* MOCKDESERIALIZE_H */