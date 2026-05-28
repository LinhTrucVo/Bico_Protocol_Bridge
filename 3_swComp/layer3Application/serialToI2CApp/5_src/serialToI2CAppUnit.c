// SerialToI2CApp Implementation - Typed I2C API

#include <stddef.h>
#include "serialToI2CApp.h"
#include "serialToI2CAppCfg.h"
#include "i2cMasterDriver.h"

typedef struct
{
    bool initialized;
} SerialToI2CApp_Context_t;

static SerialToI2CApp_Context_t context = {0};

SerialToI2CApp_Status_t SerialToI2CApp_Init(void)
{
    I2cMasterDriver_Config_t i2cCfg = {0};
    i2cCfg.speed = I2C_SPEED_STANDARD;
    i2cCfg.addressMode = I2C_ADDRESS_7BIT;
    i2cCfg.enableDMA = false;
    i2cCfg.enableInterrupt = false;
    i2cCfg.timeoutMs = I2C_MASTER_CFG_TIMEOUT_MS;

    if (I2cMasterDriverUnit_Init(&i2cCfg) != I2CMASTERDRIVERSTATUS_OK)
    {
        return SERIAL_TO_I2C_APP_STATUS_ERROR;
    }

    context.initialized = true;
    return SERIAL_TO_I2C_APP_STATUS_OK;
}

SerialToI2CApp_Status_t SerialToI2CApp_DeInit(void)
{
    if (context.initialized)
    {
        (void)I2cMasterDriverUnit_DeInit();
    }
    context.initialized = false;
    return SERIAL_TO_I2C_APP_STATUS_OK;
}

SerialToI2CApp_Status_t SerialToI2CApp_Write(uint16_t address, const uint8_t *pData, uint16_t length)
{
    if (!context.initialized)
    {
        return SERIAL_TO_I2C_APP_STATUS_NOT_INITIALIZED;
    }
    if (pData == NULL || length == 0U || length > SERIAL_TO_I2C_CFG_MAX_TRANSFER)
    {
        return SERIAL_TO_I2C_APP_STATUS_INVALID_PARAM;
    }

    I2cMasterDriver_Status_t drvStatus = I2cMasterDriverUnit_Write(
        (I2cMasterDriver_Address_t)address, pData, length);

    if (drvStatus == I2CMASTERDRIVERSTATUS_NACK)
    {
        return SERIAL_TO_I2C_APP_STATUS_NACK;
    }
    if (drvStatus != I2CMASTERDRIVERSTATUS_OK)
    {
        return SERIAL_TO_I2C_APP_STATUS_BUS_ERROR;
    }

    return SERIAL_TO_I2C_APP_STATUS_OK;
}

SerialToI2CApp_Status_t SerialToI2CApp_Read(uint16_t address, uint8_t *pData, uint16_t length)
{
    if (!context.initialized)
    {
        return SERIAL_TO_I2C_APP_STATUS_NOT_INITIALIZED;
    }
    if (pData == NULL || length == 0U || length > SERIAL_TO_I2C_CFG_MAX_TRANSFER)
    {
        return SERIAL_TO_I2C_APP_STATUS_INVALID_PARAM;
    }

    I2cMasterDriver_Status_t drvStatus = I2cMasterDriverUnit_Read(
        (I2cMasterDriver_Address_t)address, pData, length);

    if (drvStatus == I2CMASTERDRIVERSTATUS_NACK)
    {
        return SERIAL_TO_I2C_APP_STATUS_NACK;
    }
    if (drvStatus != I2CMASTERDRIVERSTATUS_OK)
    {
        return SERIAL_TO_I2C_APP_STATUS_BUS_ERROR;
    }

    return SERIAL_TO_I2C_APP_STATUS_OK;
}