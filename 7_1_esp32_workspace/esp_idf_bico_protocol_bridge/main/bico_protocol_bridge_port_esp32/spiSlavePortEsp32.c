// ESP32 implementation of the SPI slave port (spiSlaveDriverPorting.h).

//============================================================================
// Dependencies
//============================================================================
#include <stddef.h>
#include <string.h>
#include "spiSlaveDriverPorting.h"
#include "spiSlavePortEsp32Cfg.h"
#include "driver/spi_slave.h"
#include "driver/gpio.h"
#include "esp_attr.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

//============================================================================
// Variables
//============================================================================
static bool slaveInitialized = false;
static volatile bool transferPending = false;
static TaskHandle_t transferTask = NULL;
static spi_slave_transaction_t transaction;
static DMA_ATTR uint8_t txBuffer[SPISLAVEPORT_MAX_TRANSFER_SIZE];
static DMA_ATTR uint8_t rxBuffer[SPISLAVEPORT_MAX_TRANSFER_SIZE];
static SpiSlavePort_SelectHandler_t selectHandler = NULL;
static SpiSlavePort_TransferHandler_t transferHandler = NULL;

//============================================================================
// Local Function Prototypes
//============================================================================
static void SpiSlavePort_OnSetup(spi_slave_transaction_t *pTransaction);
static void SpiSlavePort_OnTransferDone(spi_slave_transaction_t *pTransaction);
static void SpiSlavePort_TransferTask(void *pArg);

//============================================================================
// Public Function Implementations
//============================================================================
bool SpiSlavePort_Init(uint8_t mode, bool lsbFirst)
{
    if (slaveInitialized)
    {
        return true;
    }

    const spi_bus_config_t busCfg = {
        .mosi_io_num = BICO_PROTOCOL_BRIDGE_SPI_SLAVE_MOSI_PIN,
        .miso_io_num = BICO_PROTOCOL_BRIDGE_SPI_SLAVE_MISO_PIN,
        .sclk_io_num = BICO_PROTOCOL_BRIDGE_SPI_SLAVE_SCLK_PIN,
        .quadwp_io_num = -1,
        .quadhd_io_num = -1,
    };
    const spi_slave_interface_config_t slaveCfg = {
        .mode = mode,
        .spics_io_num = BICO_PROTOCOL_BRIDGE_SPI_SLAVE_CS_PIN,
        .queue_size = BICO_PROTOCOL_BRIDGE_SPI_SLAVE_QUEUE_SIZE,
        .flags = lsbFirst ? SPI_SLAVE_BIT_LSBFIRST : 0,
        .post_setup_cb = SpiSlavePort_OnSetup,
        .post_trans_cb = SpiSlavePort_OnTransferDone,
    };

    if (BICO_PROTOCOL_BRIDGE_SPI_SLAVE_INPUT_PULLUP)
    {
        (void)gpio_set_pull_mode(BICO_PROTOCOL_BRIDGE_SPI_SLAVE_MOSI_PIN, GPIO_PULLUP_ONLY);
        (void)gpio_set_pull_mode(BICO_PROTOCOL_BRIDGE_SPI_SLAVE_SCLK_PIN, GPIO_PULLUP_ONLY);
        (void)gpio_set_pull_mode(BICO_PROTOCOL_BRIDGE_SPI_SLAVE_CS_PIN, GPIO_PULLUP_ONLY);
    }
    (void)gpio_set_drive_capability(BICO_PROTOCOL_BRIDGE_SPI_SLAVE_MISO_PIN, BICO_PROTOCOL_BRIDGE_SPI_SLAVE_MISO_DRIVE_CAP);

    if (spi_slave_initialize(BICO_PROTOCOL_BRIDGE_SPI_SLAVE_HOST, &busCfg, &slaveCfg, BICO_PROTOCOL_BRIDGE_SPI_SLAVE_DMA_CHANNEL) != ESP_OK)
    {
        return false;
    }
    slaveInitialized = true;
    transferPending = false;

    if (xTaskCreate(SpiSlavePort_TransferTask, "spiSlaveXfer", BICO_PROTOCOL_BRIDGE_SPI_SLAVE_TASK_STACK_SIZE, NULL,
                    BICO_PROTOCOL_BRIDGE_SPI_SLAVE_TASK_PRIORITY, &transferTask) != pdPASS)
    {
        transferTask = NULL;
        SpiSlavePort_DeInit();
        return false;
    }
    return true;
}

void SpiSlavePort_DeInit(void)
{
    if (transferTask != NULL)
    {
        vTaskDelete(transferTask);
        transferTask = NULL;
    }
    if (slaveInitialized)
    {
        (void)spi_slave_free(BICO_PROTOCOL_BRIDGE_SPI_SLAVE_HOST);
        slaveInitialized = false;
    }
    transferPending = false;
    selectHandler = NULL;
    transferHandler = NULL;
}

bool SpiSlavePort_QueueTransfer(const uint8_t *pTxData, uint16_t txLength, uint16_t maxLength)
{
    if (!slaveInitialized || transferPending || (maxLength == 0U) || (maxLength > SPISLAVEPORT_MAX_TRANSFER_SIZE) || (txLength > maxLength))
    {
        return false;
    }

    (void)memset(txBuffer, 0, maxLength);
    if ((pTxData != NULL) && (txLength > 0U))
    {
        (void)memcpy(txBuffer, pTxData, txLength);
    }
    (void)memset(rxBuffer, 0, maxLength);

    (void)memset(&transaction, 0, sizeof(transaction));
    transaction.length = (size_t)maxLength * 8U;
    transaction.tx_buffer = txBuffer;
    transaction.rx_buffer = rxBuffer;

    transferPending = true;
    if (spi_slave_queue_trans(BICO_PROTOCOL_BRIDGE_SPI_SLAVE_HOST, &transaction, 0) != ESP_OK)
    {
        transferPending = false;
        return false;
    }
    return true;
}

void SpiSlavePort_SetSelectHandler(SpiSlavePort_SelectHandler_t handler)
{
    selectHandler = handler;
}

void SpiSlavePort_SetTransferHandler(SpiSlavePort_TransferHandler_t handler)
{
    transferHandler = handler;
}

//============================================================================
// Local Function Implementations
//============================================================================
static void IRAM_ATTR SpiSlavePort_OnSetup(spi_slave_transaction_t *pTransaction)
{
    (void)pTransaction;
    if (selectHandler != NULL)
    {
        selectHandler(true);
    }
}

static void IRAM_ATTR SpiSlavePort_OnTransferDone(spi_slave_transaction_t *pTransaction)
{
    (void)pTransaction;
    if (selectHandler != NULL)
    {
        selectHandler(false);
    }
}

static void SpiSlavePort_TransferTask(void *pArg)
{
    (void)pArg;

    for (;;)
    {
        spi_slave_transaction_t *pDone = NULL;
        if (spi_slave_get_trans_result(BICO_PROTOCOL_BRIDGE_SPI_SLAVE_HOST, &pDone, portMAX_DELAY) != ESP_OK)
        {
            continue;
        }

        transferPending = false;
        if (transferHandler != NULL)
        {
            transferHandler(rxBuffer, (uint16_t)(pDone->trans_len / 8U));
        }
    }
}
