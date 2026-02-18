// This file declares the FFF for functions and MOCK functions for SpiSlaveDriver testing

#ifndef MOCKSPISLAVEDRIVER_H
#define MOCKSPISLAVEDRIVER_H

//============================================================================
// Dependencies
//============================================================================
#include "fff.h"

#include "spiSlaveDriver.h"
#include "spiSlaveDriverUnit.h"

//============================================================================
// Mock function declarations
//============================================================================
// Declare fake functions for external dependencies if any
// DECLARE_FAKE_VALUE_FUNC(int, ExternalFunction, int);

//============================================================================
// Static function wrapper declarations
//============================================================================

SpiSlaveDriver_Status_t call_SpiSlaveDriverUnit_Init(const SpiSlaveDriver_Config_t *pConfig);
SpiSlaveDriver_Status_t call_SpiSlaveDriverUnit_SetTxBuffer(const uint8_t *pData, uint16_t length);
SpiSlaveDriver_Status_t call_SpiSlaveDriverUnit_SetRxBuffer(uint8_t *pData, uint16_t maxLength);
SpiSlaveDriver_Status_t call_SpiSlaveDriverUnit_GetRxLength(uint16_t *pLength);
SpiSlaveDriver_Status_t call_SpiSlaveDriverUnit_IsSelected(bool *pIsSelected);
SpiSlaveDriver_Status_t call_SpiSlaveDriverUnit_RegisterRxCallback(SpiSlaveDriver_RxCallback_t callback);
SpiSlaveDriver_Status_t call_SpiSlaveDriverUnit_RegisterTxCallback(SpiSlaveDriver_TxCallback_t callback);
SpiSlaveDriver_Status_t call_SpiSlaveDriverUnit_DeInit(void);

#endif /* MOCKSPISLAVEDRIVER_H */
