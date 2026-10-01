// SpiSlaveDriver Implementation
#include <stddef.h>
#include <string.h>
#include "spiSlaveDriver.h"
#include "spiSlaveDriverPorting.h"

typedef struct
{
    bool initialized;
    bool armed;
    SpiSlaveDriver_Config_t config;
    const uint8_t *pTxBuffer;
    uint16_t txLength;
    uint8_t *pRxBuffer;
    uint16_t rxMaxLength;
    uint16_t rxLength;
    bool selected;
    SpiSlaveDriver_RxCallback_t rxCallback;
    SpiSlaveDriver_TxCallback_t txCallback;
    uint8_t txScratch[SPI_SLAVE_MAX_BUFFER];
} SpiSlaveDriver_Context_t;

static SpiSlaveDriver_Context_t context = {0};

static void SpiSlaveDriverUnit_Arm(void);
static void SpiSlaveDriverUnit_OnPortSelect(bool selected);
static void SpiSlaveDriverUnit_OnPortTransfer(const uint8_t *pRxData, uint16_t length);

SpiSlaveDriver_Status_t SpiSlaveDriverUnit_Init(const SpiSlaveDriver_Config_t *pConfig)
{
    if (pConfig == NULL)
    {
        return SPI_SLAVE_STATUS_ERROR;
    }
    if (context.initialized)
    {
        SpiSlavePort_DeInit();
    }

    (void)memset(&context, 0, sizeof(context));
    if (!SpiSlavePort_Init((uint8_t)pConfig->mode, pConfig->bitOrder == SPI_SLAVE_BITORDER_LSB_FIRST))
    {
        return SPI_SLAVE_STATUS_ERROR;
    }
    SpiSlavePort_SetSelectHandler(SpiSlaveDriverUnit_OnPortSelect);
    SpiSlavePort_SetTransferHandler(SpiSlaveDriverUnit_OnPortTransfer);

    context.config = *pConfig;
    context.initialized = true;
    return SPI_SLAVE_STATUS_OK;
}

SpiSlaveDriver_Status_t SpiSlaveDriverUnit_SetTxBuffer(const uint8_t *pData, uint16_t length)
{
    if (!context.initialized)
    {
        return SPI_SLAVE_STATUS_NOT_INITIALIZED;
    }
    if (pData == NULL || length == 0 || length > SPI_SLAVE_MAX_BUFFER)
    {
        return SPI_SLAVE_STATUS_ERROR;
    }
    context.pTxBuffer = pData;
    context.txLength = length;
    SpiSlaveDriverUnit_Arm();
    return SPI_SLAVE_STATUS_OK;
}

SpiSlaveDriver_Status_t SpiSlaveDriverUnit_SetRxBuffer(uint8_t *pData, uint16_t maxLength)
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
    SpiSlaveDriverUnit_Arm();
    return SPI_SLAVE_STATUS_OK;
}

SpiSlaveDriver_Status_t SpiSlaveDriverUnit_GetRxLength(uint16_t *pLength)
{
    if (pLength == NULL)
    {
        return SPI_SLAVE_STATUS_ERROR;
    }
    *pLength = context.rxLength;
    return SPI_SLAVE_STATUS_OK;
}

SpiSlaveDriver_Status_t SpiSlaveDriverUnit_IsSelected(bool *pIsSelected)
{
    if (pIsSelected == NULL)
    {
        return SPI_SLAVE_STATUS_ERROR;
    }
    *pIsSelected = context.selected;
    return SPI_SLAVE_STATUS_OK;
}

SpiSlaveDriver_Status_t SpiSlaveDriverUnit_RegisterRxCallback(SpiSlaveDriver_RxCallback_t callback)
{
    if (!context.initialized)
    {
        return SPI_SLAVE_STATUS_NOT_INITIALIZED;
    }
    context.rxCallback = callback;
    return SPI_SLAVE_STATUS_OK;
}

SpiSlaveDriver_Status_t SpiSlaveDriverUnit_RegisterTxCallback(SpiSlaveDriver_TxCallback_t callback)
{
    if (!context.initialized)
    {
        return SPI_SLAVE_STATUS_NOT_INITIALIZED;
    }
    context.txCallback = callback;
    SpiSlaveDriverUnit_Arm();
    return SPI_SLAVE_STATUS_OK;
}

SpiSlaveDriver_Status_t SpiSlaveDriverUnit_DeInit(void)
{
    if (context.initialized)
    {
        SpiSlavePort_DeInit();
    }
    (void)memset(&context, 0, sizeof(context));
    return SPI_SLAVE_STATUS_OK;
}

// Queues the next transfer. The data of an already queued transfer is not changed, new data is used for the next one.
static void SpiSlaveDriverUnit_Arm(void)
{
    if (!context.initialized || context.armed)
    {
        return;
    }

    const uint8_t *pTxData = context.pTxBuffer;
    uint16_t txLength = context.txLength;
    if (context.txCallback != NULL)
    {
        txLength = SPI_SLAVE_MAX_BUFFER;
        context.txCallback(context.txScratch, &txLength);
        pTxData = context.txScratch;
        if (txLength > SPI_SLAVE_MAX_BUFFER)
        {
            txLength = SPI_SLAVE_MAX_BUFFER;
        }
    }

    uint16_t maxLength = (txLength > context.rxMaxLength) ? txLength : context.rxMaxLength;
    if (maxLength == 0U)
    {
        maxLength = SPI_SLAVE_MAX_BUFFER;
    }
    if (pTxData == NULL)
    {
        txLength = 0U;
    }

    context.armed = SpiSlavePort_QueueTransfer(pTxData, txLength, maxLength);
}

static void SpiSlaveDriverUnit_OnPortSelect(bool selected)
{
    context.selected = selected;
}

static void SpiSlaveDriverUnit_OnPortTransfer(const uint8_t *pRxData, uint16_t length)
{
    const uint8_t *pReported = pRxData;
    uint16_t reportedLength = length;

    if (context.pRxBuffer != NULL)
    {
        reportedLength = (length < context.rxMaxLength) ? length : context.rxMaxLength;
        (void)memcpy(context.pRxBuffer, pRxData, reportedLength);
        pReported = context.pRxBuffer;
    }
    context.rxLength = reportedLength;
    context.armed = false;

    if (context.rxCallback != NULL)
    {
        context.rxCallback(pReported, reportedLength);
    }
    SpiSlaveDriverUnit_Arm();
}
