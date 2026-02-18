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

// Required for FFF
DEFINE_FFF_GLOBALS;

// DEFINE_FAKE_VALUE_FUNC(int, ExternalFunction, int);

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

Serialize_Status_t call_SerializeUnit_BuildFrame(const Serialize_Message_t *pMessage, Serialize_Buffer_t *pOutBuffer, uint16_t *pFrameLength)
{
    return SerializeUnit_BuildFrame(pMessage, pOutBuffer, pFrameLength);
}

Serialize_Status_t call_SerializeUnit_BuildError(uint8_t commandId, uint8_t sequenceId, Serialize_ErrorCode_t errorCode, Serialize_Buffer_t *pOutBuffer, uint16_t *pFrameLength)
{
    return SerializeUnit_BuildError(commandId, sequenceId, errorCode, pOutBuffer, pFrameLength);
}

Serialize_Status_t call_SerializeUnit_BuildAnalogSamples(uint8_t channelId, const uint16_t *pSamples, uint16_t sampleCount, Serialize_Buffer_t *pOutBuffer, uint16_t *pFrameLength)
{
    return SerializeUnit_BuildAnalogSamples(channelId, pSamples, sampleCount, pOutBuffer, pFrameLength);
}

Serialize_Status_t call_SerializeUnit_BuildDigitalRead(uint8_t pinId, uint8_t state, Serialize_Buffer_t *pOutBuffer, uint16_t *pFrameLength)
{
    return SerializeUnit_BuildDigitalRead(pinId, state, pOutBuffer, pFrameLength);
}

Serialize_Status_t call_SerializeUnit_BuildI2CRead(uint8_t address, const uint8_t *pData, uint16_t length, Serialize_Buffer_t *pOutBuffer, uint16_t *pFrameLength)
{
    return SerializeUnit_BuildI2CRead(address, pData, length, pOutBuffer, pFrameLength);
}

Serialize_Status_t call_SerializeUnit_BuildSPITransfer(const uint8_t *pTxData, const uint8_t *pRxData, uint16_t length, Serialize_Buffer_t *pOutBuffer, uint16_t *pFrameLength)
{
    return SerializeUnit_BuildSPITransfer(pTxData, pRxData, length, pOutBuffer, pFrameLength);
}

Serialize_Status_t call_SerializeUnit_ComputeCrc(const uint8_t *pData, uint16_t length, uint16_t *pCrc)
{
    return SerializeUnit_ComputeCrc(pData, length, pCrc);
}
