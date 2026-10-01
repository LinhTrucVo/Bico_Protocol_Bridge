// SpiMasterDriver Implementation
#include <stddef.h>
#include <string.h>
#include "spiMasterDriver.h"
#include "spiMasterDriverPorting.h"

typedef struct
{
    bool initialized;
    bool busy;
    SpiMasterDriver_Config_t config;
    SpiMasterDriver_ChipSelect_t currentCs;
    SpiMasterDriver_Callback_t callback;
} SpiMasterDriver_Context_t;

static SpiMasterDriver_Context_t context = {0};

static SpiMasterDriver_Status_t SpiMasterDriverUnit_Transfer(const uint8_t *pTxData, uint8_t *pRxData, uint16_t length);

SpiMasterDriver_Status_t SpiMasterDriverUnit_Init(const SpiMasterDriver_Config_t *pConfig)
{
    if (pConfig == NULL)
    {
        return SPI_MASTER_STATUS_INVALID_PARAM;
    }
    if (context.initialized)
    {
        SpiMasterPort_DeInit();
    }

    (void)memset(&context, 0, sizeof(context));
    if (!SpiMasterPort_Init(pConfig->clockSpeed, (uint8_t)pConfig->mode, pConfig->bitOrder == SPI_BITORDER_LSB_FIRST))
    {
        return SPI_MASTER_STATUS_ERROR;
    }

    context.config = *pConfig;
    context.initialized = true;
    return SPI_MASTER_STATUS_OK;
}

SpiMasterDriver_Status_t SpiMasterDriverUnit_Configure(uint32_t clockSpeed, SpiMasterDriver_Mode_t mode, SpiMasterDriver_BitOrder_t bitOrder)
{
    if (!context.initialized)
    {
        return SPI_MASTER_STATUS_NOT_INITIALIZED;
    }
    if (clockSpeed == 0U)
    {
        return SPI_MASTER_STATUS_INVALID_PARAM;
    }

    if (!SpiMasterPort_Configure(clockSpeed, (uint8_t)mode, bitOrder == SPI_BITORDER_LSB_FIRST))
    {
        return SPI_MASTER_STATUS_ERROR;
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
    if (!SpiMasterPort_AcquireBus())
    {
        return SPI_MASTER_STATUS_ERROR;
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
    SpiMasterPort_ReleaseBus();
    return SPI_MASTER_STATUS_OK;
}

SpiMasterDriver_Status_t SpiMasterDriverUnit_Transmit(const uint8_t *pData, uint16_t length)
{
    if (pData == NULL)
    {
        return context.initialized ? SPI_MASTER_STATUS_INVALID_PARAM : SPI_MASTER_STATUS_NOT_INITIALIZED;
    }
    return SpiMasterDriverUnit_Transfer(pData, NULL, length);
}

SpiMasterDriver_Status_t SpiMasterDriverUnit_Receive(uint8_t *pData, uint16_t length)
{
    if (pData == NULL)
    {
        return context.initialized ? SPI_MASTER_STATUS_INVALID_PARAM : SPI_MASTER_STATUS_NOT_INITIALIZED;
    }
    return SpiMasterDriverUnit_Transfer(NULL, pData, length);
}

SpiMasterDriver_Status_t SpiMasterDriverUnit_TransmitReceive(const uint8_t *pTxData, uint8_t *pRxData, uint16_t length)
{
    if (pTxData == NULL || pRxData == NULL)
    {
        return context.initialized ? SPI_MASTER_STATUS_INVALID_PARAM : SPI_MASTER_STATUS_NOT_INITIALIZED;
    }
    return SpiMasterDriverUnit_Transfer(pTxData, pRxData, length);
}

SpiMasterDriver_Status_t SpiMasterDriverUnit_TransmitWithTimeout(const uint8_t *pData, uint16_t length, uint32_t timeoutMs)
{
    (void)timeoutMs; // the transfer is blocking and ends when the hardware is done
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
    if (context.initialized)
    {
        SpiMasterPort_DeInit();
    }
    (void)memset(&context, 0, sizeof(context));
    return SPI_MASTER_STATUS_OK;
}

static SpiMasterDriver_Status_t SpiMasterDriverUnit_Transfer(const uint8_t *pTxData, uint8_t *pRxData, uint16_t length)
{
    if (!context.initialized)
    {
        return SPI_MASTER_STATUS_NOT_INITIALIZED;
    }
    if (length == 0 || length > SPI_MAX_TRANSFER_SIZE)
    {
        return SPI_MASTER_STATUS_INVALID_PARAM;
    }
    if (context.busy)
    {
        return SPI_MASTER_STATUS_BUSY;
    }

    context.busy = true;
    const bool done = SpiMasterPort_Transfer(pTxData, pRxData, length);
    context.busy = false;

    const SpiMasterDriver_Status_t status = done ? SPI_MASTER_STATUS_OK : SPI_MASTER_STATUS_ERROR;
    if (context.callback != NULL)
    {
        context.callback(status);
    }
    return status;
}
