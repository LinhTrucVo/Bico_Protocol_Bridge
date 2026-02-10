#ifndef SERIALIZEUNIT_H
#define SERIALIZEUNIT_H

//============================================================================
// Dependencies
//============================================================================
#include <stdint.h>
#include <stdbool.h>
#include "serializeCfg.h"

//============================================================================
// Forward declarations (types defined in serialize.h)
//============================================================================
typedef enum Serialize_Status_t Serialize_Status_t;
typedef enum Serialize_ErrorCode_t Serialize_ErrorCode_t;
typedef struct Serialize_Message_t Serialize_Message_t;
typedef struct Serialize_Buffer_t Serialize_Buffer_t;

//============================================================================
// Public Functions
//============================================================================
Serialize_Status_t SerializeUnit_Init(void);
Serialize_Status_t SerializeUnit_DeInit(void);
Serialize_Status_t SerializeUnit_BuildFrame(const Serialize_Message_t *pMessage, Serialize_Buffer_t *pOutBuffer, uint16_t *pFrameLength);
Serialize_Status_t SerializeUnit_BuildError(uint8_t commandId, uint8_t sequenceId, Serialize_ErrorCode_t errorCode, Serialize_Buffer_t *pOutBuffer, uint16_t *pFrameLength);
Serialize_Status_t SerializeUnit_BuildAnalogSamples(uint8_t channelId, const uint16_t *pSamples, uint16_t sampleCount, Serialize_Buffer_t *pOutBuffer, uint16_t *pFrameLength);
Serialize_Status_t SerializeUnit_BuildDigitalRead(uint8_t pinId, uint8_t state, Serialize_Buffer_t *pOutBuffer, uint16_t *pFrameLength);
Serialize_Status_t SerializeUnit_BuildI2CRead(uint8_t address, const uint8_t *pData, uint16_t length, Serialize_Buffer_t *pOutBuffer, uint16_t *pFrameLength);
Serialize_Status_t SerializeUnit_BuildSPITransfer(const uint8_t *pTxData, const uint8_t *pRxData, uint16_t length, Serialize_Buffer_t *pOutBuffer, uint16_t *pFrameLength);
Serialize_Status_t SerializeUnit_ComputeCrc(const uint8_t *pData, uint16_t length, uint16_t *pCrc);

#endif /* SERIALIZEUNIT_H */
