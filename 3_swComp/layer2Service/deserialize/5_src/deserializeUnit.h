#ifndef DESERIALIZEUNIT_H
#define DESERIALIZEUNIT_H
#include <stdint.h>
#include <stdbool.h>
#include "deserializeCfg.h"

//============================================================================
// Configuration Macros
//============================================================================
#define DESERIALIZE_MAX_FRAME_SIZE      256U
#define DESERIALIZE_MAX_PAYLOAD_SIZE    250U
#define DESERIALIZE_MIN_FRAME_SIZE      3U   /* SID(1) + DID(2) minimum */

//============================================================================
// UDS Service Identifiers
//============================================================================
#define DESERIALIZE_SID_READ_DATA_BY_ID     0x22U
#define DESERIALIZE_SID_WRITE_DATA_BY_ID    0x2EU
#define DESERIALIZE_SID_ROUTINE_CONTROL     0x31U

//============================================================================
// Status Codes
//============================================================================
typedef enum
{
    DESERIALIZE_STATUS_OK = 0,
    DESERIALIZE_STATUS_ERROR,
    DESERIALIZE_STATUS_INVALID_PARAM,
    DESERIALIZE_STATUS_INVALID_FRAME,
    DESERIALIZE_STATUS_UNSUPPORTED_SID
} Deserialize_Status_t;

//============================================================================
// UDS Request Structure
//============================================================================
typedef struct
{
    uint8_t sid;                     /* Service Identifier (0x22, 0x2E, 0x31) */
    uint16_t id;                     /* DID or RoutineIdentifier (big-endian decoded) */
    uint8_t routineControlType;      /* Only for SID 0x31 (0x01=start, 0x02=stop, 0x03=requestResults) */
    const uint8_t *pPayload;         /* Data payload (write data or routine params) */
    uint16_t payloadLength;          /* Length of payload in bytes */
} Deserialize_UdsRequest_t;

//============================================================================
// Input Frame Structure
//============================================================================
typedef struct
{
    const uint8_t *pData;
    uint16_t length;
} Deserialize_Frame_t;

//============================================================================
// Function Declarations
//============================================================================
Deserialize_Status_t DeserializeUnit_Init(void);
Deserialize_Status_t DeserializeUnit_DeInit(void);
Deserialize_Status_t DeserializeUnit_Parse(const Deserialize_Frame_t *pFrame, Deserialize_UdsRequest_t *pRequest);

#endif /* DESERIALIZEUNIT_H */