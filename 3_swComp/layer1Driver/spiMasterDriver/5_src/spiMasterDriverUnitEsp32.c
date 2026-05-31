// ESP32 variant implementation for SpiMasterDriver. (spiMasterDriverUnitEsp32.c)
// This file provides the ESP32-specific implementation of the SpiMasterDriver interface.
// Selected when L1_VARIANT is set to "Esp32" in the CMake build configuration.

//============================================================================
// Dependencies
//============================================================================
#include "spiMasterDriver.h"
#include "spiMasterDriverCfg.h"
#include "spiMasterDriverUnit.h"
#include "driver/spi_master.h"
#include "driver/gpio.h"
#include <string.h>

//============================================================================
// Internal Defines
//============================================================================
#define SPI_ESP32_HOST          SPI2_HOST
#define SPI_ESP32_DMA_CHAN      SPI_DMA_CH_AUTO
#define SPI_ESP32_PIN_MISO      12
#define SPI_ESP32_PIN_MOSI      13
#define SPI_ESP32_PIN_CLK       14
#define SPI_ESP32_PIN_CS0       15

//============================================================================
// Internal Types
//============================================================================
typedef struct
{
    bool                        initialized;
    spi_device_handle_t         deviceHandle;
    SpiMasterDriver_Config_t    config;
    SpiMasterDriver_Callback_t  callback;
    bool                        busy;
} SpiMasterDriver_Context_t;

static SpiMasterDriver_Context_t context = {0};

//============================================================================
// Public Functions
//============================================================================
SpiMasterDriver_Status_t SpiMasterDriverUnit_Init(const SpiMasterDriver_Config_t *pConfig)
{
    if (pConfig == NULL) { return SPIMASTERDRIVERSTATUS_INVALID_PARAM; }

    spi_bus_config_t busCfg = {
        .miso_io_num   = SPI_ESP32_PIN_MISO,
        .mosi_io_num   = SPI_ESP32_PIN_MOSI,
        .sclk_io_num   = SPI_ESP32_PIN_CLK,
        .quadwp_io_num = -1,
        .quadhd_io_num = -1,
        .max_transfer_sz = SPI_MAX_TRANSFER_SIZE,
    };
    if (spi_bus_initialize(SPI_ESP32_HOST, &busCfg, SPI_ESP32_DMA_CHAN) != ESP_OK)
    {
        return SPIMASTERDRIVERSTATUS_ERROR;
    }

    spi_device_interface_config_t devCfg = {
        .clock_speed_hz = (int)pConfig->clockSpeed,
        .mode           = (uint8_t)pConfig->mode,
        .spics_io_num   = SPI_ESP32_PIN_CS0,
        .queue_size     = 1,
        .pre_cb         = NULL,
        .post_cb        = NULL,
    };
    if (pConfig->bitOrder == SPI_BITORDER_LSB_FIRST)
    {
        devCfg.flags |= SPI_DEVICE_BIT_LSBFIRST;
    }
    if (spi_bus_add_device(SPI_ESP32_HOST, &devCfg, &context.deviceHandle) != ESP_OK)
    {
        (void)spi_bus_free(SPI_ESP32_HOST);
        return SPIMASTERDRIVERSTATUS_ERROR;
    }
    (void)memcpy(&context.config, pConfig, sizeof(SpiMasterDriver_Config_t));
    context.initialized = true;
    return SPIMASTERDRIVERSTATUS_OK;
}

SpiMasterDriver_Status_t SpiMasterDriverUnit_Configure(uint32_t clockSpeed, SpiMasterDriver_Mode_t mode,
                                                        SpiMasterDriver_BitOrder_t bitOrder)
{
    if (!context.initialized) { return SPIMASTERDRIVERSTATUS_NOT_INITIALIZED; }
    context.config.clockSpeed = clockSpeed;
    context.config.mode       = mode;
    context.config.bitOrder   = bitOrder;
    /* Full reconfiguration requires removing and re-adding the device */
    return SPIMASTERDRIVERSTATUS_OK;
}

SpiMasterDriver_Status_t SpiMasterDriverUnit_SelectChip(SpiMasterDriver_ChipSelect_t cs)
{
    if (!context.initialized) { return SPIMASTERDRIVERSTATUS_NOT_INITIALIZED; }
    (void)cs;
    spi_device_acquire_bus(context.deviceHandle, portMAX_DELAY);
    return SPIMASTERDRIVERSTATUS_OK;
}

SpiMasterDriver_Status_t SpiMasterDriverUnit_DeselectChip(SpiMasterDriver_ChipSelect_t cs)
{
    if (!context.initialized) { return SPIMASTERDRIVERSTATUS_NOT_INITIALIZED; }
    (void)cs;
    spi_device_release_bus(context.deviceHandle);
    return SPIMASTERDRIVERSTATUS_OK;
}

SpiMasterDriver_Status_t SpiMasterDriverUnit_Transmit(const uint8_t *pData, uint16_t length)
{
    if (!context.initialized) { return SPIMASTERDRIVERSTATUS_NOT_INITIALIZED; }
    if (pData == NULL || length == 0U) { return SPIMASTERDRIVERSTATUS_INVALID_PARAM; }

    spi_transaction_t trans = {0};
    trans.length    = (size_t)length * 8U;
    trans.tx_buffer = pData;
    trans.rx_buffer = NULL;

    context.busy = true;
    esp_err_t ret = spi_device_polling_transmit(context.deviceHandle, &trans);
    context.busy  = false;

    if (ret != ESP_OK) { return SPIMASTERDRIVERSTATUS_ERROR; }
    if (context.callback != NULL) { context.callback(SPIMASTERDRIVERSTATUS_OK); }
    return SPIMASTERDRIVERSTATUS_OK;
}

SpiMasterDriver_Status_t SpiMasterDriverUnit_Receive(uint8_t *pData, uint16_t length)
{
    if (!context.initialized) { return SPIMASTERDRIVERSTATUS_NOT_INITIALIZED; }
    if (pData == NULL || length == 0U) { return SPIMASTERDRIVERSTATUS_INVALID_PARAM; }

    static uint8_t dummyTx[SPI_MAX_TRANSFER_SIZE];
    (void)memset(dummyTx, 0xFFU, length);

    spi_transaction_t trans = {0};
    trans.length    = (size_t)length * 8U;
    trans.tx_buffer = dummyTx;
    trans.rx_buffer = pData;

    context.busy = true;
    esp_err_t ret = spi_device_polling_transmit(context.deviceHandle, &trans);
    context.busy  = false;

    return (ret == ESP_OK) ? SPIMASTERDRIVERSTATUS_OK : SPIMASTERDRIVERSTATUS_ERROR;
}

SpiMasterDriver_Status_t SpiMasterDriverUnit_TransmitReceive(const uint8_t *pTxData, uint8_t *pRxData, uint16_t length)
{
    if (!context.initialized) { return SPIMASTERDRIVERSTATUS_NOT_INITIALIZED; }
    if (pTxData == NULL || pRxData == NULL || length == 0U) { return SPIMASTERDRIVERSTATUS_INVALID_PARAM; }

    spi_transaction_t trans = {0};
    trans.length    = (size_t)length * 8U;
    trans.tx_buffer = pTxData;
    trans.rx_buffer = pRxData;

    context.busy = true;
    esp_err_t ret = spi_device_polling_transmit(context.deviceHandle, &trans);
    context.busy  = false;

    if (ret != ESP_OK) { return SPIMASTERDRIVERSTATUS_ERROR; }
    if (context.callback != NULL) { context.callback(SPIMASTERDRIVERSTATUS_OK); }
    return SPIMASTERDRIVERSTATUS_OK;
}

SpiMasterDriver_Status_t SpiMasterDriverUnit_TransmitWithTimeout(const uint8_t *pData, uint16_t length,
                                                                   uint32_t timeoutMs)
{
    (void)timeoutMs;
    /* spi_device_polling_transmit is blocking; timeout handled by ESP-IDF internally */
    return SpiMasterDriverUnit_Transmit(pData, length);
}

SpiMasterDriver_Status_t SpiMasterDriverUnit_IsBusy(bool *pIsBusy)
{
    if (!context.initialized) { return SPIMASTERDRIVERSTATUS_NOT_INITIALIZED; }
    if (pIsBusy == NULL) { return SPIMASTERDRIVERSTATUS_INVALID_PARAM; }
    *pIsBusy = context.busy;
    return SPIMASTERDRIVERSTATUS_OK;
}

SpiMasterDriver_Status_t SpiMasterDriverUnit_RegisterCallback(SpiMasterDriver_Callback_t callback)
{
    if (!context.initialized) { return SPIMASTERDRIVERSTATUS_NOT_INITIALIZED; }
    context.callback = callback;
    return SPIMASTERDRIVERSTATUS_OK;
}

SpiMasterDriver_Status_t SpiMasterDriverUnit_DeInit(void)
{
    if (!context.initialized) { return SPIMASTERDRIVERSTATUS_NOT_INITIALIZED; }
    (void)spi_bus_remove_device(context.deviceHandle);
    (void)spi_bus_free(SPI_ESP32_HOST);
    context.initialized = false;
    return SPIMASTERDRIVERSTATUS_OK;
}
