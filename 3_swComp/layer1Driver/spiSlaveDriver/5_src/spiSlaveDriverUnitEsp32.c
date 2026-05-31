// ESP32 variant implementation for SpiSlaveDriver. (spiSlaveDriverUnitEsp32.c)
// This file provides the ESP32-specific implementation of the SpiSlaveDriver interface.
// Selected when L1_VARIANT is set to "Esp32" in the CMake build configuration.

//============================================================================
// Dependencies
//============================================================================
#include "spiSlaveDriver.h"
#include "spiSlaveDriverCfg.h"
#include "spiSlaveDriverUnit.h"
#include "driver/spi_slave.h"
#include "driver/gpio.h"
#include <string.h>

//============================================================================
// Internal Defines
//============================================================================
#define SPI_SLAVE_ESP32_HOST        SPI2_HOST
#define SPI_SLAVE_ESP32_PIN_MISO    12
#define SPI_SLAVE_ESP32_PIN_MOSI    13
#define SPI_SLAVE_ESP32_PIN_CLK     14
#define SPI_SLAVE_ESP32_PIN_CS      15
#define SPI_SLAVE_ESP32_DMA_CHAN    SPI_DMA_CH_AUTO

//============================================================================
// Internal Types
//============================================================================
typedef struct
{
    bool                        initialized;
    bool                        selected;
    SpiSlaveDriver_Config_t     config;
    uint8_t                     rxBuffer[SPI_SLAVE_CFG_BUFFER_SIZE];
    uint16_t                    rxLength;
    uint8_t                     txBuffer[SPI_SLAVE_CFG_BUFFER_SIZE];
    uint16_t                    txLength;
    SpiSlaveDriver_RxCallback_t rxCallback;
    SpiSlaveDriver_TxCallback_t txCallback;
    spi_slave_transaction_t     transaction;
} SpiSlaveDriver_Context_t;

static SpiSlaveDriver_Context_t context = {0};

//============================================================================
// Internal Callbacks (ISR-safe)
//============================================================================
static void IRAM_ATTR PostSetupCb(spi_slave_transaction_t *pTrans)
{
    (void)pTrans;
    context.selected = true;
}

static void IRAM_ATTR PostTransCb(spi_slave_transaction_t *pTrans)
{
    context.rxLength = (uint16_t)(pTrans->trans_len / 8U);
    (void)memcpy(context.rxBuffer, pTrans->rx_buffer, context.rxLength);
    context.selected = false;
    if (context.rxCallback != NULL)
    {
        context.rxCallback(context.rxBuffer, context.rxLength);
    }
}

//============================================================================
// Public Functions
//============================================================================
SpiSlaveDriver_Status_t SpiSlaveDriverUnit_Init(const SpiSlaveDriver_Config_t *pConfig)
{
    if (pConfig == NULL) { return SPISLAVEDRIVERSTATUS_INVALID_PARAM; }

    spi_bus_config_t busCfg = {
        .miso_io_num   = SPI_SLAVE_ESP32_PIN_MISO,
        .mosi_io_num   = SPI_SLAVE_ESP32_PIN_MOSI,
        .sclk_io_num   = SPI_SLAVE_ESP32_PIN_CLK,
        .quadwp_io_num = -1,
        .quadhd_io_num = -1,
    };
    spi_slave_interface_config_t slaveCfg = {
        .mode          = (uint8_t)pConfig->mode,
        .spics_io_num  = SPI_SLAVE_ESP32_PIN_CS,
        .queue_size    = 1,
        .flags         = 0,
        .post_setup_cb = PostSetupCb,
        .post_trans_cb = PostTransCb,
    };
    if (spi_slave_initialize(SPI_SLAVE_ESP32_HOST, &busCfg, &slaveCfg,
                             SPI_SLAVE_ESP32_DMA_CHAN) != ESP_OK)
    {
        return SPISLAVEDRIVERSTATUS_ERROR;
    }
    (void)memcpy(&context.config, pConfig, sizeof(SpiSlaveDriver_Config_t));
    context.initialized = true;
    return SPISLAVEDRIVERSTATUS_OK;
}

SpiSlaveDriver_Status_t SpiSlaveDriverUnit_SetTxBuffer(const uint8_t *pData, uint16_t length)
{
    if (!context.initialized) { return SPISLAVEDRIVERSTATUS_NOT_INITIALIZED; }
    if (pData == NULL || length == 0U) { return SPISLAVEDRIVERSTATUS_INVALID_PARAM; }

    (void)memcpy(context.txBuffer, pData, length);
    context.txLength = length;

    (void)memset(&context.transaction, 0, sizeof(context.transaction));
    context.transaction.length    = (size_t)length * 8U;
    context.transaction.tx_buffer = context.txBuffer;
    context.transaction.rx_buffer = context.rxBuffer;

    if (spi_slave_queue_trans(SPI_SLAVE_ESP32_HOST, &context.transaction, 0) != ESP_OK)
    {
        return SPISLAVEDRIVERSTATUS_ERROR;
    }
    return SPISLAVEDRIVERSTATUS_OK;
}

SpiSlaveDriver_Status_t SpiSlaveDriverUnit_SetRxBuffer(uint8_t *pData, uint16_t maxLength)
{
    if (!context.initialized) { return SPISLAVEDRIVERSTATUS_NOT_INITIALIZED; }
    if (pData == NULL || maxLength == 0U) { return SPISLAVEDRIVERSTATUS_INVALID_PARAM; }
    /* Retrieve the last received data */
    uint16_t copyLen = (context.rxLength < maxLength) ? context.rxLength : maxLength;
    (void)memcpy(pData, context.rxBuffer, copyLen);
    return SPISLAVEDRIVERSTATUS_OK;
}

SpiSlaveDriver_Status_t SpiSlaveDriverUnit_GetRxLength(uint16_t *pLength)
{
    if (!context.initialized) { return SPISLAVEDRIVERSTATUS_NOT_INITIALIZED; }
    if (pLength == NULL) { return SPISLAVEDRIVERSTATUS_INVALID_PARAM; }
    *pLength = context.rxLength;
    return SPISLAVEDRIVERSTATUS_OK;
}

SpiSlaveDriver_Status_t SpiSlaveDriverUnit_IsSelected(bool *pIsSelected)
{
    if (!context.initialized) { return SPISLAVEDRIVERSTATUS_NOT_INITIALIZED; }
    if (pIsSelected == NULL) { return SPISLAVEDRIVERSTATUS_INVALID_PARAM; }
    *pIsSelected = context.selected;
    return SPISLAVEDRIVERSTATUS_OK;
}

SpiSlaveDriver_Status_t SpiSlaveDriverUnit_RegisterRxCallback(SpiSlaveDriver_RxCallback_t callback)
{
    if (!context.initialized) { return SPISLAVEDRIVERSTATUS_NOT_INITIALIZED; }
    context.rxCallback = callback;
    return SPISLAVEDRIVERSTATUS_OK;
}

SpiSlaveDriver_Status_t SpiSlaveDriverUnit_RegisterTxCallback(SpiSlaveDriver_TxCallback_t callback)
{
    if (!context.initialized) { return SPISLAVEDRIVERSTATUS_NOT_INITIALIZED; }
    context.txCallback = callback;
    return SPISLAVEDRIVERSTATUS_OK;
}

SpiSlaveDriver_Status_t SpiSlaveDriverUnit_DeInit(void)
{
    if (!context.initialized) { return SPISLAVEDRIVERSTATUS_NOT_INITIALIZED; }
    (void)spi_slave_free(SPI_SLAVE_ESP32_HOST);
    (void)memset(&context, 0, sizeof(context));
    return SPISLAVEDRIVERSTATUS_OK;
}
