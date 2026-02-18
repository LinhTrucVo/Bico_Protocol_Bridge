#ifndef DESERIALIZEUNIT_H
#define DESERIALIZEUNIT_H
#include <stdint.h>
#include <stdbool.h>
#include "deserializeCfg.h"

//============================================================================
// Configuration Macros
//============================================================================
#define DESERIALIZE_CFG_MAX_FRAME_SIZE      256
#define DESERIALIZE_CFG_MAX_PAYLOAD_SIZE    224
#define DESERIALIZE_CFG_CRC_POLY            0x1021
#define DESERIALIZE_CFG_CRC_INIT            0xFFFF

//============================================================================
// Status Codes
//============================================================================
typedef enum
{
    DESERIALIZE_STATUS_OK = 0,
    DESERIALIZE_STATUS_ERROR,
    DESERIALIZE_STATUS_INVALID_PARAM,
    DESERIALIZE_STATUS_INVALID_FRAME,
    DESERIALIZE_STATUS_CRC_ERROR,
    DESERIALIZE_STATUS_UNSUPPORTED_CMD
} Deserialize_Status_t;

//============================================================================
// Command Types
//============================================================================
typedef enum
{
    DESERIALIZE_CMD_NONE = 0,
    DESERIALIZE_CMD_ADC_CONFIG,
    DESERIALIZE_CMD_ADC_READ,
    DESERIALIZE_CMD_DIGITAL_WRITE,
    DESERIALIZE_CMD_DIGITAL_READ,
    DESERIALIZE_CMD_PWM_CONFIG,
    DESERIALIZE_CMD_PWM_START,
    DESERIALIZE_CMD_PWM_STOP,
    DESERIALIZE_CMD_I2C_WRITE,
    DESERIALIZE_CMD_I2C_READ,
    DESERIALIZE_CMD_SPI_TRANSFER,
    DESERIALIZE_CMD_CONFIG_SAVE,
    DESERIALIZE_CMD_CONFIG_LOAD
} Deserialize_Command_t;

//============================================================================
// Structures
//============================================================================
typedef struct
{
    const uint8_t *pFrame;
    uint16_t frameLength;
} Deserialize_Frame_t;

typedef struct
{
    uint8_t commandId;
    uint8_t sequenceId;
    Deserialize_Command_t command;
    const uint8_t *pPayload;
    uint16_t payloadLength;
} Deserialize_Request_t;

//============================================================================
// Function declarations
//============================================================================
Deserialize_Status_t DeserializeUnit_Init(void);
Deserialize_Status_t DeserializeUnit_DeInit(void);
Deserialize_Status_t DeserializeUnit_ValidateFrame(const Deserialize_Frame_t *pFrame);
Deserialize_Status_t DeserializeUnit_ParseFrame(const Deserialize_Frame_t *pFrame, Deserialize_Request_t *pRequest);
Deserialize_Status_t DeserializeUnit_ComputeCrc(const uint8_t *pData, uint16_t length, uint16_t *pCrc);

#endif
