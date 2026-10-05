// This file is used to define the public interface of the component unit.
// It contains public macros, private variables, and function definitions.

//============================================================================
// Dependencies
//============================================================================
#include <stddef.h>
#include <string.h>
#include "i2cMasterDriver.h"
#include "i2cMasterDriverCfg.h"
#include "i2cMasterDriverUnit.h"
#include "i2cMasterDriverPorting.h"

//============================================================================
// Local Macros
//============================================================================
#define I2C_MASTER_SCAN_FIRST_ADDRESS       0x08U
#define I2C_MASTER_SCAN_LAST_ADDRESS        0x77U
#define I2C_MASTER_SCAN_TIMEOUT_MS          10U

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
// Local Function Prototypes
//============================================================================
static uint32_t I2cMasterDriverUnit_DefaultTimeout(void);
static I2cMasterDriver_Status_t I2cMasterDriverUnit_Complete(I2cMasterPort_Result_t result);

//============================================================================
// Public Function Implementations
//============================================================================

I2cMasterDriver_Status_t I2cMasterDriverUnit_Init(const I2cMasterDriver_Config_t *pConfig)
{
    if (pConfig == NULL)
    {
        return I2C_MASTER_STATUS_INVALID_PARAM;
    }
    if (i2cMasterContext.initialized)
    {
        I2cMasterPort_DeInit();
    }

    (void)memset(&i2cMasterContext, 0, sizeof(i2cMasterContext));
    if (!I2cMasterPort_Init((uint32_t)pConfig->speed))
    {
        return I2C_MASTER_STATUS_ERROR;
    }

    i2cMasterContext.config = *pConfig;
    i2cMasterContext.initialized = true;
    return I2C_MASTER_STATUS_OK;
}

I2cMasterDriver_Status_t I2cMasterDriverUnit_SetSpeed(I2cMasterDriver_Speed_t speed)
{
    if (!i2cMasterContext.initialized)
    {
        return I2C_MASTER_STATUS_ERROR;
    }

    if (!I2cMasterPort_SetSpeed((uint32_t)speed))
    {
        return I2C_MASTER_STATUS_ERROR;
    }
    i2cMasterContext.config.speed = speed;
    return I2C_MASTER_STATUS_OK;
}

I2cMasterDriver_Status_t I2cMasterDriverUnit_Write(I2cMasterDriver_Address_t address, const uint8_t *pData, uint16_t length)
{
    return I2cMasterDriverUnit_WriteWithTimeout(address, pData, length, I2cMasterDriverUnit_DefaultTimeout());
}

I2cMasterDriver_Status_t I2cMasterDriverUnit_WriteWithTimeout(I2cMasterDriver_Address_t address, const uint8_t *pData, uint16_t length, uint32_t timeoutMs)
{
    if (!i2cMasterContext.initialized)
    {
        return I2C_MASTER_STATUS_ERROR;
    }
    if (pData == NULL || length == 0 || length > I2C_MAX_TRANSFER_SIZE)
    {
        return I2C_MASTER_STATUS_INVALID_PARAM;
    }

    i2cMasterContext.busy = true;
    const I2cMasterPort_Result_t result = I2cMasterPort_Write(address, pData, length, timeoutMs);
    return I2cMasterDriverUnit_Complete(result);
}

I2cMasterDriver_Status_t I2cMasterDriverUnit_Read(I2cMasterDriver_Address_t address, uint8_t *pData, uint16_t length)
{
    return I2cMasterDriverUnit_ReadWithTimeout(address, pData, length, I2cMasterDriverUnit_DefaultTimeout());
}

I2cMasterDriver_Status_t I2cMasterDriverUnit_ReadWithTimeout(I2cMasterDriver_Address_t address, uint8_t *pData, uint16_t length, uint32_t timeoutMs)
{
    if (!i2cMasterContext.initialized)
    {
        return I2C_MASTER_STATUS_ERROR;
    }
    if (pData == NULL || length == 0 || length > I2C_MAX_TRANSFER_SIZE)
    {
        return I2C_MASTER_STATUS_INVALID_PARAM;
    }

    i2cMasterContext.busy = true;
    const I2cMasterPort_Result_t result = I2cMasterPort_Read(address, pData, length, timeoutMs);
    return I2cMasterDriverUnit_Complete(result);
}

I2cMasterDriver_Status_t I2cMasterDriverUnit_WriteRead(I2cMasterDriver_Address_t address, const uint8_t *pWriteData, uint16_t writeLength, uint8_t *pReadData, uint16_t readLength)
{
    if (!i2cMasterContext.initialized)
    {
        return I2C_MASTER_STATUS_ERROR;
    }
    if (pWriteData == NULL || pReadData == NULL || writeLength == 0 || readLength == 0 ||
        writeLength > I2C_MAX_TRANSFER_SIZE || readLength > I2C_MAX_TRANSFER_SIZE)
    {
        return I2C_MASTER_STATUS_INVALID_PARAM;
    }

    i2cMasterContext.busy = true;
    const I2cMasterPort_Result_t result = I2cMasterPort_WriteRead(address, pWriteData, writeLength, pReadData, readLength,
                                                                  I2cMasterDriverUnit_DefaultTimeout());
    return I2cMasterDriverUnit_Complete(result);
}

I2cMasterDriver_Status_t I2cMasterDriverUnit_WriteRegister(I2cMasterDriver_Address_t address, uint8_t regAddress, const uint8_t *pData, uint16_t length)
{
    if (!i2cMasterContext.initialized)
    {
        return I2C_MASTER_STATUS_ERROR;
    }
    if (pData == NULL || length == 0 || length >= I2C_MAX_TRANSFER_SIZE)
    {
        return I2C_MASTER_STATUS_INVALID_PARAM;
    }

    uint8_t frame[I2C_MAX_TRANSFER_SIZE];
    frame[0] = regAddress;
    (void)memcpy(&frame[1], pData, length);
    return I2cMasterDriverUnit_Write(address, frame, (uint16_t)(length + 1U));
}

I2cMasterDriver_Status_t I2cMasterDriverUnit_ReadRegister(I2cMasterDriver_Address_t address, uint8_t regAddress, uint8_t *pData, uint16_t length)
{
    return I2cMasterDriverUnit_WriteRead(address, &regAddress, 1U, pData, length);
}

I2cMasterDriver_Status_t I2cMasterDriverUnit_ScanBus(I2cMasterDriver_Address_t *pFoundAddresses, uint8_t maxAddresses, uint8_t *pNumFound)
{
    if (pFoundAddresses == NULL || pNumFound == NULL)
    {
        return I2C_MASTER_STATUS_INVALID_PARAM;
    }
    if (!i2cMasterContext.initialized)
    {
        return I2C_MASTER_STATUS_ERROR;
    }

    *pNumFound = 0;
    for (uint16_t address = I2C_MASTER_SCAN_FIRST_ADDRESS;
         (address <= I2C_MASTER_SCAN_LAST_ADDRESS) && (*pNumFound < maxAddresses);
         address++)
    {
        if (I2cMasterPort_Probe(address, I2C_MASTER_SCAN_TIMEOUT_MS))
        {
            pFoundAddresses[*pNumFound] = (I2cMasterDriver_Address_t)address;
            (*pNumFound)++;
        }
    }
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
    if (i2cMasterContext.initialized)
    {
        I2cMasterPort_DeInit();
    }
    (void)memset(&i2cMasterContext, 0, sizeof(i2cMasterContext));
    return I2C_MASTER_STATUS_OK;
}

//============================================================================
// Local Function Implementations
//============================================================================

static uint32_t I2cMasterDriverUnit_DefaultTimeout(void)
{
    return (i2cMasterContext.config.timeoutMs != 0U) ? i2cMasterContext.config.timeoutMs : I2C_MASTER_CFG_TIMEOUT_MS;
}

static I2cMasterDriver_Status_t I2cMasterDriverUnit_Complete(I2cMasterPort_Result_t result)
{
    I2cMasterDriver_Status_t status = I2C_MASTER_STATUS_ERROR;
    if (result == I2CMASTERPORT_OK)
    {
        status = I2C_MASTER_STATUS_OK;
    }
    else if (result == I2CMASTERPORT_TIMEOUT)
    {
        status = I2C_MASTER_STATUS_TIMEOUT;
    }

    i2cMasterContext.busy = false;
    if (i2cMasterContext.callback != NULL)
    {
        i2cMasterContext.callback(status);
    }
    return status;
}
