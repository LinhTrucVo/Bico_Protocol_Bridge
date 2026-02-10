// SerialToI2CApp Implementation

#include "serialToI2CApp.h"
#include "serialToI2CAppCfg.h"

typedef struct
{
    bool initialized;
    SerialToI2CApp_State_t currentState;
    SerialToI2CApp_Config_t config;
} SerialToI2CApp_Context_t;

static SerialToI2CApp_Context_t context = {0};

SerialToI2CApp_Status_t SerialToI2CApp_Init(void)
{
    context.initialized = true;
    context.currentState = SerialToI2CApp_STATE_IDLE;
    context.config.speed = SERIAL_TO_I2C_CFG_DEFAULT_SPEED;
    context.config.addressMode = SERIAL_TO_I2C_ADDR_7BIT;
    context.config.timeoutMs = SERIAL_TO_I2C_CFG_DEFAULT_TIMEOUT;
    return SERIAL_TO_I2C_APP_STATUS_OK;
}

SerialToI2CApp_Status_t SerialToI2CApp_DeInit(void)
{
    context.initialized = false;
    context.currentState = SerialToI2CApp_STATE_IDLE;
    return SERIAL_TO_I2C_APP_STATUS_OK;
}

SerialToI2CApp_Status_t SerialToI2CApp_Run(void)
{
    if (!context.initialized)
    {
        return SERIAL_TO_I2C_APP_STATUS_NOT_INITIALIZED;
    }
    return SERIAL_TO_I2C_APP_STATUS_OK;
}

SerialToI2CApp_Status_t SerialToI2CApp_GetState(SerialToI2CApp_State_t *pState)
{
    if (pState == NULL)
    {
        return SERIAL_TO_I2C_APP_STATUS_INVALID_PARAM;
    }
    *pState = context.currentState;
    return SERIAL_TO_I2C_APP_STATUS_OK;
}

SerialToI2CApp_Status_t SerialToI2CApp_Configure(const SerialToI2CApp_Config_t *pConfig)
{
    if (pConfig == NULL)
    {
        return SERIAL_TO_I2C_APP_STATUS_INVALID_PARAM;
    }
    context.config = *pConfig;
    return SERIAL_TO_I2C_APP_STATUS_OK;
}

SerialToI2CApp_Status_t SerialToI2CApp_GetConfig(SerialToI2CApp_Config_t *pConfig)
{
    if (pConfig == NULL)
    {
        return SERIAL_TO_I2C_APP_STATUS_INVALID_PARAM;
    }
    *pConfig = context.config;
    return SERIAL_TO_I2C_APP_STATUS_OK;
}

SerialToI2CApp_Status_t SerialToI2CApp_Write(uint16_t address, const uint8_t *pData, uint16_t length)
{
    (void)address;
    if (pData == NULL || length == 0 || length > SERIAL_TO_I2C_CFG_MAX_TRANSFER)
    {
        return SERIAL_TO_I2C_APP_STATUS_INVALID_PARAM;
    }
    return SERIAL_TO_I2C_APP_STATUS_OK;
}

SerialToI2CApp_Status_t SerialToI2CApp_Read(uint16_t address, uint8_t *pData, uint16_t length)
{
    (void)address;
    if (pData == NULL || length == 0 || length > SERIAL_TO_I2C_CFG_MAX_TRANSFER)
    {
        return SERIAL_TO_I2C_APP_STATUS_INVALID_PARAM;
    }
    for (uint16_t i = 0; i < length; i++)
    {
        pData[i] = 0;
    }
    return SERIAL_TO_I2C_APP_STATUS_OK;
}

SerialToI2CApp_Status_t SerialToI2CApp_WriteRead(const SerialToI2CApp_Transfer_t *pTransfer)
{
    if (pTransfer == NULL)
    {
        return SERIAL_TO_I2C_APP_STATUS_INVALID_PARAM;
    }
    if (pTransfer->pReadData != NULL && pTransfer->readLength > 0)
    {
        for (uint16_t i = 0; i < pTransfer->readLength; i++)
        {
            pTransfer->pReadData[i] = 0;
        }
    }
    return SERIAL_TO_I2C_APP_STATUS_OK;
}

SerialToI2CApp_Status_t SerialToI2CApp_SaveConfig(void)
{
    // TODO: Persist configuration using NvmService
    return SERIAL_TO_I2C_APP_STATUS_OK;
}

SerialToI2CApp_Status_t SerialToI2CApp_LoadConfig(void)
{
    // TODO: Load configuration using NvmService
    return SERIAL_TO_I2C_APP_STATUS_OK;
}
