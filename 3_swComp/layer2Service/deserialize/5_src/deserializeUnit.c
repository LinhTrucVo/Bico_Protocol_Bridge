// Deserialize Implementation

#include "deserialize.h"
#include "deserializeCfg.h"

#define DESERIALIZE_HEADER_SIZE   5
#define DESERIALIZE_CRC_SIZE      2

typedef struct
{
    bool initialized;
} Deserialize_Context_t;

static Deserialize_Context_t context = {false};

static uint16_t Deserialize_ComputeCrc16(const uint8_t *pData, uint16_t length)
{
    uint16_t crc = DESERIALIZE_CFG_CRC_INIT;
    for (uint16_t i = 0; i < length; i++)
    {
        crc ^= (uint16_t)pData[i] << 8U;
        for (uint8_t j = 0; j < 8; j++)
        {
            if (crc & 0x8000U)
            {
                crc = (crc << 1U) ^ DESERIALIZE_CFG_CRC_POLY;
            }
            else
            {
                crc <<= 1U;
            }
        }
    }
    return crc;
}

static Deserialize_Command_t Deserialize_MapCommand(uint8_t commandId)
{
    switch (commandId)
    {
        case 0x01: return DESERIALIZE_CMD_ADC_CONFIG;
        case 0x02: return DESERIALIZE_CMD_ADC_READ;
        case 0x03: return DESERIALIZE_CMD_DIGITAL_WRITE;
        case 0x04: return DESERIALIZE_CMD_DIGITAL_READ;
        case 0x05: return DESERIALIZE_CMD_PWM_CONFIG;
        case 0x06: return DESERIALIZE_CMD_PWM_START;
        case 0x07: return DESERIALIZE_CMD_PWM_STOP;
        case 0x08: return DESERIALIZE_CMD_I2C_WRITE;
        case 0x09: return DESERIALIZE_CMD_I2C_READ;
        case 0x0A: return DESERIALIZE_CMD_SPI_TRANSFER;
        case 0x0B: return DESERIALIZE_CMD_CONFIG_SAVE;
        case 0x0C: return DESERIALIZE_CMD_CONFIG_LOAD;
        default: return DESERIALIZE_CMD_NONE;
    }
}

Deserialize_Status_t Deserialize_Init(void)
{
    context.initialized = true;
    return DESERIALIZE_STATUS_OK;
}

Deserialize_Status_t Deserialize_DeInit(void)
{
    context.initialized = false;
    return DESERIALIZE_STATUS_OK;
}

Deserialize_Status_t Deserialize_ValidateFrame(const Deserialize_Frame_t *pFrame)
{
    if (pFrame == NULL || pFrame->pFrame == NULL)
    {
        return DESERIALIZE_STATUS_INVALID_PARAM;
    }
    if (pFrame->frameLength < (DESERIALIZE_HEADER_SIZE + DESERIALIZE_CRC_SIZE))
    {
        return DESERIALIZE_STATUS_INVALID_FRAME;
    }

    const uint8_t *pBuf = pFrame->pFrame;
    uint16_t payloadLength = (uint16_t)pBuf[3] | ((uint16_t)pBuf[4] << 8U);
    uint16_t expectedLength = DESERIALIZE_HEADER_SIZE + payloadLength + DESERIALIZE_CRC_SIZE;
    if (expectedLength != pFrame->frameLength)
    {
        return DESERIALIZE_STATUS_INVALID_FRAME;
    }

    uint16_t crcCalc = Deserialize_ComputeCrc16(pBuf, DESERIALIZE_HEADER_SIZE + payloadLength);
    uint16_t crcFrame = (uint16_t)pBuf[DESERIALIZE_HEADER_SIZE + payloadLength] |
                        ((uint16_t)pBuf[DESERIALIZE_HEADER_SIZE + payloadLength + 1U] << 8U);
    if (crcCalc != crcFrame)
    {
        return DESERIALIZE_STATUS_CRC_ERROR;
    }

    return DESERIALIZE_STATUS_OK;
}

Deserialize_Status_t Deserialize_ParseFrame(const Deserialize_Frame_t *pFrame, Deserialize_Request_t *pRequest)
{
    if (!context.initialized)
    {
        return DESERIALIZE_STATUS_ERROR;
    }
    if (pFrame == NULL || pRequest == NULL)
    {
        return DESERIALIZE_STATUS_INVALID_PARAM;
    }

    Deserialize_Status_t status = Deserialize_ValidateFrame(pFrame);
    if (status != DESERIALIZE_STATUS_OK)
    {
        return status;
    }

    const uint8_t *pBuf = pFrame->pFrame;
    uint16_t payloadLength = (uint16_t)pBuf[3] | ((uint16_t)pBuf[4] << 8U);
    pRequest->commandId = pBuf[0];
    pRequest->sequenceId = pBuf[1];
    pRequest->command = Deserialize_MapCommand(pBuf[0]);
    if (pRequest->command == DESERIALIZE_CMD_NONE)
    {
        return DESERIALIZE_STATUS_UNSUPPORTED_CMD;
    }
    pRequest->pPayload = &pBuf[DESERIALIZE_HEADER_SIZE];
    pRequest->payloadLength = payloadLength;
    return DESERIALIZE_STATUS_OK;
}

Deserialize_Status_t Deserialize_ComputeCrc(const uint8_t *pData, uint16_t length, uint16_t *pCrc)
{
    if (pData == NULL || pCrc == NULL)
    {
        return DESERIALIZE_STATUS_INVALID_PARAM;
    }
    *pCrc = Deserialize_ComputeCrc16(pData, length);
    return DESERIALIZE_STATUS_OK;
}

Deserialize_Status_t Deserialize_GetCommandName(Deserialize_Command_t command, const char **pName)
{
    if (pName == NULL)
    {
        return DESERIALIZE_STATUS_INVALID_PARAM;
    }
    switch (command)
    {
        case DESERIALIZE_CMD_ADC_CONFIG: *pName = "ADC_CONFIG"; break;
        case DESERIALIZE_CMD_ADC_READ: *pName = "ADC_READ"; break;
        case DESERIALIZE_CMD_DIGITAL_WRITE: *pName = "DIGITAL_WRITE"; break;
        case DESERIALIZE_CMD_DIGITAL_READ: *pName = "DIGITAL_READ"; break;
        case DESERIALIZE_CMD_PWM_CONFIG: *pName = "PWM_CONFIG"; break;
        case DESERIALIZE_CMD_PWM_START: *pName = "PWM_START"; break;
        case DESERIALIZE_CMD_PWM_STOP: *pName = "PWM_STOP"; break;
        case DESERIALIZE_CMD_I2C_WRITE: *pName = "I2C_WRITE"; break;
        case DESERIALIZE_CMD_I2C_READ: *pName = "I2C_READ"; break;
        case DESERIALIZE_CMD_SPI_TRANSFER: *pName = "SPI_TRANSFER"; break;
        case DESERIALIZE_CMD_CONFIG_SAVE: *pName = "CONFIG_SAVE"; break;
        case DESERIALIZE_CMD_CONFIG_LOAD: *pName = "CONFIG_LOAD"; break;
        default: *pName = "UNKNOWN"; return DESERIALIZE_STATUS_UNSUPPORTED_CMD;
    }
    return DESERIALIZE_STATUS_OK;
}
