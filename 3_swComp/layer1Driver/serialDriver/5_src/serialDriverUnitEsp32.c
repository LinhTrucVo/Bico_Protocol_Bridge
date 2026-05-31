// ESP32 variant implementation for SerialDriver. (serialDriverUnitEsp32.c)
// This file provides the ESP32-specific implementation of the SerialDriver interface.
// Selected when L1_VARIANT is set to "Esp32" in the CMake build configuration.

//============================================================================
// Dependencies
//============================================================================
#include "serialDriver.h"
#include "serialDriverCfg.h"
#include "serialDriverUnit.h"
#include "driver/uart.h"
#include "driver/gpio.h"
#include <string.h>

//============================================================================
// Internal Defines
//============================================================================
#define SERIAL_ESP32_UART_NUM       UART_NUM_0
#define SERIAL_ESP32_RX_BUF_SIZE    (SERIAL_CFG_MAX_BUFFER_SIZE * 2)
#define SERIAL_ESP32_TX_BUF_SIZE    (SERIAL_CFG_MAX_BUFFER_SIZE * 2)

//============================================================================
// Internal Types
//============================================================================
typedef struct
{
    bool                        initialized;
    SerialDriver_Config_t       config;
    SerialDriver_RxCallback_t   rxCallback;
    SerialDriver_TxCallback_t   txCallback;
    SerialDriver_Status_t       lastStatus;
} SerialDriver_Context_t;

static SerialDriver_Context_t context = {0};

//============================================================================
// Internal Functions
//============================================================================
static uart_word_length_t MapDataBits(SerialDriver_DataBits_t bits)
{
    switch (bits)
    {
        case SERIAL_DATABITS_7: return UART_DATA_7_BITS;
        case SERIAL_DATABITS_9: return UART_DATA_8_BITS; /* ESP32 doesn't support 9-bit natively */
        default:                return UART_DATA_8_BITS;
    }
}

static uart_parity_t MapParity(SerialDriver_Parity_t parity)
{
    switch (parity)
    {
        case SERIAL_PARITY_EVEN: return UART_PARITY_EVEN;
        case SERIAL_PARITY_ODD:  return UART_PARITY_ODD;
        default:                 return UART_PARITY_DISABLE;
    }
}

static uart_stop_bits_t MapStopBits(SerialDriver_StopBits_t stop)
{
    return (stop == SERIAL_STOPBITS_2) ? UART_STOP_BITS_2 : UART_STOP_BITS_1;
}

//============================================================================
// Public Functions
//============================================================================
SerialDriver_Status_t SerialDriverUnit_Init(const SerialDriver_Config_t *pConfig)
{
    if (pConfig == NULL) { return SERIAL_STATUS_ERROR; }

    uart_config_t uartCfg = {
        .baud_rate  = (int)pConfig->baudrate,
        .data_bits  = MapDataBits(pConfig->dataBits),
        .parity     = MapParity(pConfig->parity),
        .stop_bits  = MapStopBits(pConfig->stopBits),
        .flow_ctrl  = UART_HW_FLOWCTRL_DISABLE,
        .source_clk = UART_SCLK_DEFAULT,
    };
    if (uart_param_config(SERIAL_ESP32_UART_NUM, &uartCfg) != ESP_OK) { return SERIAL_STATUS_ERROR; }
    if (uart_driver_install(SERIAL_ESP32_UART_NUM, SERIAL_ESP32_RX_BUF_SIZE,
                            SERIAL_ESP32_TX_BUF_SIZE, 0, NULL, 0) != ESP_OK)
    {
        return SERIAL_STATUS_ERROR;
    }
    (void)memcpy(&context.config, pConfig, sizeof(SerialDriver_Config_t));
    context.initialized = true;
    context.lastStatus  = SERIAL_STATUS_OK;
    return SERIAL_STATUS_OK;
}

SerialDriver_Status_t SerialDriverUnit_Configure(SerialDriver_Baudrate_t baudrate, SerialDriver_Parity_t parity,
                                                  SerialDriver_StopBits_t stopBits, SerialDriver_DataBits_t dataBits)
{
    if (!context.initialized) { return SERIAL_STATUS_ERROR; }

    uart_config_t uartCfg = {
        .baud_rate  = (int)baudrate,
        .data_bits  = MapDataBits(dataBits),
        .parity     = MapParity(parity),
        .stop_bits  = MapStopBits(stopBits),
        .flow_ctrl  = UART_HW_FLOWCTRL_DISABLE,
        .source_clk = UART_SCLK_DEFAULT,
    };
    if (uart_param_config(SERIAL_ESP32_UART_NUM, &uartCfg) != ESP_OK) { return SERIAL_STATUS_ERROR; }
    context.config.baudrate  = baudrate;
    context.config.parity    = parity;
    context.config.stopBits  = stopBits;
    context.config.dataBits  = dataBits;
    return SERIAL_STATUS_OK;
}

SerialDriver_Status_t SerialDriverUnit_Send(const uint8_t *pData, uint16_t length)
{
    if (!context.initialized) { return SERIAL_STATUS_ERROR; }
    if (pData == NULL || length == 0U) { return SERIAL_STATUS_ERROR; }

    int sent = uart_write_bytes(SERIAL_ESP32_UART_NUM, (const char *)pData, length);
    if (sent < 0) { return SERIAL_STATUS_ERROR; }
    if (context.txCallback != NULL) { context.txCallback(); }
    return SERIAL_STATUS_OK;
}

SerialDriver_Status_t SerialDriverUnit_SendWithTimeout(const uint8_t *pData, uint16_t length, uint32_t timeoutMs)
{
    if (!context.initialized) { return SERIAL_STATUS_ERROR; }
    if (pData == NULL || length == 0U) { return SERIAL_STATUS_ERROR; }

    int sent = uart_write_bytes(SERIAL_ESP32_UART_NUM, (const char *)pData, length);
    if (sent < 0) { return SERIAL_STATUS_ERROR; }
    if (uart_wait_tx_done(SERIAL_ESP32_UART_NUM, pdMS_TO_TICKS(timeoutMs)) != ESP_OK)
    {
        return SERIAL_STATUS_TIMEOUT;
    }
    if (context.txCallback != NULL) { context.txCallback(); }
    return SERIAL_STATUS_OK;
}

SerialDriver_Status_t SerialDriverUnit_Receive(uint8_t *pData, uint16_t maxLength, uint16_t *pReceivedLength)
{
    if (!context.initialized) { return SERIAL_STATUS_ERROR; }
    if (pData == NULL || pReceivedLength == NULL) { return SERIAL_STATUS_ERROR; }

    int received = uart_read_bytes(SERIAL_ESP32_UART_NUM, pData, maxLength, 0);
    *pReceivedLength = (received > 0) ? (uint16_t)received : 0U;
    if (received > 0 && context.rxCallback != NULL)
    {
        context.rxCallback(pData, *pReceivedLength);
    }
    return SERIAL_STATUS_OK;
}

SerialDriver_Status_t SerialDriverUnit_ReceiveWithTimeout(uint8_t *pData, uint16_t maxLength,
                                                           uint16_t *pReceivedLength, uint32_t timeoutMs)
{
    if (!context.initialized) { return SERIAL_STATUS_ERROR; }
    if (pData == NULL || pReceivedLength == NULL) { return SERIAL_STATUS_ERROR; }

    int received = uart_read_bytes(SERIAL_ESP32_UART_NUM, pData, maxLength, pdMS_TO_TICKS(timeoutMs));
    if (received < 0) { *pReceivedLength = 0U; return SERIAL_STATUS_TIMEOUT; }
    *pReceivedLength = (uint16_t)received;
    if (received > 0 && context.rxCallback != NULL)
    {
        context.rxCallback(pData, *pReceivedLength);
    }
    return SERIAL_STATUS_OK;
}

SerialDriver_Status_t SerialDriverUnit_GetAvailable(uint16_t *pAvailable)
{
    if (!context.initialized) { return SERIAL_STATUS_ERROR; }
    if (pAvailable == NULL) { return SERIAL_STATUS_ERROR; }

    size_t buffered = 0U;
    uart_get_buffered_data_len(SERIAL_ESP32_UART_NUM, &buffered);
    *pAvailable = (uint16_t)buffered;
    return SERIAL_STATUS_OK;
}

SerialDriver_Status_t SerialDriverUnit_FlushRx(void)
{
    if (!context.initialized) { return SERIAL_STATUS_ERROR; }
    uart_flush_input(SERIAL_ESP32_UART_NUM);
    return SERIAL_STATUS_OK;
}

SerialDriver_Status_t SerialDriverUnit_FlushTx(void)
{
    if (!context.initialized) { return SERIAL_STATUS_ERROR; }
    uart_wait_tx_done(SERIAL_ESP32_UART_NUM, pdMS_TO_TICKS(100));
    return SERIAL_STATUS_OK;
}

SerialDriver_Status_t SerialDriverUnit_RegisterRxCallback(SerialDriver_RxCallback_t callback)
{
    if (!context.initialized) { return SERIAL_STATUS_ERROR; }
    context.rxCallback = callback;
    return SERIAL_STATUS_OK;
}

SerialDriver_Status_t SerialDriverUnit_RegisterTxCallback(SerialDriver_TxCallback_t callback)
{
    if (!context.initialized) { return SERIAL_STATUS_ERROR; }
    context.txCallback = callback;
    return SERIAL_STATUS_OK;
}

SerialDriver_Status_t SerialDriverUnit_GetStatus(SerialDriver_Status_t *pStatus)
{
    if (pStatus == NULL) { return SERIAL_STATUS_ERROR; }
    *pStatus = context.lastStatus;
    return SERIAL_STATUS_OK;
}

SerialDriver_Status_t SerialDriverUnit_DeInit(void)
{
    if (!context.initialized) { return SERIAL_STATUS_ERROR; }
    uart_driver_delete(SERIAL_ESP32_UART_NUM);
    context.initialized = false;
    return SERIAL_STATUS_OK;
}
