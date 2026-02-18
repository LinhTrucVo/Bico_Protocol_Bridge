// Mock implementation for SerialDriver testing
// This file provides mock implementations for dependency injection

#include "mockSerialDriver.h"

// Include the .c file to get access to static variables and functions
#include "serialDriverUnit.c"

//============================================================================
// Mock function definitions
//============================================================================

// Required for FFF
DEFINE_FFF_GLOBALS;

//============================================================================
// Static function wrapper definitions
//============================================================================

SerialDriver_Status_t call_SerialDriverUnit_Init(const SerialDriver_Config_t *pConfig)
{
    return SerialDriverUnit_Init(pConfig);
}

SerialDriver_Status_t call_SerialDriverUnit_Configure(SerialDriver_Baudrate_t baudrate, SerialDriver_Parity_t parity, SerialDriver_StopBits_t stopBits, SerialDriver_DataBits_t dataBits)
{
    return SerialDriverUnit_Configure(baudrate, parity, stopBits, dataBits);
}

SerialDriver_Status_t call_SerialDriverUnit_Send(const uint8_t *pData, uint16_t length)
{
    return SerialDriverUnit_Send(pData, length);
}

SerialDriver_Status_t call_SerialDriverUnit_SendWithTimeout(const uint8_t *pData, uint16_t length, uint32_t timeoutMs)
{
    return SerialDriverUnit_SendWithTimeout(pData, length, timeoutMs);
}

SerialDriver_Status_t call_SerialDriverUnit_Receive(uint8_t *pData, uint16_t maxLength, uint16_t *pReceivedLength)
{
    return SerialDriverUnit_Receive(pData, maxLength, pReceivedLength);
}

SerialDriver_Status_t call_SerialDriverUnit_ReceiveWithTimeout(uint8_t *pData, uint16_t maxLength, uint16_t *pReceivedLength, uint32_t timeoutMs)
{
    return SerialDriverUnit_ReceiveWithTimeout(pData, maxLength, pReceivedLength, timeoutMs);
}

SerialDriver_Status_t call_SerialDriverUnit_GetAvailable(uint16_t *pAvailable)
{
    return SerialDriverUnit_GetAvailable(pAvailable);
}

SerialDriver_Status_t call_SerialDriverUnit_FlushRx(void)
{
    return SerialDriverUnit_FlushRx();
}

SerialDriver_Status_t call_SerialDriverUnit_FlushTx(void)
{
    return SerialDriverUnit_FlushTx();
}

SerialDriver_Status_t call_SerialDriverUnit_RegisterRxCallback(SerialDriver_RxCallback_t callback)
{
    return SerialDriverUnit_RegisterRxCallback(callback);
}

SerialDriver_Status_t call_SerialDriverUnit_RegisterTxCallback(SerialDriver_TxCallback_t callback)
{
    return SerialDriverUnit_RegisterTxCallback(callback);
}

SerialDriver_Status_t call_SerialDriverUnit_GetStatus(SerialDriver_Status_t *pStatus)
{
    return SerialDriverUnit_GetStatus(pStatus);
}

SerialDriver_Status_t call_SerialDriverUnit_DeInit(void)
{
    return SerialDriverUnit_DeInit();
}
