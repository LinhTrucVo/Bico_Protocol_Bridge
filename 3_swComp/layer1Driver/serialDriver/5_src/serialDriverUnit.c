// This file is used to define the public interface of the component unit.
// It contains public macros, private variables, and function definitions.

//============================================================================
// Dependencies
//============================================================================
#include "serialDriver.h"
#include "serialDriverCfg.h"
#include "serialDriverUnit.h"

//============================================================================
// Local Macros
//============================================================================

//============================================================================
// Local Types
//============================================================================
typedef struct
{
    bool initialized;
    SerialDriver_Config_t config;
    SerialDriver_RxCallback_t rxCallback;
    SerialDriver_TxCallback_t txCallback;
} SerialDriver_Context_t;

//============================================================================
// Variables
//============================================================================
static SerialDriver_Context_t serialContext = {0};

//============================================================================
// Public Function Implementations
//============================================================================

SerialDriver_Status_t SerialDriverUnit_Init(const SerialDriver_Config_t *pConfig)
{
    if (pConfig == NULL)
    {
        return SERIAL_STATUS_ERROR;
    }

    // TODO: Add vendor-specific HAL UART initialization here
    serialContext.config = *pConfig;
    serialContext.initialized = true;
    serialContext.rxCallback = NULL;
    serialContext.txCallback = NULL;
    return SERIAL_STATUS_OK;
}

SerialDriver_Status_t SerialDriverUnit_Configure(SerialDriver_Baudrate_t baudrate, SerialDriver_Parity_t parity, SerialDriver_StopBits_t stopBits, SerialDriver_DataBits_t dataBits)
{
    if (!serialContext.initialized)
    {
        return SERIAL_STATUS_ERROR;
    }

    serialContext.config.baudrate = baudrate;
    serialContext.config.parity = parity;
    serialContext.config.stopBits = stopBits;
    serialContext.config.dataBits = dataBits;
    return SERIAL_STATUS_OK;
}

SerialDriver_Status_t SerialDriverUnit_Send(const uint8_t *pData, uint16_t length)
{
    if (!serialContext.initialized)
    {
        return SERIAL_STATUS_ERROR;
    }
    if (pData == NULL || length == 0 || length > SERIAL_MAX_BUFFER_SIZE)
    {
        return SERIAL_STATUS_ERROR;
    }

    // TODO: Add vendor-specific HAL UART transmit here
    if (serialContext.txCallback != NULL)
    {
        serialContext.txCallback();
    }
    return SERIAL_STATUS_OK;
}

SerialDriver_Status_t SerialDriverUnit_SendWithTimeout(const uint8_t *pData, uint16_t length, uint32_t timeoutMs)
{
    (void)timeoutMs;
    return SerialDriverUnit_Send(pData, length);
}

SerialDriver_Status_t SerialDriverUnit_Receive(uint8_t *pData, uint16_t maxLength, uint16_t *pReceivedLength)
{
    if (!serialContext.initialized)
    {
        return SERIAL_STATUS_ERROR;
    }
    if (pData == NULL || pReceivedLength == NULL || maxLength == 0)
    {
        return SERIAL_STATUS_ERROR;
    }

    // TODO: Add vendor-specific HAL UART receive here
    *pReceivedLength = 0;
    if (serialContext.rxCallback != NULL)
    {
        serialContext.rxCallback(pData, *pReceivedLength);
    }
    return SERIAL_STATUS_OK;
}

SerialDriver_Status_t SerialDriverUnit_ReceiveWithTimeout(uint8_t *pData, uint16_t maxLength, uint16_t *pReceivedLength, uint32_t timeoutMs)
{
    (void)timeoutMs;
    return SerialDriverUnit_Receive(pData, maxLength, pReceivedLength);
}

SerialDriver_Status_t SerialDriverUnit_GetAvailable(uint16_t *pAvailable)
{
    if (pAvailable == NULL)
    {
        return SERIAL_STATUS_ERROR;
    }

    *pAvailable = 0;
    return SERIAL_STATUS_OK;
}

SerialDriver_Status_t SerialDriverUnit_FlushRx(void)
{
    if (!serialContext.initialized)
    {
        return SERIAL_STATUS_ERROR;
    }
    return SERIAL_STATUS_OK;
}

SerialDriver_Status_t SerialDriverUnit_FlushTx(void)
{
    if (!serialContext.initialized)
    {
        return SERIAL_STATUS_ERROR;
    }
    return SERIAL_STATUS_OK;
}

SerialDriver_Status_t SerialDriverUnit_RegisterRxCallback(SerialDriver_RxCallback_t callback)
{
    if (!serialContext.initialized)
    {
        return SERIAL_STATUS_ERROR;
    }
    serialContext.rxCallback = callback;
    return SERIAL_STATUS_OK;
}

SerialDriver_Status_t SerialDriverUnit_RegisterTxCallback(SerialDriver_TxCallback_t callback)
{
    if (!serialContext.initialized)
    {
        return SERIAL_STATUS_ERROR;
    }
    serialContext.txCallback = callback;
    return SERIAL_STATUS_OK;
}

SerialDriver_Status_t SerialDriverUnit_GetStatus(SerialDriver_Status_t *pStatus)
{
    if (pStatus == NULL)
    {
        return SERIAL_STATUS_ERROR;
    }
    *pStatus = serialContext.initialized ? SERIAL_STATUS_OK : SERIAL_STATUS_ERROR;
    return SERIAL_STATUS_OK;
}

SerialDriver_Status_t SerialDriverUnit_DeInit(void)
{
    // TODO: Add vendor-specific HAL deinitialization here
    serialContext.initialized = false;
    return SERIAL_STATUS_OK;
}
