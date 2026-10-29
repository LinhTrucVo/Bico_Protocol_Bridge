// This file defines the FFF for functions and MOCK functions for SpiMasterDriver testing

//============================================================================
// Dependencies
//============================================================================
#include "mockSpiMasterDriver.h"

// Include the .c file to get access to static variables and functions
#include "spiMasterDriverUnit.c"

//============================================================================
// Mock function definitions
//============================================================================

// Required for FFF
DEFINE_FFF_GLOBALS;

// DEFINE_FAKE_VALUE_FUNC(int, ExternalFunction, int);

//============================================================================
// Static function wrapper definitions
//============================================================================

SpiMasterDriver_Status_t call_SpiMasterDriverUnit_Init(const SpiMasterDriver_Config_t *pConfig)
{
    return SpiMasterDriverUnit_Init(pConfig);
}

SpiMasterDriver_Status_t call_SpiMasterDriverUnit_Configure(uint32_t clockSpeed, SpiMasterDriver_Mode_t mode, SpiMasterDriver_BitOrder_t bitOrder)
{
    return SpiMasterDriverUnit_Configure(clockSpeed, mode, bitOrder);
}

SpiMasterDriver_Status_t call_SpiMasterDriverUnit_SelectChip(SpiMasterDriver_ChipSelect_t cs)
{
    return SpiMasterDriverUnit_SelectChip(cs);
}

SpiMasterDriver_Status_t call_SpiMasterDriverUnit_DeselectChip(SpiMasterDriver_ChipSelect_t cs)
{
    return SpiMasterDriverUnit_DeselectChip(cs);
}

SpiMasterDriver_Status_t call_SpiMasterDriverUnit_Transmit(const uint8_t *pData, uint16_t length)
{
    return SpiMasterDriverUnit_Transmit(pData, length);
}

SpiMasterDriver_Status_t call_SpiMasterDriverUnit_Receive(uint8_t *pData, uint16_t length)
{
    return SpiMasterDriverUnit_Receive(pData, length);
}

SpiMasterDriver_Status_t call_SpiMasterDriverUnit_TransmitReceive(const uint8_t *pTxData, uint8_t *pRxData, uint16_t length)
{
    return SpiMasterDriverUnit_TransmitReceive(pTxData, pRxData, length);
}

SpiMasterDriver_Status_t call_SpiMasterDriverUnit_TransmitWithTimeout(const uint8_t *pData, uint16_t length, uint32_t timeoutMs)
{
    return SpiMasterDriverUnit_TransmitWithTimeout(pData, length, timeoutMs);
}

SpiMasterDriver_Status_t call_SpiMasterDriverUnit_IsBusy(bool *pIsBusy)
{
    return SpiMasterDriverUnit_IsBusy(pIsBusy);
}

SpiMasterDriver_Status_t call_SpiMasterDriverUnit_RegisterCallback(SpiMasterDriver_Callback_t callback)
{
    return SpiMasterDriverUnit_RegisterCallback(callback);
}

SpiMasterDriver_Status_t call_SpiMasterDriverUnit_DeInit(void)
{
    return SpiMasterDriverUnit_DeInit();
}
