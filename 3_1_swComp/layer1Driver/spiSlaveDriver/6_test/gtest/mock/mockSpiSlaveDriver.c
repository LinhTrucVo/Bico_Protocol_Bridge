// This file defines the FFF for functions and MOCK functions for SpiSlaveDriver testing

//============================================================================
// Dependencies
//============================================================================
#include "mockSpiSlaveDriver.h"

// Include the .c file to get access to static variables and functions
#include "spiSlaveDriverUnit.c"

//============================================================================
// Mock function definitions
//============================================================================

// Required for FFF
DEFINE_FFF_GLOBALS;

// DEFINE_FAKE_VALUE_FUNC(int, ExternalFunction, int);

//============================================================================
// Static function wrapper definitions
//============================================================================

SpiSlaveDriver_Status_t call_SpiSlaveDriverUnit_Init(const SpiSlaveDriver_Config_t *pConfig)
{
    return SpiSlaveDriverUnit_Init(pConfig);
}

SpiSlaveDriver_Status_t call_SpiSlaveDriverUnit_SetTxBuffer(const uint8_t *pData, uint16_t length)
{
    return SpiSlaveDriverUnit_SetTxBuffer(pData, length);
}

SpiSlaveDriver_Status_t call_SpiSlaveDriverUnit_SetRxBuffer(uint8_t *pData, uint16_t maxLength)
{
    return SpiSlaveDriverUnit_SetRxBuffer(pData, maxLength);
}

SpiSlaveDriver_Status_t call_SpiSlaveDriverUnit_GetRxLength(uint16_t *pLength)
{
    return SpiSlaveDriverUnit_GetRxLength(pLength);
}

SpiSlaveDriver_Status_t call_SpiSlaveDriverUnit_IsSelected(bool *pIsSelected)
{
    return SpiSlaveDriverUnit_IsSelected(pIsSelected);
}

SpiSlaveDriver_Status_t call_SpiSlaveDriverUnit_RegisterRxCallback(SpiSlaveDriver_RxCallback_t callback)
{
    return SpiSlaveDriverUnit_RegisterRxCallback(callback);
}

SpiSlaveDriver_Status_t call_SpiSlaveDriverUnit_RegisterTxCallback(SpiSlaveDriver_TxCallback_t callback)
{
    return SpiSlaveDriverUnit_RegisterTxCallback(callback);
}

SpiSlaveDriver_Status_t call_SpiSlaveDriverUnit_DeInit(void)
{
    return SpiSlaveDriverUnit_DeInit();
}
