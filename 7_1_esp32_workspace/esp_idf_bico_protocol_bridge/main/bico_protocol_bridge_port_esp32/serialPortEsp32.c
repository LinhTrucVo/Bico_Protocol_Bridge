// ESP32 implementation of the serial port (serialDriverPorting.h).

//============================================================================
// Dependencies
//============================================================================
#include <stddef.h>
#include "serialDriverPorting.h"
#include "serialPortEsp32Cfg.h"
#include "driver/uart.h"
#include "freertos/FreeRTOS.h"

//============================================================================
// Variables
//============================================================================
static bool uartInstalled = false;

//============================================================================
// Local Function Prototypes
//============================================================================
static bool SerialPort_ApplyParameters(uint32_t baudrate, SerialPort_Parity_t parity, SerialPort_StopBits_t stopBits, uint8_t dataBits);

//============================================================================
// Public Function Implementations
//============================================================================
bool SerialPort_Init(uint32_t baudrate, SerialPort_Parity_t parity, SerialPort_StopBits_t stopBits, uint8_t dataBits)
{
    if (uartInstalled)
    {
        return SerialPort_ApplyParameters(baudrate, parity, stopBits, dataBits);
    }

    if (uart_driver_install(BICO_PROTOCOL_BRIDGE_SERIAL_UART_NUM, BICO_PROTOCOL_BRIDGE_SERIAL_RX_BUFFER_SIZE,
                            BICO_PROTOCOL_BRIDGE_SERIAL_TX_BUFFER_SIZE, 0, NULL, 0) != ESP_OK)
    {
        return false;
    }
    uartInstalled = true;

    if (!SerialPort_ApplyParameters(baudrate, parity, stopBits, dataBits) ||
        (uart_set_pin(BICO_PROTOCOL_BRIDGE_SERIAL_UART_NUM, BICO_PROTOCOL_BRIDGE_SERIAL_TX_PIN,
                      BICO_PROTOCOL_BRIDGE_SERIAL_RX_PIN, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE) != ESP_OK))
    {
        SerialPort_DeInit();
        return false;
    }
    return true;
}

void SerialPort_DeInit(void)
{
    if (uartInstalled)
    {
        (void)uart_driver_delete(BICO_PROTOCOL_BRIDGE_SERIAL_UART_NUM);
        uartInstalled = false;
    }
}

bool SerialPort_Configure(uint32_t baudrate, SerialPort_Parity_t parity, SerialPort_StopBits_t stopBits, uint8_t dataBits)
{
    if (!uartInstalled)
    {
        return false;
    }
    return SerialPort_ApplyParameters(baudrate, parity, stopBits, dataBits);
}

bool SerialPort_Write(const uint8_t *pData, uint16_t length)
{
    if (!uartInstalled || (pData == NULL))
    {
        return false;
    }
    return (uart_write_bytes(BICO_PROTOCOL_BRIDGE_SERIAL_UART_NUM, (const char *)pData, length) >= 0);
}

bool SerialPort_WaitTxDone(uint32_t timeoutMs)
{
    if (!uartInstalled)
    {
        return false;
    }
    return (uart_wait_tx_done(BICO_PROTOCOL_BRIDGE_SERIAL_UART_NUM, pdMS_TO_TICKS(timeoutMs)) == ESP_OK);
}

bool SerialPort_Read(uint8_t *pData, uint16_t maxLength, uint16_t *pReadLength, uint32_t timeoutMs)
{
    if (!uartInstalled || (pData == NULL) || (pReadLength == NULL))
    {
        return false;
    }

    const int received = uart_read_bytes(BICO_PROTOCOL_BRIDGE_SERIAL_UART_NUM, pData, maxLength, pdMS_TO_TICKS(timeoutMs));
    if (received < 0)
    {
        return false;
    }
    *pReadLength = (uint16_t)received;
    return true;
}

bool SerialPort_GetAvailable(uint16_t *pAvailable)
{
    if (!uartInstalled || (pAvailable == NULL))
    {
        return false;
    }

    size_t buffered = 0U;
    if (uart_get_buffered_data_len(BICO_PROTOCOL_BRIDGE_SERIAL_UART_NUM, &buffered) != ESP_OK)
    {
        return false;
    }
    *pAvailable = (uint16_t)buffered;
    return true;
}

void SerialPort_FlushRx(void)
{
    if (uartInstalled)
    {
        (void)uart_flush_input(BICO_PROTOCOL_BRIDGE_SERIAL_UART_NUM);
    }
}

//============================================================================
// Local Function Implementations
//============================================================================
static bool SerialPort_ApplyParameters(uint32_t baudrate, SerialPort_Parity_t parity, SerialPort_StopBits_t stopBits, uint8_t dataBits)
{
    uart_word_length_t espDataBits = UART_DATA_8_BITS; // 9 data bits are not supported by the UART
    if (dataBits == 7U)
    {
        espDataBits = UART_DATA_7_BITS;
    }

    uart_parity_t espParity = UART_PARITY_DISABLE;
    if (parity == SERIALPORT_PARITY_EVEN)
    {
        espParity = UART_PARITY_EVEN;
    }
    else if (parity == SERIALPORT_PARITY_ODD)
    {
        espParity = UART_PARITY_ODD;
    }

    const uart_config_t uartCfg = {
        .baud_rate = (int)baudrate,
        .data_bits = espDataBits,
        .parity = espParity,
        .stop_bits = (stopBits == SERIALPORT_STOPBITS_2) ? UART_STOP_BITS_2 : UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
        .source_clk = UART_SCLK_DEFAULT,
    };
    return (uart_param_config(BICO_PROTOCOL_BRIDGE_SERIAL_UART_NUM, &uartCfg) == ESP_OK);
}
