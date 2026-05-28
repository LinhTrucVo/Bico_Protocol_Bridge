// SPIAPP Implementation - Typed SPI API

#include <stddef.h>
#include <string.h>
#include "SPIAPP.h"
#include "SPIAPPCfg.h"
#include "spiMasterDriver.h"

typedef struct
{
    bool initialized;
} SPIAPP_Context_t;

static SPIAPP_Context_t context = {0};

SPIAPP_Status_t SPIAPP_Init(void)
{
    SpiMasterDriver_Config_t spiCfg = {0};
    spiCfg.clockSpeed = SPI_MASTER_CFG_DEFAULT_SPEED;
    spiCfg.mode = SPI_MODE_0;
    spiCfg.bitOrder = SPI_BITORDER_MSB_FIRST;
    spiCfg.dataSize = SPI_DATASIZE_8BIT;
    spiCfg.csMode = SPI_CS_MODE_MANUAL;
    spiCfg.dmaEnabled = false;
    spiCfg.interruptEnabled = false;

    if (SpiMasterDriverUnit_Init(&spiCfg) != SPIMASTERDRIVERSTATUS_OK)
    {
        return SPI_APP_STATUS_ERROR;
    }

    context.initialized = true;
    return SPI_APP_STATUS_OK;
}

SPIAPP_Status_t SPIAPP_DeInit(void)
{
    if (context.initialized)
    {
        (void)SpiMasterDriverUnit_DeInit();
    }
    context.initialized = false;
    return SPI_APP_STATUS_OK;
}

SPIAPP_Status_t SPIAPP_Write(uint8_t device, const uint8_t *pData, uint16_t length)
{
    if (!context.initialized)
    {
        return SPI_APP_STATUS_NOT_INITIALIZED;
    }
    if (pData == NULL || length == 0U || length > SERIAL_TO_SPI_CFG_MAX_TRANSFER)
    {
        return SPI_APP_STATUS_INVALID_PARAM;
    }

    SpiMasterDriver_ChipSelect_t cs = (SpiMasterDriver_ChipSelect_t)device;

    if (SpiMasterDriverUnit_SelectChip(cs) != SPIMASTERDRIVERSTATUS_OK)
    {
        return SPI_APP_STATUS_BUS_ERROR;
    }

    SpiMasterDriver_Status_t drvStatus = SpiMasterDriverUnit_Transmit(pData, length);

    (void)SpiMasterDriverUnit_DeselectChip(cs);

    if (drvStatus != SPIMASTERDRIVERSTATUS_OK)
    {
        return SPI_APP_STATUS_BUS_ERROR;
    }

    return SPI_APP_STATUS_OK;
}

SPIAPP_Status_t SPIAPP_Transceive(uint8_t device, const uint8_t *pTxData, uint16_t txLength, uint8_t *pRxData, uint16_t rxLength)
{
    if (!context.initialized)
    {
        return SPI_APP_STATUS_NOT_INITIALIZED;
    }
    if (pTxData == NULL || txLength == 0U || pRxData == NULL || rxLength == 0U)
    {
        return SPI_APP_STATUS_INVALID_PARAM;
    }
    if ((txLength + rxLength) > SERIAL_TO_SPI_CFG_MAX_TRANSFER)
    {
        return SPI_APP_STATUS_INVALID_PARAM;
    }

    SpiMasterDriver_ChipSelect_t cs = (SpiMasterDriver_ChipSelect_t)device;

    if (SpiMasterDriverUnit_SelectChip(cs) != SPIMASTERDRIVERSTATUS_OK)
    {
        return SPI_APP_STATUS_BUS_ERROR;
    }

    /* Transmit command/address bytes first */
    SpiMasterDriver_Status_t drvStatus = SpiMasterDriverUnit_Transmit(pTxData, txLength);
    if (drvStatus != SPIMASTERDRIVERSTATUS_OK)
    {
        (void)SpiMasterDriverUnit_DeselectChip(cs);
        return SPI_APP_STATUS_BUS_ERROR;
    }

    /* Then receive response bytes */
    drvStatus = SpiMasterDriverUnit_Receive(pRxData, rxLength);

    (void)SpiMasterDriverUnit_DeselectChip(cs);

    if (drvStatus != SPIMASTERDRIVERSTATUS_OK)
    {
        return SPI_APP_STATUS_BUS_ERROR;
    }

    return SPI_APP_STATUS_OK;
}