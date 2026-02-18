// This file declares the FFF for functions and MOCK functions for SpiMasterDriver testing

#ifndef MOCKSPIMASTERDRIVER_H
#define MOCKSPIMASTERDRIVER_H

//============================================================================
// Dependencies
//============================================================================
#include "fff.h"

#include "spiMasterDriver.h"
#include "spiMasterDriverUnit.h"

//============================================================================
// Mock function declarations
//============================================================================
// Declare fake functions for external dependencies if any
// DECLARE_FAKE_VALUE_FUNC(int, ExternalFunction, int);

//============================================================================
// Static function wrapper declarations
//============================================================================

SpiMasterDriver_Status_t call_SpiMasterDriverUnit_Init(const SpiMasterDriver_Config_t *pConfig);
SpiMasterDriver_Status_t call_SpiMasterDriverUnit_Configure(uint32_t clockSpeed, SpiMasterDriver_Mode_t mode, SpiMasterDriver_BitOrder_t bitOrder);
SpiMasterDriver_Status_t call_SpiMasterDriverUnit_SelectChip(SpiMasterDriver_ChipSelect_t cs);
SpiMasterDriver_Status_t call_SpiMasterDriverUnit_DeselectChip(SpiMasterDriver_ChipSelect_t cs);
SpiMasterDriver_Status_t call_SpiMasterDriverUnit_Transmit(const uint8_t *pData, uint16_t length);
SpiMasterDriver_Status_t call_SpiMasterDriverUnit_Receive(uint8_t *pData, uint16_t length);
SpiMasterDriver_Status_t call_SpiMasterDriverUnit_TransmitReceive(const uint8_t *pTxData, uint8_t *pRxData, uint16_t length);
SpiMasterDriver_Status_t call_SpiMasterDriverUnit_TransmitWithTimeout(const uint8_t *pData, uint16_t length, uint32_t timeoutMs);
SpiMasterDriver_Status_t call_SpiMasterDriverUnit_IsBusy(bool *pIsBusy);
SpiMasterDriver_Status_t call_SpiMasterDriverUnit_RegisterCallback(SpiMasterDriver_Callback_t callback);
SpiMasterDriver_Status_t call_SpiMasterDriverUnit_DeInit(void);

#endif /* MOCKSPIMASTERDRIVER_H */
