#ifndef SERIALIZEUNIT_H
#define SERIALIZEUNIT_H

//============================================================================
// Dependencies
//============================================================================
#include <stdint.h>
#include <stdbool.h>
#include "serializeCfg.h"

//============================================================================
// Configuration Macros
//============================================================================
#define SERIALIZE_CFG_MAX_FRAME_SIZE      256
#define SERIALIZE_CFG_MAX_PAYLOAD_SIZE    224
#define SERIALIZE_CFG_CRC_POLY            0x1021
#define SERIALIZE_CFG_CRC_INIT            0xFFFF

//============================================================================
// Type Definitions
//============================================================================
typedef struct
{
    uint8_t *pBuffer;
    uint16_t bufferLength;
} Serialize_Buffer_t;

typedef enum
{
    SERIALIZE_MSG_TYPE_REQUEST = 0,
    SERIALIZE_MSG_TYPE_RESPONSE = 1,
    SERIALIZE_MSG_TYPE_EVENT = 2,
    SERIALIZE_MSG_TYPE_ERROR = 3
} Serialize_MessageType_t;

typedef struct
{
    uint8_t commandId;
    uint8_t sequenceId;
    Serialize_MessageType_t type;
} Serialize_Header_t;

typedef struct
{
    Serialize_Header_t header;
    const uint8_t *pPayload;
    uint16_t payloadLength;
} Serialize_Message_t;

typedef enum
{
    SERIALIZE_ERROR_OK = 0,
    SERIALIZE_ERROR_INVALID_PARAM,
    SERIALIZE_ERROR_INVALID_COMMAND,
    SERIALIZE_ERROR_BUFFER_OVERFLOW,
    SERIALIZE_ERROR_UNKNOWN
} Serialize_ErrorCode_t;

typedef enum
{
    SERIALIZE_STATUS_OK = 0,
    SERIALIZE_STATUS_ERROR,
    SERIALIZE_STATUS_INVALID_PARAM,
    SERIALIZE_STATUS_BUFFER_TOO_SMALL,
    SERIALIZE_STATUS_BUFFER_OVERFLOW
} Serialize_Status_t;

//============================================================================
// Public Functions
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

//============================================================================
// Backward Compatibility Macros
//============================================================================
#define Serialize_Init SerializeUnit_Init
#define Serialize_DeInit SerializeUnit_DeInit
#define Serialize_BuildFrame SerializeUnit_BuildFrame
#define Serialize_BuildError SerializeUnit_BuildError
#define Serialize_BuildAnalogSamples SerializeUnit_BuildAnalogSamples
#define Serialize_BuildDigitalRead SerializeUnit_BuildDigitalRead
#define Serialize_BuildI2CRead SerializeUnit_BuildI2CRead
#define Serialize_BuildSPITransfer SerializeUnit_BuildSPITransfer
#define Serialize_ComputeCrc SerializeUnit_ComputeCrc
#define SERIALIZE_ERROR_INVALID_CMD SERIALIZE_ERROR_INVALID_COMMAND

#endif /* SERIALIZEUNIT_H */
