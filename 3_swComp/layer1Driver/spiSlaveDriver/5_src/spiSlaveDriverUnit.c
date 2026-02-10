// SpiSlaveDriver Implementation
#include "spiSlaveDriver.h"

typedef struct
{
    bool initialized;
    SpiSlaveDriver_Config_t config;
    const uint8_t *pTxBuffer;
    uint16_t txLength;
    uint8_t *pRxBuffer;
    uint16_t rxMaxLength;
    uint16_t rxLength;
    bool selected;
    SpiSlaveDriver_RxCallback_t rxCallback;
    SpiSlaveDriver_TxCallback_t txCallback;
} SpiSlaveDriver_Context_t;

static SpiSlaveDriver_Context_t context = {0};

SpiSlaveDriver_Status_t SpiSlaveDriver_Init(const SpiSlaveDriver_Config_t *pConfig)
{
    if (pConfig == NULL)
    {
        return SPI_SLAVE_STATUS_ERROR;
    }

    // TODO: Add vendor-specific HAL initialization here
    context.config = *pConfig;
    context.initialized = true;
    context.pTxBuffer = NULL;
    context.txLength = 0;
    context.pRxBuffer = NULL;
    context.rxMaxLength = 0;
    context.rxLength = 0;
    context.selected = false;
    context.rxCallback = NULL;
    context.txCallback = NULL;
    return SPI_SLAVE_STATUS_OK;
}

SpiSlaveDriver_Status_t SpiSlaveDriver_SetTxBuffer(const uint8_t *pData, uint16_t length)
{
    if (!context.initialized)
    {
        return SPI_SLAVE_STATUS_NOT_INITIALIZED;
    }
    if (pData == NULL || length == 0)
    {
        return SPI_SLAVE_STATUS_ERROR;
    }
    context.pTxBuffer = pData;
    context.txLength = length;
    return SPI_SLAVE_STATUS_OK;
}

SpiSlaveDriver_Status_t SpiSlaveDriver_SetRxBuffer(uint8_t *pData, uint16_t maxLength)
{
    if (!context.initialized)
    {
        return SPI_SLAVE_STATUS_NOT_INITIALIZED;
    }
    if (pData == NULL || maxLength == 0)
    {
        return SPI_SLAVE_STATUS_ERROR;
    }
    context.pRxBuffer = pData;
    context.rxMaxLength = maxLength;
    context.rxLength = 0;
    return SPI_SLAVE_STATUS_OK;
}

SpiSlaveDriver_Status_t SpiSlaveDriver_GetRxLength(uint16_t *pLength)
{
    if (pLength == NULL)
    {
        return SPI_SLAVE_STATUS_ERROR;
    }
    *pLength = context.rxLength;
    return SPI_SLAVE_STATUS_OK;
}

SpiSlaveDriver_Status_t SpiSlaveDriver_IsSelected(bool *pIsSelected)
{
    if (pIsSelected == NULL)
    {
        return SPI_SLAVE_STATUS_ERROR;
    }
    *pIsSelected = context.selected;
    return SPI_SLAVE_STATUS_OK;
}

SpiSlaveDriver_Status_t SpiSlaveDriver_RegisterRxCallback(SpiSlaveDriver_RxCallback_t callback)
{
    if (!context.initialized)
    {
        return SPI_SLAVE_STATUS_NOT_INITIALIZED;
    }
    context.rxCallback = callback;
    return SPI_SLAVE_STATUS_OK;
}

SpiSlaveDriver_Status_t SpiSlaveDriver_RegisterTxCallback(SpiSlaveDriver_TxCallback_t callback)
{
    if (!context.initialized)
    {
        return SPI_SLAVE_STATUS_NOT_INITIALIZED;
    }
    context.txCallback = callback;
    return SPI_SLAVE_STATUS_OK;
}

SpiSlaveDriver_Status_t SpiSlaveDriver_DeInit(void)
{
    // TODO: Add vendor-specific HAL deinitialization here
    context.initialized = false;
    return SPI_SLAVE_STATUS_OK;
}
