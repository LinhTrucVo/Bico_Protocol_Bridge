#ifndef SERIALIZEUNIT_H
#define SERIALIZEUNIT_H
#include <stdint.h>
#include <stdbool.h>
#include "serializeCfg.h"

//============================================================================
// Configuration Macros
//============================================================================
#define SERIALIZE_MAX_RESPONSE_SIZE      256U

//============================================================================
// UDS Response SID Offset
//============================================================================
#define SERIALIZE_POSITIVE_RESPONSE_OFFSET   0x40U
#define SERIALIZE_NEGATIVE_RESPONSE_SID      0x7FU

//============================================================================
// NRC (Negative Response Codes)
//============================================================================
#define SERIALIZE_NRC_SERVICE_NOT_SUPPORTED          0x11U
#define SERIALIZE_NRC_INCORRECT_MSG_LENGTH           0x13U
#define SERIALIZE_NRC_REQUEST_OUT_OF_RANGE           0x31U
#define SERIALIZE_NRC_CONDITIONS_NOT_CORRECT         0x22U
#define SERIALIZE_NRC_GENERAL_REJECT                 0x10U

//============================================================================
// Status Codes
//============================================================================
typedef enum
{
    SERIALIZE_STATUS_OK = 0,
    SERIALIZE_STATUS_ERROR,
    SERIALIZE_STATUS_INVALID_PARAM,
    SERIALIZE_STATUS_BUFFER_OVERFLOW
} Serialize_Status_t;

//============================================================================
// UDS Response Structure
//============================================================================
typedef struct
{
    uint8_t buffer[SERIALIZE_MAX_RESPONSE_SIZE];
    uint16_t length;
} Serialize_UdsResponse_t;

//============================================================================
// Function Declarations
//============================================================================
Serialize_Status_t SerializeUnit_Init(void);
Serialize_Status_t SerializeUnit_DeInit(void);

/* Build positive response for SID 0x22 (ReadDataByIdentifier) */
/* Response: [0x62, DID_HI, DID_LO, Data...] */
Serialize_Status_t SerializeUnit_BuildReadResponse(
    uint16_t did,
    const uint8_t *pData,
    uint16_t dataLength,
    Serialize_UdsResponse_t *pResponse);

/* Build positive response for SID 0x2E (WriteDataByIdentifier) */
/* Response: [0x6E, DID_HI, DID_LO] */
Serialize_Status_t SerializeUnit_BuildWriteResponse(
    uint16_t did,
    Serialize_UdsResponse_t *pResponse);

/* Build positive response for SID 0x31 (RoutineControl) */
/* Response: [0x71, routineControlType, RID_HI, RID_LO, statusRecord...] */
Serialize_Status_t SerializeUnit_BuildRoutineResponse(
    uint8_t routineControlType,
    uint16_t rid,
    const uint8_t *pStatusRecord,
    uint16_t statusLength,
    Serialize_UdsResponse_t *pResponse);

/* Build negative response */
/* Response: [0x7F, requestSID, NRC] */
Serialize_Status_t SerializeUnit_BuildNegativeResponse(
    uint8_t requestSid,
    uint8_t nrc,
    Serialize_UdsResponse_t *pResponse);

#endif /* SERIALIZEUNIT_H */