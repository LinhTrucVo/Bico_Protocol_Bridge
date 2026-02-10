// This file is used to define the public interface of the component unit.
// It contains public macros, private variables, and function definitions.

//============================================================================
// Dependencies
//============================================================================
#include "i2cMasterDriver.h"
#include "i2cMasterDriverCfg.h"
#include "i2cMasterDriverUnit.h"

//============================================================================
// Local Macros
//============================================================================

//============================================================================
// Local Types
//============================================================================
typedef struct
{
    bool initialized;
    bool busy;
    I2cMasterDriver_Config_t config;
    I2cMasterDriver_Callback_t callback;
} I2cMasterDriver_Context_t;

//============================================================================
// Variables
//============================================================================
static I2cMasterDriver_Context_t i2cMasterContext = {0};

//============================================================================
// Public Function Implementations
//============================================================================

I2cMasterDriver_Status_t I2cMasterDriverUnit_Init(const I2cMasterDriver_Config_t *pConfig)
{
    if (pConfig == NULL)
    {
        return I2C_MASTER_STATUS_INVALID_PARAM;
    }

    // TODO: Add vendor-specific HAL I2C initialization here
    i2cMasterContext.config = *pConfig;
    i2cMasterContext.initialized = true;
    i2cMasterContext.busy = false;
    i2cMasterContext.callback = NULL;
    return I2C_MASTER_STATUS_OK;
}

I2cMasterDriver_Status_t I2cMasterDriverUnit_SetSpeed(I2cMasterDriver_Speed_t speed)
{
    if (!i2cMasterContext.initialized)
    {
        return I2C_MASTER_STATUS_ERROR;
    }

    i2cMasterContext.config.speed = speed;
    return I2C_MASTER_STATUS_OK;
}

I2cMasterDriver_Status_t I2cMasterDriverUnit_Write(I2cMasterDriver_Address_t address, const uint8_t *pData, uint16_t length)
{
    (void)address;
    if (!i2cMasterContext.initialized)
    {
        return I2C_MASTER_STATUS_ERROR;
    }
    if (pData == NULL || length == 0 || length > I2C_MAX_TRANSFER_SIZE)
    {
        return I2C_MASTER_STATUS_INVALID_PARAM;
    }

    // TODO: Add vendor-specific HAL I2C write here
    if (i2cMasterContext.callback != NULL)
    {
        i2cMasterContext.callback(I2C_MASTER_STATUS_OK);
    }
    return I2C_MASTER_STATUS_OK;
}

I2cMasterDriver_Status_t I2cMasterDriverUnit_WriteWithTimeout(I2cMasterDriver_Address_t address, const uint8_t *pData, uint16_t length, uint32_t timeoutMs)
{
    (void)timeoutMs;
    return I2cMasterDriverUnit_Write(address, pData, length);
}

I2cMasterDriver_Status_t I2cMasterDriverUnit_Read(I2cMasterDriver_Address_t address, uint8_t *pData, uint16_t length)
{
    (void)address;
    if (!i2cMasterContext.initialized)
    {
        return I2C_MASTER_STATUS_ERROR;
    }
    if (pData == NULL || length == 0 || length > I2C_MAX_TRANSFER_SIZE)
    {
        return I2C_MASTER_STATUS_INVALID_PARAM;
    }

    // TODO: Add vendor-specific HAL I2C read here
    return I2C_MASTER_STATUS_OK;
}

I2cMasterDriver_Status_t I2cMasterDriverUnit_ReadWithTimeout(I2cMasterDriver_Address_t address, uint8_t *pData, uint16_t length, uint32_t timeoutMs)
{
    (void)timeoutMs;
    return I2cMasterDriverUnit_Read(address, pData, length);
}

I2cMasterDriver_Status_t I2cMasterDriverUnit_WriteRead(I2cMasterDriver_Address_t address, const uint8_t *pWriteData, uint16_t writeLength, uint8_t *pReadData, uint16_t readLength)
{
    if (!i2cMasterContext.initialized)
    {
        return I2C_MASTER_STATUS_ERROR;
    }
    if (pWriteData == NULL || pReadData == NULL)
    {
        return I2C_MASTER_STATUS_INVALID_PARAM;
    }

    // TODO: Add vendor-specific HAL I2C write-read here
    (void)address;
    (void)writeLength;
    (void)readLength;
    return I2C_MASTER_STATUS_OK;
}

I2cMasterDriver_Status_t I2cMasterDriverUnit_WriteRegister(I2cMasterDriver_Address_t address, uint8_t regAddress, const uint8_t *pData, uint16_t length)
{
    (void)regAddress;
    return I2cMasterDriverUnit_Write(address, pData, length);
}

I2cMasterDriver_Status_t I2cMasterDriverUnit_ReadRegister(I2cMasterDriver_Address_t address, uint8_t regAddress, uint8_t *pData, uint16_t length)
{
    (void)regAddress;
    return I2cMasterDriverUnit_Read(address, pData, length);
}

I2cMasterDriver_Status_t I2cMasterDriverUnit_ScanBus(I2cMasterDriver_Address_t *pFoundAddresses, uint8_t maxAddresses, uint8_t *pNumFound)
{
    if (pFoundAddresses == NULL || pNumFound == NULL)
    {
        return I2C_MASTER_STATUS_INVALID_PARAM;
    }
    (void)maxAddresses;
    *pNumFound = 0;
    return I2C_MASTER_STATUS_OK;
}

I2cMasterDriver_Status_t I2cMasterDriverUnit_IsBusy(bool *pIsBusy)
{
    if (pIsBusy == NULL)
    {
        return I2C_MASTER_STATUS_INVALID_PARAM;
    }
    *pIsBusy = i2cMasterContext.busy;
    return I2C_MASTER_STATUS_OK;
}

I2cMasterDriver_Status_t I2cMasterDriverUnit_RegisterCallback(I2cMasterDriver_Callback_t callback)
{
    if (!i2cMasterContext.initialized)
    {
        return I2C_MASTER_STATUS_ERROR;
    }
    i2cMasterContext.callback = callback;
    return I2C_MASTER_STATUS_OK;
}

I2cMasterDriver_Status_t I2cMasterDriverUnit_DeInit(void)
{
    // TODO: Add vendor-specific HAL deinitialization here
    i2cMasterContext.initialized = false;
    i2cMasterContext.busy = false;
    i2cMasterContext.callback = NULL;
    return I2C_MASTER_STATUS_OK;
}
