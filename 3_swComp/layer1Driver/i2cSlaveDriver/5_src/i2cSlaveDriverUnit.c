// I2cSlaveDriver Implementation
#include "i2cSlaveDriver.h"
#include "i2cSlaveDriverUnit.h"

typedef struct
{
    bool initialized;
    I2cSlaveDriver_Config_t config;
    uint8_t *pRxBuffer;
    uint16_t rxMaxLength;
    uint16_t rxLength;
    const uint8_t *pTxBuffer;
    uint16_t txLength;
    I2cSlaveDriver_RxCallback_t rxCallback;
    I2cSlaveDriver_TxCallback_t txCallback;
    I2cSlaveDriver_AddressMatchCallback_t addressCallback;
} I2cSlaveDriver_Context_t;

static I2cSlaveDriver_Context_t context = {0};

I2cSlaveDriver_Status_t I2cSlaveDriverUnit_Init(const I2cSlaveDriver_Config_t *pConfig)
{
    if (pConfig == NULL)
    {
        return I2C_SLAVE_STATUS_ERROR;
    }

    // TODO: Add vendor-specific HAL initialization here
    context.config = *pConfig;
    context.initialized = true;
    context.pRxBuffer = NULL;
    context.rxMaxLength = 0;
    context.rxLength = 0;
    context.pTxBuffer = NULL;
    context.txLength = 0;
    context.rxCallback = NULL;
    context.txCallback = NULL;
    context.addressCallback = NULL;
    return I2C_SLAVE_STATUS_OK;
}

I2cSlaveDriver_Status_t I2cSlaveDriverUnit_SetAddress(I2cSlaveDriver_Address_t address)
{
    if (!context.initialized)
    {
        return I2C_SLAVE_STATUS_NOT_INITIALIZED;
    }
    context.config.ownAddress = address;
    return I2C_SLAVE_STATUS_OK;
}

I2cSlaveDriver_Status_t I2cSlaveDriverUnit_GetAddress(I2cSlaveDriver_Address_t *pAddress)
{
    if (pAddress == NULL)
    {
        return I2C_SLAVE_STATUS_ERROR;
    }
    *pAddress = context.config.ownAddress;
    return I2C_SLAVE_STATUS_OK;
}

I2cSlaveDriver_Status_t I2cSlaveDriverUnit_SetTxBuffer(const uint8_t *pData, uint16_t length)
{
    if (!context.initialized)
    {
        return I2C_SLAVE_STATUS_NOT_INITIALIZED;
    }
    if (pData == NULL || length == 0)
    {
        return I2C_SLAVE_STATUS_ERROR;
    }
    context.pTxBuffer = pData;
    context.txLength = length;
    return I2C_SLAVE_STATUS_OK;
}

I2cSlaveDriver_Status_t I2cSlaveDriverUnit_SetRxBuffer(uint8_t *pData, uint16_t maxLength)
{
    if (!context.initialized)
    {
        return I2C_SLAVE_STATUS_NOT_INITIALIZED;
    }
    if (pData == NULL || maxLength == 0)
    {
        return I2C_SLAVE_STATUS_ERROR;
    }
    context.pRxBuffer = pData;
    context.rxMaxLength = maxLength;
    context.rxLength = 0;
    return I2C_SLAVE_STATUS_OK;
}

I2cSlaveDriver_Status_t I2cSlaveDriverUnit_GetRxLength(uint16_t *pLength)
{
    if (pLength == NULL)
    {
        return I2C_SLAVE_STATUS_ERROR;
    }
    *pLength = context.rxLength;
    return I2C_SLAVE_STATUS_OK;
}

I2cSlaveDriver_Status_t I2cSlaveDriverUnit_IsAddressed(bool *pIsAddressed)
{
    if (pIsAddressed == NULL)
    {
        return I2C_SLAVE_STATUS_ERROR;
    }
    *pIsAddressed = false;
    return I2C_SLAVE_STATUS_OK;
}

I2cSlaveDriver_Status_t I2cSlaveDriverUnit_RegisterRxCallback(I2cSlaveDriver_RxCallback_t callback)
{
    if (!context.initialized)
    {
        return I2C_SLAVE_STATUS_NOT_INITIALIZED;
    }
    context.rxCallback = callback;
    return I2C_SLAVE_STATUS_OK;
}

I2cSlaveDriver_Status_t I2cSlaveDriverUnit_RegisterTxCallback(I2cSlaveDriver_TxCallback_t callback)
{
    if (!context.initialized)
    {
        return I2C_SLAVE_STATUS_NOT_INITIALIZED;
    }
    context.txCallback = callback;
    return I2C_SLAVE_STATUS_OK;
}

I2cSlaveDriver_Status_t I2cSlaveDriverUnit_RegisterAddressMatchCallback(I2cSlaveDriver_AddressMatchCallback_t callback)
{
    if (!context.initialized)
    {
        return I2C_SLAVE_STATUS_NOT_INITIALIZED;
    }
    context.addressCallback = callback;
    return I2C_SLAVE_STATUS_OK;
}

I2cSlaveDriver_Status_t I2cSlaveDriverUnit_DeInit(void)
{
    // TODO: Add vendor-specific HAL deinitialization here
    context.initialized = false;
    return I2C_SLAVE_STATUS_OK;
}
