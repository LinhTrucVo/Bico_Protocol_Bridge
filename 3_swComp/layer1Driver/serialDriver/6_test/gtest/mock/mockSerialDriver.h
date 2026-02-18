// This file declares the FFF for functions and MOCK functions for SerialDriver testing

#ifndef MOCKSERIALDRIVER_H
#define MOCKSERIALDRIVER_H

//============================================================================
// Dependencies
//============================================================================
#include "fff.h"

#include "serialDriver.h"
#include "serialDriverUnit.h"

//============================================================================
// Mock function declarations
//============================================================================
// Declare fake functions for external dependencies if any
// DECLARE_FAKE_VALUE_FUNC(int, ExternalFunction, int);

//============================================================================
// Static function wrapper declarations
//============================================================================

SerialDriver_Status_t call_SerialDriverUnit_Init(const SerialDriver_Config_t *pConfig);
SerialDriver_Status_t call_SerialDriverUnit_Configure(SerialDriver_Baudrate_t baudrate, SerialDriver_Parity_t parity, SerialDriver_StopBits_t stopBits, SerialDriver_DataBits_t dataBits);
SerialDriver_Status_t call_SerialDriverUnit_Send(const uint8_t *pData, uint16_t length);
SerialDriver_Status_t call_SerialDriverUnit_SendWithTimeout(const uint8_t *pData, uint16_t length, uint32_t timeoutMs);
SerialDriver_Status_t call_SerialDriverUnit_Receive(uint8_t *pData, uint16_t maxLength, uint16_t *pReceivedLength);
SerialDriver_Status_t call_SerialDriverUnit_ReceiveWithTimeout(uint8_t *pData, uint16_t maxLength, uint16_t *pReceivedLength, uint32_t timeoutMs);
SerialDriver_Status_t call_SerialDriverUnit_GetAvailable(uint16_t *pAvailable);
SerialDriver_Status_t call_SerialDriverUnit_FlushRx(void);
SerialDriver_Status_t call_SerialDriverUnit_FlushTx(void);
SerialDriver_Status_t call_SerialDriverUnit_RegisterRxCallback(SerialDriver_RxCallback_t callback);
SerialDriver_Status_t call_SerialDriverUnit_RegisterTxCallback(SerialDriver_TxCallback_t callback);
SerialDriver_Status_t call_SerialDriverUnit_GetStatus(SerialDriver_Status_t *pStatus);
SerialDriver_Status_t call_SerialDriverUnit_DeInit(void);

#endif /* MOCKSERIALDRIVER_H */
