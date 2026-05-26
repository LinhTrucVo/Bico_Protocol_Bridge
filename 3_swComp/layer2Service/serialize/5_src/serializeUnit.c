// Serialize Implementation - UDS Response Builder

#include <stddef.h>
#include <string.h>
#include "serialize.h"
#include "serializeCfg.h"

//============================================================================
// UDS Response SIDs (requestSID + 0x40)
//============================================================================
#define RESPONSE_SID_READ_DATA_BY_ID    0x62U  /* 0x22 + 0x40 */
#define RESPONSE_SID_WRITE_DATA_BY_ID   0x6EU  /* 0x2E + 0x40 */
#define RESPONSE_SID_ROUTINE_CONTROL    0x71U  /* 0x31 + 0x40 */

typedef struct
{
    bool initialized;
} Serialize_Context_t;

static Serialize_Context_t context = {false};

Serialize_Status_t SerializeUnit_Init(void)
{
    context.initialized = true;
    return SERIALIZE_STATUS_OK;
}

Serialize_Status_t SerializeUnit_DeInit(void)
{
    context.initialized = false;
    return SERIALIZE_STATUS_OK;
}

Serialize_Status_t SerializeUnit_BuildReadResponse(
    uint16_t did,
    const uint8_t *pData,
    uint16_t dataLength,
    Serialize_UdsResponse_t *pResponse)
{
    if (!context.initialized)
    {
        return SERIALIZE_STATUS_ERROR;
    }
    if (pResponse == NULL || (dataLength > 0U && pData == NULL))
    {
        return SERIALIZE_STATUS_INVALID_PARAM;
    }

    uint16_t totalLength = 3U + dataLength; /* responseSID(1) + DID(2) + data */
    if (totalLength > SERIALIZE_MAX_RESPONSE_SIZE)
    {
        return SERIALIZE_STATUS_BUFFER_OVERFLOW;
    }

    pResponse->buffer[0] = RESPONSE_SID_READ_DATA_BY_ID; /* 0x62 */
    pResponse->buffer[1] = (uint8_t)(did >> 8U);
    pResponse->buffer[2] = (uint8_t)(did & 0xFFU);

    if (dataLength > 0U)
    {
        (void)memcpy(&pResponse->buffer[3], pData, dataLength);
    }

    pResponse->length = totalLength;
    return SERIALIZE_STATUS_OK;
}

Serialize_Status_t SerializeUnit_BuildWriteResponse(
    uint16_t did,
    Serialize_UdsResponse_t *pResponse)
{
    if (!context.initialized)
    {
        return SERIALIZE_STATUS_ERROR;
    }
    if (pResponse == NULL)
    {
        return SERIALIZE_STATUS_INVALID_PARAM;
    }

    pResponse->buffer[0] = RESPONSE_SID_WRITE_DATA_BY_ID; /* 0x6E */
    pResponse->buffer[1] = (uint8_t)(did >> 8U);
    pResponse->buffer[2] = (uint8_t)(did & 0xFFU);
    pResponse->length = 3U;

    return SERIALIZE_STATUS_OK;
}

Serialize_Status_t SerializeUnit_BuildRoutineResponse(
    uint8_t routineControlType,
    uint16_t rid,
    const uint8_t *pStatusRecord,
    uint16_t statusLength,
    Serialize_UdsResponse_t *pResponse)
{
    if (!context.initialized)
    {
        return SERIALIZE_STATUS_ERROR;
    }
    if (pResponse == NULL || (statusLength > 0U && pStatusRecord == NULL))
    {
        return SERIALIZE_STATUS_INVALID_PARAM;
    }

    uint16_t totalLength = 4U + statusLength; /* responseSID(1) + type(1) + RID(2) + statusRecord */
    if (totalLength > SERIALIZE_MAX_RESPONSE_SIZE)
    {
        return SERIALIZE_STATUS_BUFFER_OVERFLOW;
    }

    pResponse->buffer[0] = RESPONSE_SID_ROUTINE_CONTROL; /* 0x71 */
    pResponse->buffer[1] = routineControlType;
    pResponse->buffer[2] = (uint8_t)(rid >> 8U);
    pResponse->buffer[3] = (uint8_t)(rid & 0xFFU);

    if (statusLength > 0U)
    {
        (void)memcpy(&pResponse->buffer[4], pStatusRecord, statusLength);
    }

    pResponse->length = totalLength;
    return SERIALIZE_STATUS_OK;
}

Serialize_Status_t SerializeUnit_BuildNegativeResponse(
    uint8_t requestSid,
    uint8_t nrc,
    Serialize_UdsResponse_t *pResponse)
{
    if (!context.initialized)
    {
        return SERIALIZE_STATUS_ERROR;
    }
    if (pResponse == NULL)
    {
        return SERIALIZE_STATUS_INVALID_PARAM;
    }

    pResponse->buffer[0] = SERIALIZE_NEGATIVE_RESPONSE_SID; /* 0x7F */
    pResponse->buffer[1] = requestSid;
    pResponse->buffer[2] = nrc;
    pResponse->length = 3U;

    return SERIALIZE_STATUS_OK;
}