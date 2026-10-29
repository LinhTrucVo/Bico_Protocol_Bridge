// This file defines the FFF for functions and MOCK functions for I2cSlaveDriver testing

//============================================================================
// Dependencies
//============================================================================
#include "mockI2cSlaveDriver.h"

// Include the .c file to get access to static variables and functions
#include "i2cSlaveDriverUnit.c"

//============================================================================
// Mock function definitions
//============================================================================

// Required for FFF
DEFINE_FFF_GLOBALS;

// DEFINE_FAKE_VALUE_FUNC(int, ExternalFunction, int);

//============================================================================
// Static function wrapper definitions
//============================================================================

I2cSlaveDriver_Status_t call_I2cSlaveDriverUnit_Init(const I2cSlaveDriver_Config_t *pConfig)
{
    return I2cSlaveDriverUnit_Init(pConfig);
}

I2cSlaveDriver_Status_t call_I2cSlaveDriverUnit_SetAddress(I2cSlaveDriver_Address_t address)
{
    return I2cSlaveDriverUnit_SetAddress(address);
}

I2cSlaveDriver_Status_t call_I2cSlaveDriverUnit_GetAddress(I2cSlaveDriver_Address_t *pAddress)
{
    return I2cSlaveDriverUnit_GetAddress(pAddress);
}

I2cSlaveDriver_Status_t call_I2cSlaveDriverUnit_SetTxBuffer(const uint8_t *pData, uint16_t length)
{
    return I2cSlaveDriverUnit_SetTxBuffer(pData, length);
}

I2cSlaveDriver_Status_t call_I2cSlaveDriverUnit_SetRxBuffer(uint8_t *pData, uint16_t maxLength)
{
    return I2cSlaveDriverUnit_SetRxBuffer(pData, maxLength);
}

I2cSlaveDriver_Status_t call_I2cSlaveDriverUnit_GetRxLength(uint16_t *pLength)
{
    return I2cSlaveDriverUnit_GetRxLength(pLength);
}

I2cSlaveDriver_Status_t call_I2cSlaveDriverUnit_IsAddressed(bool *pIsAddressed)
{
    return I2cSlaveDriverUnit_IsAddressed(pIsAddressed);
}

I2cSlaveDriver_Status_t call_I2cSlaveDriverUnit_RegisterRxCallback(I2cSlaveDriver_RxCallback_t callback)
{
    return I2cSlaveDriverUnit_RegisterRxCallback(callback);
}

I2cSlaveDriver_Status_t call_I2cSlaveDriverUnit_RegisterTxCallback(I2cSlaveDriver_TxCallback_t callback)
{
    return I2cSlaveDriverUnit_RegisterTxCallback(callback);
}

I2cSlaveDriver_Status_t call_I2cSlaveDriverUnit_RegisterAddressMatchCallback(I2cSlaveDriver_AddressMatchCallback_t callback)
{
    return I2cSlaveDriverUnit_RegisterAddressMatchCallback(callback);
}

I2cSlaveDriver_Status_t call_I2cSlaveDriverUnit_DeInit(void)
{
    return I2cSlaveDriverUnit_DeInit();
}
