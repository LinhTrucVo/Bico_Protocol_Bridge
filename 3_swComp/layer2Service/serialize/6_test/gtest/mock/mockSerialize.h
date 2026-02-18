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
// Mock function declarations
//============================================================================
// Declare fake functions for external dependencies if any
// DECLARE_FAKE_VALUE_FUNC(int, ExternalFunction, int);

//============================================================================
// Static function wrapper declarations
//============================================================================

Serialize_Status_t call_SerializeUnit_Init(void);
Serialize_Status_t call_SerializeUnit_DeInit(void);
Serialize_Status_t call_SerializeUnit_BuildFrame(const Serialize_Message_t *pMessage, Serialize_Buffer_t *pOutBuffer, uint16_t *pFrameLength);
Serialize_Status_t call_SerializeUnit_BuildError(uint8_t commandId, uint8_t sequenceId, Serialize_ErrorCode_t errorCode, Serialize_Buffer_t *pOutBuffer, uint16_t *pFrameLength);
Serialize_Status_t call_SerializeUnit_BuildAnalogSamples(uint8_t channelId, const uint16_t *pSamples, uint16_t sampleCount, Serialize_Buffer_t *pOutBuffer, uint16_t *pFrameLength);
Serialize_Status_t call_SerializeUnit_BuildDigitalRead(uint8_t pinId, uint8_t state, Serialize_Buffer_t *pOutBuffer, uint16_t *pFrameLength);
Serialize_Status_t call_SerializeUnit_BuildI2CRead(uint8_t address, const uint8_t *pData, uint16_t length, Serialize_Buffer_t *pOutBuffer, uint16_t *pFrameLength);
Serialize_Status_t call_SerializeUnit_BuildSPITransfer(const uint8_t *pTxData, const uint8_t *pRxData, uint16_t length, Serialize_Buffer_t *pOutBuffer, uint16_t *pFrameLength);
Serialize_Status_t call_SerializeUnit_ComputeCrc(const uint8_t *pData, uint16_t length, uint16_t *pCrc);

#endif /* MOCKSERIALIZE_H */
