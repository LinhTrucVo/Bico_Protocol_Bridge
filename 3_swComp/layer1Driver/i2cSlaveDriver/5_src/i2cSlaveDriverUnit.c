// I2cSlaveDriver Implementation
#include <stddef.h>
#include <string.h>
#include "i2cSlaveDriver.h"
#include "i2cSlaveDriverUnit.h"
#include "i2cSlaveDriverPorting.h"

#define I2C_SLAVE_WRITE_TIMEOUT_MS  100U

typedef struct
{
    bool initialized;
    bool addressed;
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

static bool I2cSlaveDriverUnit_StartPort(I2cSlaveDriver_Address_t address);
static void I2cSlaveDriverUnit_OnPortReceive(const uint8_t *pData, uint16_t length);
static void I2cSlaveDriverUnit_OnPortRequest(void);

I2cSlaveDriver_Status_t I2cSlaveDriverUnit_Init(const I2cSlaveDriver_Config_t *pConfig)
{
    if (pConfig == NULL)
    {
        return I2C_SLAVE_STATUS_ERROR;
    }
    if (context.initialized)
    {
        I2cSlavePort_DeInit();
    }

    (void)memset(&context, 0, sizeof(context));
    if (!I2cSlaveDriverUnit_StartPort(pConfig->ownAddress))
    {
        return I2C_SLAVE_STATUS_ERROR;
    }

    context.config = *pConfig;
    context.initialized = true;
    return I2C_SLAVE_STATUS_OK;
}

I2cSlaveDriver_Status_t I2cSlaveDriverUnit_SetAddress(I2cSlaveDriver_Address_t address)
{
    if (!context.initialized)
    {
        return I2C_SLAVE_STATUS_NOT_INITIALIZED;
    }

    // The address is fixed when the port is started, so the port is restarted.
    I2cSlavePort_DeInit();
    if (!I2cSlaveDriverUnit_StartPort(address))
    {
        context.initialized = false;
        return I2C_SLAVE_STATUS_ERROR;
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
    if (pData == NULL || length == 0 || length > I2C_SLAVE_MAX_BUFFER_SIZE)
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
    *pIsAddressed = context.addressed;
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
    if (context.initialized)
    {
        I2cSlavePort_DeInit();
    }
    (void)memset(&context, 0, sizeof(context));
    return I2C_SLAVE_STATUS_OK;
}

static bool I2cSlaveDriverUnit_StartPort(I2cSlaveDriver_Address_t address)
{
    if (!I2cSlavePort_Init(address))
    {
        return false;
    }
    I2cSlavePort_SetReceiveHandler(I2cSlaveDriverUnit_OnPortReceive);
    I2cSlavePort_SetRequestHandler(I2cSlaveDriverUnit_OnPortRequest);
    return true;
}

static void I2cSlaveDriverUnit_OnPortReceive(const uint8_t *pData, uint16_t length)
{
    const uint8_t *pReported = pData;
    uint16_t reportedLength = length;

    if (context.pRxBuffer != NULL)
    {
        reportedLength = (length < context.rxMaxLength) ? length : context.rxMaxLength;
        (void)memcpy(context.pRxBuffer, pData, reportedLength);
        pReported = context.pRxBuffer;
    }
    context.rxLength = reportedLength;

    if (context.addressCallback != NULL)
    {
        context.addressCallback(context.config.ownAddress);
    }
    if (context.rxCallback != NULL)
    {
        context.rxCallback(pReported, reportedLength);
    }
}

static void I2cSlaveDriverUnit_OnPortRequest(void)
{
    context.addressed = true;
    if (context.addressCallback != NULL)
    {
        context.addressCallback(context.config.ownAddress);
    }

    uint8_t scratch[I2C_SLAVE_MAX_BUFFER_SIZE];
    const uint8_t *pSource = context.pTxBuffer;
    uint16_t length = context.txLength;

    if (context.txCallback != NULL)
    {
        length = I2C_SLAVE_MAX_BUFFER_SIZE;
        context.txCallback(scratch, &length);
        pSource = scratch;
        if (length > I2C_SLAVE_MAX_BUFFER_SIZE)
        {
            length = I2C_SLAVE_MAX_BUFFER_SIZE;
        }
    }

    if (pSource != NULL && length > 0U)
    {
        (void)I2cSlavePort_Write(pSource, length, I2C_SLAVE_WRITE_TIMEOUT_MS);
    }
    context.addressed = false;
}
