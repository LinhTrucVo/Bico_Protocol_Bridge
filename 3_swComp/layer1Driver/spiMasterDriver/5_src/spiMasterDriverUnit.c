// SpiMasterDriver Implementation
#include "spiMasterDriver.h"

typedef struct
{
    bool initialized;
    bool busy;
    SpiMasterDriver_Config_t config;
    SpiMasterDriver_ChipSelect_t currentCs;
    SpiMasterDriver_Callback_t callback;
} SpiMasterDriver_Context_t;

static SpiMasterDriver_Context_t context = {0};

SpiMasterDriver_Status_t SpiMasterDriverUnit_Init(const SpiMasterDriver_Config_t *pConfig)
{
    if (pConfig == NULL)
    {
        return SPI_MASTER_STATUS_INVALID_PARAM;
    }

    // TODO: Add vendor-specific HAL initialization here
    context.config = *pConfig;
    context.initialized = true;
    context.busy = false;
    context.currentCs = 0;
    context.callback = NULL;
    return SPI_MASTER_STATUS_OK;
}

SpiMasterDriver_Status_t SpiMasterDriverUnit_Configure(uint32_t clockSpeed, SpiMasterDriver_Mode_t mode, SpiMasterDriver_BitOrder_t bitOrder)
{
    if (!context.initialized)
    {
        return SPI_MASTER_STATUS_NOT_INITIALIZED;
    }
    context.config.clockSpeed = clockSpeed;
    context.config.mode = mode;
    context.config.bitOrder = bitOrder;
    return SPI_MASTER_STATUS_OK;
}

SpiMasterDriver_Status_t SpiMasterDriverUnit_SelectChip(SpiMasterDriver_ChipSelect_t cs)
{
    if (!context.initialized)
    {
        return SPI_MASTER_STATUS_NOT_INITIALIZED;
    }
    context.currentCs = cs;
    return SPI_MASTER_STATUS_OK;
}

SpiMasterDriver_Status_t SpiMasterDriverUnit_DeselectChip(SpiMasterDriver_ChipSelect_t cs)
{
    if (!context.initialized)
    {
        return SPI_MASTER_STATUS_NOT_INITIALIZED;
    }
    (void)cs;
    return SPI_MASTER_STATUS_OK;
}

SpiMasterDriver_Status_t SpiMasterDriverUnit_Transmit(const uint8_t *pData, uint16_t length)
{
    if (!context.initialized)
    {
        return SPI_MASTER_STATUS_NOT_INITIALIZED;
    }
    if (pData == NULL || length == 0 || length > SPI_MAX_TRANSFER_SIZE)
    {
        return SPI_MASTER_STATUS_INVALID_PARAM;
    }
    // TODO: Add vendor-specific HAL transmit here
    if (context.callback != NULL)
    {
        context.callback(SPI_MASTER_STATUS_OK);
    }
    return SPI_MASTER_STATUS_OK;
}

SpiMasterDriver_Status_t SpiMasterDriverUnit_Receive(uint8_t *pData, uint16_t length)
{
    if (!context.initialized)
    {
        return SPI_MASTER_STATUS_NOT_INITIALIZED;
    }
    if (pData == NULL || length == 0 || length > SPI_MAX_TRANSFER_SIZE)
    {
        return SPI_MASTER_STATUS_INVALID_PARAM;
    }
    // TODO: Add vendor-specific HAL receive here
    return SPI_MASTER_STATUS_OK;
}

SpiMasterDriver_Status_t SpiMasterDriverUnit_TransmitReceive(const uint8_t *pTxData, uint8_t *pRxData, uint16_t length)
{
    if (!context.initialized)
    {
        return SPI_MASTER_STATUS_NOT_INITIALIZED;
    }
    if (length == 0 || length > SPI_MAX_TRANSFER_SIZE)
    {
        return SPI_MASTER_STATUS_INVALID_PARAM;
    }
    // TODO: Add vendor-specific HAL transfer here
    (void)pTxData;
    (void)pRxData;
    return SPI_MASTER_STATUS_OK;
}

SpiMasterDriver_Status_t SpiMasterDriverUnit_TransmitWithTimeout(const uint8_t *pData, uint16_t length, uint32_t timeoutMs)
{
    (void)timeoutMs;
    return SpiMasterDriverUnit_Transmit(pData, length);
}

SpiMasterDriver_Status_t SpiMasterDriverUnit_IsBusy(bool *pIsBusy)
{
    if (pIsBusy == NULL)
    {
        return SPI_MASTER_STATUS_INVALID_PARAM;
    }
    *pIsBusy = context.busy;
    return SPI_MASTER_STATUS_OK;
}

SpiMasterDriver_Status_t SpiMasterDriverUnit_RegisterCallback(SpiMasterDriver_Callback_t callback)
{
    if (!context.initialized)
    {
        return SPI_MASTER_STATUS_NOT_INITIALIZED;
    }
    context.callback = callback;
    return SPI_MASTER_STATUS_OK;
}

SpiMasterDriver_Status_t SpiMasterDriverUnit_DeInit(void)
{
    // TODO: Add vendor-specific HAL deinitialization here
    context.initialized = false;
    context.busy = false;
    context.callback = NULL;
    return SPI_MASTER_STATUS_OK;
}
