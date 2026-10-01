// This file is used to define the public interface of the component unit.
// It contains public macros, private variables, and function definitions.

//============================================================================
// Dependencies
//============================================================================
#include <stddef.h>
#include <string.h>
#include "serialDriver.h"
#include "serialDriverCfg.h"
#include "serialDriverPorting.h"

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
// Local Function Prototypes
//============================================================================
static SerialPort_Parity_t SerialDriverUnit_ToPortParity(SerialDriver_Parity_t parity);
static SerialPort_StopBits_t SerialDriverUnit_ToPortStopBits(SerialDriver_StopBits_t stopBits);

//============================================================================
// Public Function Implementations
//============================================================================

SerialDriver_Status_t SerialDriverUnit_Init(const SerialDriver_Config_t *pConfig)
{
    if (pConfig == NULL)
    {
        return SERIAL_STATUS_ERROR;
    }
    if (serialContext.initialized)
    {
        SerialPort_DeInit();
    }

    (void)memset(&serialContext, 0, sizeof(serialContext));
    if (!SerialPort_Init((uint32_t)pConfig->baudrate, SerialDriverUnit_ToPortParity(pConfig->parity),
                         SerialDriverUnit_ToPortStopBits(pConfig->stopBits), (uint8_t)pConfig->dataBits))
    {
        return SERIAL_STATUS_ERROR;
    }

    serialContext.config = *pConfig;
    serialContext.initialized = true;
    return SERIAL_STATUS_OK;
}

SerialDriver_Status_t SerialDriverUnit_Configure(SerialDriver_Baudrate_t baudrate, SerialDriver_Parity_t parity, SerialDriver_StopBits_t stopBits, SerialDriver_DataBits_t dataBits)
{
    if (!serialContext.initialized)
    {
        return SERIAL_STATUS_ERROR;
    }

    if (!SerialPort_Configure((uint32_t)baudrate, SerialDriverUnit_ToPortParity(parity),
                              SerialDriverUnit_ToPortStopBits(stopBits), (uint8_t)dataBits))
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

    if (!SerialPort_Write(pData, length))
    {
        return SERIAL_STATUS_ERROR;
    }
    if (serialContext.txCallback != NULL)
    {
        serialContext.txCallback();
    }
    return SERIAL_STATUS_OK;
}

SerialDriver_Status_t SerialDriverUnit_SendWithTimeout(const uint8_t *pData, uint16_t length, uint32_t timeoutMs)
{
    if (!serialContext.initialized)
    {
        return SERIAL_STATUS_ERROR;
    }
    if (pData == NULL || length == 0 || length > SERIAL_MAX_BUFFER_SIZE)
    {
        return SERIAL_STATUS_ERROR;
    }

    if (!SerialPort_Write(pData, length))
    {
        return SERIAL_STATUS_ERROR;
    }
    if (!SerialPort_WaitTxDone(timeoutMs))
    {
        return SERIAL_STATUS_TIMEOUT;
    }
    if (serialContext.txCallback != NULL)
    {
        serialContext.txCallback();
    }
    return SERIAL_STATUS_OK;
}

SerialDriver_Status_t SerialDriverUnit_Receive(uint8_t *pData, uint16_t maxLength, uint16_t *pReceivedLength)
{
    return SerialDriverUnit_ReceiveWithTimeout(pData, maxLength, pReceivedLength, 0U);
}

SerialDriver_Status_t SerialDriverUnit_ReceiveWithTimeout(uint8_t *pData, uint16_t maxLength, uint16_t *pReceivedLength, uint32_t timeoutMs)
{
    if (!serialContext.initialized)
    {
        return SERIAL_STATUS_ERROR;
    }
    if (pData == NULL || pReceivedLength == NULL || maxLength == 0)
    {
        return SERIAL_STATUS_ERROR;
    }

    *pReceivedLength = 0U;
    if (!SerialPort_Read(pData, maxLength, pReceivedLength, timeoutMs))
    {
        *pReceivedLength = 0U;
        return SERIAL_STATUS_ERROR;
    }
    if (*pReceivedLength > 0U && serialContext.rxCallback != NULL)
    {
        serialContext.rxCallback(pData, *pReceivedLength);
    }
    return SERIAL_STATUS_OK;
}

SerialDriver_Status_t SerialDriverUnit_GetAvailable(uint16_t *pAvailable)
{
    if (!serialContext.initialized || pAvailable == NULL)
    {
        return SERIAL_STATUS_ERROR;
    }

    if (!SerialPort_GetAvailable(pAvailable))
    {
        return SERIAL_STATUS_ERROR;
    }
    return SERIAL_STATUS_OK;
}

SerialDriver_Status_t SerialDriverUnit_FlushRx(void)
{
    if (!serialContext.initialized)
    {
        return SERIAL_STATUS_ERROR;
    }

    SerialPort_FlushRx();
    return SERIAL_STATUS_OK;
}

SerialDriver_Status_t SerialDriverUnit_FlushTx(void)
{
    if (!serialContext.initialized)
    {
        return SERIAL_STATUS_ERROR;
    }

    (void)SerialPort_WaitTxDone(SERIAL_CFG_TIMEOUT_MS);
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
    if (serialContext.initialized)
    {
        SerialPort_DeInit();
    }
    (void)memset(&serialContext, 0, sizeof(serialContext));
    return SERIAL_STATUS_OK;
}

//============================================================================
// Local Function Implementations
//============================================================================

static SerialPort_Parity_t SerialDriverUnit_ToPortParity(SerialDriver_Parity_t parity)
{
    if (parity == SERIAL_PARITY_EVEN)
    {
        return SERIALPORT_PARITY_EVEN;
    }
    if (parity == SERIAL_PARITY_ODD)
    {
        return SERIALPORT_PARITY_ODD;
    }
    return SERIALPORT_PARITY_NONE;
}

static SerialPort_StopBits_t SerialDriverUnit_ToPortStopBits(SerialDriver_StopBits_t stopBits)
{
    return (stopBits == SERIAL_STOPBITS_2) ? SERIALPORT_STOPBITS_2 : SERIALPORT_STOPBITS_1;
}
