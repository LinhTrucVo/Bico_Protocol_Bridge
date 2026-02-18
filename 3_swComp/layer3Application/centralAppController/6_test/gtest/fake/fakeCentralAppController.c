// Fake implementations for CentralAppController testing
// Centralizes all dependency fakes: Serialize and Deserialize

#include <stddef.h>
#include <string.h>
#include "fakeCentralAppController.h"
#include "serialize.h"
#include "deserialize.h"

/* ============================================================
 * Fake Serialize implementations
 * ============================================================ */

Serialize_Status_t Serialize_Init(void)
{
    return SERIALIZE_STATUS_OK;
}

Serialize_Status_t Serialize_DeInit(void)
{
    return SERIALIZE_STATUS_OK;
}

Serialize_Status_t Serialize_BuildError(uint8_t commandId, uint8_t sequenceId, Serialize_ErrorCode_t errorCode, Serialize_Buffer_t *pOutBuffer, uint16_t *pFrameLength)
{
    if (pOutBuffer == NULL || pFrameLength == NULL || pOutBuffer->pBuffer == NULL)
    {
        return SERIALIZE_STATUS_INVALID_PARAM;
    }

    if (pOutBuffer->bufferLength < 8)
    {
        return SERIALIZE_STATUS_BUFFER_TOO_SMALL;
    }

    pOutBuffer->pBuffer[0] = commandId;
    pOutBuffer->pBuffer[1] = sequenceId;
    pOutBuffer->pBuffer[2] = SERIALIZE_MSG_TYPE_ERROR;
    pOutBuffer->pBuffer[3] = 1;
    pOutBuffer->pBuffer[4] = (uint8_t)errorCode;
    pOutBuffer->pBuffer[5] = 0;
    pOutBuffer->pBuffer[6] = 0;
    *pFrameLength = 7;

    return SERIALIZE_STATUS_OK;
}

Serialize_Status_t Serialize_BuildFrame(const Serialize_Message_t *pMessage, Serialize_Buffer_t *pOutBuffer, uint16_t *pFrameLength)
{
    if (pMessage == NULL || pOutBuffer == NULL || pFrameLength == NULL || pOutBuffer->pBuffer == NULL)
    {
        return SERIALIZE_STATUS_INVALID_PARAM;
    }

    if (pOutBuffer->bufferLength < 7)
    {
        return SERIALIZE_STATUS_BUFFER_TOO_SMALL;
    }

    pOutBuffer->pBuffer[0] = pMessage->header.commandId;
    pOutBuffer->pBuffer[1] = pMessage->header.sequenceId;
    pOutBuffer->pBuffer[2] = pMessage->header.type;
    pOutBuffer->pBuffer[3] = (uint8_t)(pMessage->payloadLength & 0xFFU);

    uint16_t offset = 4;
    if (pMessage->pPayload != NULL && pMessage->payloadLength > 0)
    {
        if (pMessage->payloadLength + offset + 2 > pOutBuffer->bufferLength)
        {
            return SERIALIZE_STATUS_BUFFER_TOO_SMALL;
        }
        memcpy(&pOutBuffer->pBuffer[offset], pMessage->pPayload, pMessage->payloadLength);
        offset += pMessage->payloadLength;
    }

    pOutBuffer->pBuffer[offset]     = 0;
    pOutBuffer->pBuffer[offset + 1] = 0;
    *pFrameLength = offset + 2;

    return SERIALIZE_STATUS_OK;
}

Serialize_Status_t Serialize_BuildAnalogSamples(uint8_t channelId, const uint16_t *pSamples, uint16_t sampleCount, Serialize_Buffer_t *pOutBuffer, uint16_t *pFrameLength)
{
    (void)channelId; (void)pSamples; (void)sampleCount; (void)pOutBuffer; (void)pFrameLength;
    return SERIALIZE_STATUS_OK;
}

Serialize_Status_t Serialize_BuildDigitalRead(uint8_t pinId, uint8_t state, Serialize_Buffer_t *pOutBuffer, uint16_t *pFrameLength)
{
    (void)pinId; (void)state; (void)pOutBuffer; (void)pFrameLength;
    return SERIALIZE_STATUS_OK;
}

Serialize_Status_t Serialize_BuildI2CRead(uint8_t address, const uint8_t *pData, uint16_t length, Serialize_Buffer_t *pOutBuffer, uint16_t *pFrameLength)
{
    (void)address; (void)pData; (void)length; (void)pOutBuffer; (void)pFrameLength;
    return SERIALIZE_STATUS_OK;
}

Serialize_Status_t Serialize_BuildSPITransfer(const uint8_t *pTxData, const uint8_t *pRxData, uint16_t length, Serialize_Buffer_t *pOutBuffer, uint16_t *pFrameLength)
{
    (void)pTxData; (void)pRxData; (void)length; (void)pOutBuffer; (void)pFrameLength;
    return SERIALIZE_STATUS_OK;
}

Serialize_Status_t Serialize_ComputeCrc(const uint8_t *pData, uint16_t length, uint16_t *pCrc)
{
    (void)pData; (void)length;
    if (pCrc == NULL)
    {
        return SERIALIZE_STATUS_INVALID_PARAM;
    }
    *pCrc = 0x0000;
    return SERIALIZE_STATUS_OK;
}

/* ============================================================
 * Fake Deserialize implementations
 * ============================================================ */

Deserialize_Status_t DeserializeUnit_Init(void)
{
    return DESERIALIZE_STATUS_OK;
}

Deserialize_Status_t DeserializeUnit_DeInit(void)
{
    return DESERIALIZE_STATUS_OK;
}

Deserialize_Status_t DeserializeUnit_ValidateFrame(const Deserialize_Frame_t *pFrame)
{
    if (pFrame == NULL || pFrame->pFrame == NULL)
    {
        return DESERIALIZE_STATUS_INVALID_FRAME;
    }

    if (pFrame->frameLength < 5)
    {
        return DESERIALIZE_STATUS_INVALID_FRAME;
    }

    return DESERIALIZE_STATUS_OK;
}

Deserialize_Status_t DeserializeUnit_ParseFrame(const Deserialize_Frame_t *pFrame, Deserialize_Request_t *pRequest)
{
    if (pFrame == NULL || pRequest == NULL || pFrame->pFrame == NULL)
    {
        return DESERIALIZE_STATUS_INVALID_FRAME;
    }

    if (pFrame->frameLength < 5)
    {
        return DESERIALIZE_STATUS_INVALID_FRAME;
    }

    pRequest->commandId  = pFrame->pFrame[0];
    pRequest->sequenceId = pFrame->pFrame[1];

    uint8_t cmdId = pFrame->pFrame[0];
    switch (cmdId)
    {
        case 0x01: pRequest->command = DESERIALIZE_CMD_ADC_CONFIG;    break;
        case 0x02: pRequest->command = DESERIALIZE_CMD_ADC_READ;      break;
        case 0x03: pRequest->command = DESERIALIZE_CMD_DIGITAL_WRITE; break;
        case 0x04: pRequest->command = DESERIALIZE_CMD_DIGITAL_READ;  break;
        default:   pRequest->command = DESERIALIZE_CMD_NONE;          break;
    }

    uint16_t payloadLen = pFrame->pFrame[3] | (uint16_t)((uint16_t)pFrame->pFrame[4] << 8);

    if (payloadLen > 0 && pFrame->frameLength > 5)
    {
        pRequest->pPayload     = &pFrame->pFrame[5];
        pRequest->payloadLength = (payloadLen > pFrame->frameLength - 7u)
                                  ? (pFrame->frameLength - 7u)
                                  : payloadLen;
    }
    else
    {
        pRequest->pPayload      = NULL;
        pRequest->payloadLength = 0;
    }

    return DESERIALIZE_STATUS_OK;
}

Deserialize_Status_t DeserializeUnit_ComputeCrc(const uint8_t *pData, uint16_t length, uint16_t *pCrc)
{
    (void)pData; (void)length;
    if (pCrc == NULL)
    {
        return DESERIALIZE_STATUS_INVALID_PARAM;
    }
    *pCrc = 0x0000;
    return DESERIALIZE_STATUS_OK;
}
