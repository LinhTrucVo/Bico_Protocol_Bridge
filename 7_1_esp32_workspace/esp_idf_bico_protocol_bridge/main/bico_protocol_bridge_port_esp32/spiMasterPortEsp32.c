// ESP32 implementation of the SPI master port (spiMasterDriverPorting.h).

//============================================================================
// Dependencies
//============================================================================
#include <stddef.h>
#include "spiMasterDriverPorting.h"
#include "spiMasterPortEsp32Cfg.h"
#include "driver/spi_master.h"
#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"

//============================================================================
// Variables
//============================================================================
static bool busInitialized = false;
static spi_device_handle_t deviceHandle = NULL;

//============================================================================
// Local Function Prototypes
//============================================================================
static bool SpiMasterPort_AddDevice(uint32_t clockHz, uint8_t mode, bool lsbFirst);
static void SpiMasterPort_RemoveDevice(void);

//============================================================================
// Public Function Implementations
//============================================================================
bool SpiMasterPort_Init(uint32_t clockHz, uint8_t mode, bool lsbFirst)
{
    if (busInitialized)
    {
        return SpiMasterPort_Configure(clockHz, mode, lsbFirst);
    }

    const spi_bus_config_t busCfg = {
        .mosi_io_num = BICO_PROTOCOL_BRIDGE_SPI_MASTER_MOSI_PIN,
        .miso_io_num = BICO_PROTOCOL_BRIDGE_SPI_MASTER_MISO_PIN,
        .sclk_io_num = BICO_PROTOCOL_BRIDGE_SPI_MASTER_SCLK_PIN,
        .quadwp_io_num = -1,
        .quadhd_io_num = -1,
        .max_transfer_sz = BICO_PROTOCOL_BRIDGE_SPI_MASTER_MAX_TRANSFER_SIZE,
    };
    if (BICO_PROTOCOL_BRIDGE_SPI_MASTER_MISO_PULLUP)
    {
        (void)gpio_set_pull_mode(BICO_PROTOCOL_BRIDGE_SPI_MASTER_MISO_PIN, GPIO_PULLUP_ONLY);
    }
    if (spi_bus_initialize(BICO_PROTOCOL_BRIDGE_SPI_MASTER_HOST, &busCfg, BICO_PROTOCOL_BRIDGE_SPI_MASTER_DMA_CHANNEL) != ESP_OK)
    {
        return false;
    }
    busInitialized = true;

    if (!SpiMasterPort_AddDevice(clockHz, mode, lsbFirst))
    {
        SpiMasterPort_DeInit();
        return false;
    }
    return true;
}

void SpiMasterPort_DeInit(void)
{
    SpiMasterPort_RemoveDevice();
    if (busInitialized)
    {
        (void)spi_bus_free(BICO_PROTOCOL_BRIDGE_SPI_MASTER_HOST);
        busInitialized = false;
    }
}

bool SpiMasterPort_Configure(uint32_t clockHz, uint8_t mode, bool lsbFirst)
{
    if (!busInitialized)
    {
        return false;
    }

    // The device parameters are fixed when it is added, so the device is added again.
    SpiMasterPort_RemoveDevice();
    return SpiMasterPort_AddDevice(clockHz, mode, lsbFirst);
}

bool SpiMasterPort_Transfer(const uint8_t *pTxData, uint8_t *pRxData, uint16_t length)
{
    if ((deviceHandle == NULL) || (length == 0U))
    {
        return false;
    }

    spi_transaction_t transaction = {0};
    transaction.length = (size_t)length * 8U;
    transaction.tx_buffer = pTxData; // NULL sends zeros
    transaction.rx_buffer = pRxData;
    return (spi_device_transmit(deviceHandle, &transaction) == ESP_OK);
}

bool SpiMasterPort_AcquireBus(void)
{
    if (deviceHandle == NULL)
    {
        return false;
    }
    return (spi_device_acquire_bus(deviceHandle, portMAX_DELAY) == ESP_OK);
}

void SpiMasterPort_ReleaseBus(void)
{
    if (deviceHandle != NULL)
    {
        spi_device_release_bus(deviceHandle);
    }
}

//============================================================================
// Local Function Implementations
//============================================================================
static bool SpiMasterPort_AddDevice(uint32_t clockHz, uint8_t mode, bool lsbFirst)
{
    spi_device_interface_config_t devCfg = {
        .clock_speed_hz = (int)clockHz,
        .duty_cycle_pos = BICO_PROTOCOL_BRIDGE_SPI_MASTER_DUTY_CYCLE_POS,
        .mode = mode,
        .spics_io_num = BICO_PROTOCOL_BRIDGE_SPI_MASTER_CS_PIN,
        .cs_ena_posttrans = BICO_PROTOCOL_BRIDGE_SPI_MASTER_CS_POST_TRANS_CYCLES,
        .queue_size = BICO_PROTOCOL_BRIDGE_SPI_MASTER_QUEUE_SIZE,
    };
    if (lsbFirst)
    {
        devCfg.flags |= SPI_DEVICE_BIT_LSBFIRST;
    }

    if (spi_bus_add_device(BICO_PROTOCOL_BRIDGE_SPI_MASTER_HOST, &devCfg, &deviceHandle) != ESP_OK)
    {
        deviceHandle = NULL;
        return false;
    }
    return true;
}

static void SpiMasterPort_RemoveDevice(void)
{
    if (deviceHandle != NULL)
    {
        (void)spi_bus_remove_device(deviceHandle);
        deviceHandle = NULL;
    }
}
