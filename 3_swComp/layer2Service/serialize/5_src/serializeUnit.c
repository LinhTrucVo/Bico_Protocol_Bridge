// Serialize Implementation

#include "serialize.h"
#include "serializeCfg.h"

#define SERIALIZE_HEADER_SIZE   5
#define SERIALIZE_CRC_SIZE      2

typedef struct
{
    bool initialized;
} Serialize_Context_t;

static Serialize_Context_t context = {false};

static uint16_t Serialize_ComputeCrc16(const uint8_t *pData, uint16_t length)
{
    uint16_t crc = SERIALIZE_CFG_CRC_INIT;
    for (uint16_t i = 0; i < length; i++)
    {
        crc ^= (uint16_t)pData[i] << 8U;
        for (uint8_t j = 0; j < 8; j++)
        {
            if (crc & 0x8000U)
            {
                crc = (crc << 1U) ^ SERIALIZE_CFG_CRC_POLY;
            }
            else
            {
                crc <<= 1U;
            }
        }
    }
    return crc;
}

Serialize_Status_t Serialize_Init(void)
{
    context.initialized = true;
    return SERIALIZE_STATUS_OK;
}

Serialize_Status_t Serialize_DeInit(void)
{
    context.initialized = false;
    return SERIALIZE_STATUS_OK;
}

Serialize_Status_t Serialize_BuildFrame(const Serialize_Message_t *pMessage, Serialize_Buffer_t *pOutBuffer, uint16_t *pFrameLength)
{
    if (!context.initialized)
    {
        return SERIALIZE_STATUS_ERROR;
    }
    if (pMessage == NULL || pOutBuffer == NULL || pFrameLength == NULL || pOutBuffer->pBuffer == NULL)
    {
        return SERIALIZE_STATUS_INVALID_PARAM;
    }
    if (pMessage->payloadLength > SERIALIZE_CFG_MAX_PAYLOAD_SIZE)
    {
        return SERIALIZE_STATUS_INVALID_PARAM;
    }

    uint16_t totalLength = SERIALIZE_HEADER_SIZE + pMessage->payloadLength + SERIALIZE_CRC_SIZE;
    if (pOutBuffer->bufferLength < totalLength)
    {
        return SERIALIZE_STATUS_BUFFER_TOO_SMALL;
    }

    uint8_t *pBuf = pOutBuffer->pBuffer;
    pBuf[0] = pMessage->header.commandId;
    pBuf[1] = pMessage->header.sequenceId;
    pBuf[2] = (uint8_t)pMessage->header.type;
    pBuf[3] = (uint8_t)(pMessage->payloadLength & 0xFFU);
    pBuf[4] = (uint8_t)((pMessage->payloadLength >> 8U) & 0xFFU);

    for (uint16_t i = 0; i < pMessage->payloadLength; i++)
    {
        pBuf[SERIALIZE_HEADER_SIZE + i] = pMessage->pPayload[i];
    }

    uint16_t crc = Serialize_ComputeCrc16(pBuf, SERIALIZE_HEADER_SIZE + pMessage->payloadLength);
    pBuf[SERIALIZE_HEADER_SIZE + pMessage->payloadLength] = (uint8_t)(crc & 0xFFU);
    pBuf[SERIALIZE_HEADER_SIZE + pMessage->payloadLength + 1U] = (uint8_t)((crc >> 8U) & 0xFFU);

    *pFrameLength = totalLength;
    return SERIALIZE_STATUS_OK;
}

Serialize_Status_t Serialize_BuildError(uint8_t commandId, uint8_t sequenceId, Serialize_ErrorCode_t errorCode, Serialize_Buffer_t *pOutBuffer, uint16_t *pFrameLength)
{
    uint8_t payload[1] = { (uint8_t)errorCode };
    Serialize_Message_t msg = {
        .header = { commandId, sequenceId, SERIALIZE_MSG_TYPE_ERROR },
        .pPayload = payload,
        .payloadLength = 1
    };
    return Serialize_BuildFrame(&msg, pOutBuffer, pFrameLength);
}

Serialize_Status_t Serialize_BuildAnalogSamples(uint8_t channelId, const uint16_t *pSamples, uint16_t sampleCount, Serialize_Buffer_t *pOutBuffer, uint16_t *pFrameLength)
{
    if (pSamples == NULL || sampleCount == 0)
    {
        return SERIALIZE_STATUS_INVALID_PARAM;
    }

    uint8_t payload[1 + 1 + (2 * SERIALIZE_CFG_MAX_PAYLOAD_SIZE)] = {0};
    uint16_t payloadLen = 2 + (sampleCount * 2U);
    if (payloadLen > SERIALIZE_CFG_MAX_PAYLOAD_SIZE)
    {
        return SERIALIZE_STATUS_INVALID_PARAM;
    }

    payload[0] = channelId;
    payload[1] = (uint8_t)sampleCount;
    for (uint16_t i = 0; i < sampleCount; i++)
    {
        payload[2 + (i * 2U)] = (uint8_t)(pSamples[i] & 0xFFU);
        payload[3 + (i * 2U)] = (uint8_t)((pSamples[i] >> 8U) & 0xFFU);
    }

    Serialize_Message_t msg = {
        .header = { 0, 0, SERIALIZE_MSG_TYPE_RESPONSE },
        .pPayload = payload,
        .payloadLength = payloadLen
    };
    return Serialize_BuildFrame(&msg, pOutBuffer, pFrameLength);
}

Serialize_Status_t Serialize_BuildDigitalRead(uint8_t pinId, uint8_t state, Serialize_Buffer_t *pOutBuffer, uint16_t *pFrameLength)
{
    uint8_t payload[2] = { pinId, state };
    Serialize_Message_t msg = {
        .header = { 0, 0, SERIALIZE_MSG_TYPE_RESPONSE },
        .pPayload = payload,
        .payloadLength = 2
    };
    return Serialize_BuildFrame(&msg, pOutBuffer, pFrameLength);
}

Serialize_Status_t Serialize_BuildI2CRead(uint8_t address, const uint8_t *pData, uint16_t length, Serialize_Buffer_t *pOutBuffer, uint16_t *pFrameLength)
{
    if (pData == NULL || length == 0)
    {
        return SERIALIZE_STATUS_INVALID_PARAM;
    }
    if ((length + 2U) > SERIALIZE_CFG_MAX_PAYLOAD_SIZE)
    {
        return SERIALIZE_STATUS_INVALID_PARAM;
    }

    uint8_t payload[SERIALIZE_CFG_MAX_PAYLOAD_SIZE] = {0};
    payload[0] = address;
    payload[1] = (uint8_t)length;
    for (uint16_t i = 0; i < length; i++)
    {
        payload[2 + i] = pData[i];
    }

    Serialize_Message_t msg = {
        .header = { 0, 0, SERIALIZE_MSG_TYPE_RESPONSE },
        .pPayload = payload,
        .payloadLength = (uint16_t)(length + 2U)
    };
    return Serialize_BuildFrame(&msg, pOutBuffer, pFrameLength);
}

Serialize_Status_t Serialize_BuildSPITransfer(const uint8_t *pTxData, const uint8_t *pRxData, uint16_t length, Serialize_Buffer_t *pOutBuffer, uint16_t *pFrameLength)
{
    if (length == 0 || length > SERIALIZE_CFG_MAX_PAYLOAD_SIZE - 2U)
    {
        return SERIALIZE_STATUS_INVALID_PARAM;
    }

    uint8_t payload[SERIALIZE_CFG_MAX_PAYLOAD_SIZE] = {0};
    payload[0] = (uint8_t)(length & 0xFFU);
    payload[1] = (uint8_t)((length >> 8U) & 0xFFU);
    for (uint16_t i = 0; i < length; i++)
    {
        payload[2 + i] = (pRxData != NULL) ? pRxData[i] : ((pTxData != NULL) ? pTxData[i] : 0U);
    }

    Serialize_Message_t msg = {
        .header = { 0, 0, SERIALIZE_MSG_TYPE_RESPONSE },
        .pPayload = payload,
        .payloadLength = (uint16_t)(length + 2U)
    };
    return Serialize_BuildFrame(&msg, pOutBuffer, pFrameLength);
}

Serialize_Status_t Serialize_ComputeCrc(const uint8_t *pData, uint16_t length, uint16_t *pCrc)
{
    if (pData == NULL || pCrc == NULL)
    {
        return SERIALIZE_STATUS_INVALID_PARAM;
    }
    *pCrc = Serialize_ComputeCrc16(pData, length);
    return SERIALIZE_STATUS_OK;
}
