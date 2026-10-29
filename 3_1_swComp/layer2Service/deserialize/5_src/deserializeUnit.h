#ifndef BPB_DESERIALIZEUNIT_H
#define BPB_DESERIALIZEUNIT_H
#include <stdint.h>
#include <stdbool.h>
#include "deserializeCfg.h"

//============================================================================
// Configuration Macros
//============================================================================
#define BPB_DESERIALIZE_MAX_FRAME_SIZE      256U
#define BPB_DESERIALIZE_MAX_PAYLOAD_SIZE    250U
#define BPB_DESERIALIZE_MIN_FRAME_SIZE      3U   /* SID(1) + DID(2) minimum */

//============================================================================
// UDS Service Identifiers
//============================================================================
#define BPB_DESERIALIZE_SID_READ_DATA_BY_ID     0x22U
#define BPB_DESERIALIZE_SID_WRITE_DATA_BY_ID    0x2EU
#define BPB_DESERIALIZE_SID_ROUTINE_CONTROL     0x31U

//============================================================================
// Status Codes
//============================================================================
typedef enum
{
    BPB_DESERIALIZE_STATUS_OK = 0,
    BPB_DESERIALIZE_STATUS_ERROR,
    BPB_DESERIALIZE_STATUS_INVALID_PARAM,
    BPB_DESERIALIZE_STATUS_INVALID_FRAME,
    BPB_DESERIALIZE_STATUS_UNSUPPORTED_SID
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

#endif /* BPB_DESERIALIZEUNIT_H */