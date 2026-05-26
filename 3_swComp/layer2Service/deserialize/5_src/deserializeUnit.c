// Deserialize Implementation - UDS Request Parser

#include <stddef.h>
#include "deserialize.h"
#include "deserializeCfg.h"

typedef struct
{
    bool initialized;
} Deserialize_Context_t;

static Deserialize_Context_t context = {false};

Deserialize_Status_t DeserializeUnit_Init(void)
{
    context.initialized = true;
    return DESERIALIZE_STATUS_OK;
}

Deserialize_Status_t DeserializeUnit_DeInit(void)
{
    context.initialized = false;
    return DESERIALIZE_STATUS_OK;
}

Deserialize_Status_t DeserializeUnit_Parse(const Deserialize_Frame_t *pFrame, Deserialize_UdsRequest_t *pRequest)
{
    if (!context.initialized)
    {
        return DESERIALIZE_STATUS_ERROR;
    }
    if (pFrame == NULL || pFrame->pData == NULL || pRequest == NULL)
    {
        return DESERIALIZE_STATUS_INVALID_PARAM;
    }
    if (pFrame->length < DESERIALIZE_MIN_FRAME_SIZE)
    {
        return DESERIALIZE_STATUS_INVALID_FRAME;
    }

    const uint8_t *pBuf = pFrame->pData;
    uint8_t sid = pBuf[0];

    pRequest->sid = sid;
    pRequest->routineControlType = 0U;
    pRequest->pPayload = NULL;
    pRequest->payloadLength = 0U;
    pRequest->id = 0U;

    switch (sid)
    {
        case DESERIALIZE_SID_READ_DATA_BY_ID: /* 0x22 */
        {
            /* Frame: [SID(1), DID_HI(1), DID_LO(1)] */
            if (pFrame->length < 3U)
            {
                return DESERIALIZE_STATUS_INVALID_FRAME;
            }
            pRequest->id = ((uint16_t)pBuf[1] << 8U) | (uint16_t)pBuf[2];
            /* No payload for read request */
            break;
        }

        case DESERIALIZE_SID_WRITE_DATA_BY_ID: /* 0x2E */
        {
            /* Frame: [SID(1), DID_HI(1), DID_LO(1), Data...] */
            if (pFrame->length < 4U) /* At least 1 byte of data required */
            {
                return DESERIALIZE_STATUS_INVALID_FRAME;
            }
            pRequest->id = ((uint16_t)pBuf[1] << 8U) | (uint16_t)pBuf[2];
            pRequest->pPayload = &pBuf[3];
            pRequest->payloadLength = pFrame->length - 3U;
            break;
        }

        case DESERIALIZE_SID_ROUTINE_CONTROL: /* 0x31 */
        {
            /* Frame: [SID(1), routineControlType(1), RID_HI(1), RID_LO(1), params...] */
            if (pFrame->length < 4U)
            {
                return DESERIALIZE_STATUS_INVALID_FRAME;
            }
            pRequest->routineControlType = pBuf[1];
            pRequest->id = ((uint16_t)pBuf[2] << 8U) | (uint16_t)pBuf[3];
            if (pFrame->length > 4U)
            {
                pRequest->pPayload = &pBuf[4];
                pRequest->payloadLength = pFrame->length - 4U;
            }
            break;
        }

        default:
            return DESERIALIZE_STATUS_UNSUPPORTED_SID;
    }

    return DESERIALIZE_STATUS_OK;
}