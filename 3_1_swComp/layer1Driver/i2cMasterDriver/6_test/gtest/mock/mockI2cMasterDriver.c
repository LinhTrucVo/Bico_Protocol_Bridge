// This file defines the FFF for functions and MOCK functions for I2cMasterDriver testing

//============================================================================
// Dependencies
//============================================================================
#include "mockI2cMasterDriver.h"

// Include the .c file to get access to static variables and functions
#include "i2cMasterDriverUnit.c"

//============================================================================
// Mock function definitions
//============================================================================

// Required for FFF
DEFINE_FFF_GLOBALS;

// DEFINE_FAKE_VALUE_FUNC(int, ExternalFunction, int);

//============================================================================
// Static function wrapper definitions
//============================================================================

I2cMasterDriver_Status_t call_I2cMasterDriverUnit_Init(const I2cMasterDriver_Config_t *pConfig)
{
    return I2cMasterDriverUnit_Init(pConfig);
}

I2cMasterDriver_Status_t call_I2cMasterDriverUnit_SetSpeed(I2cMasterDriver_Speed_t speed)
{
    return I2cMasterDriverUnit_SetSpeed(speed);
}

I2cMasterDriver_Status_t call_I2cMasterDriverUnit_Write(I2cMasterDriver_Address_t address, const uint8_t *pData, uint16_t length)
{
    return I2cMasterDriverUnit_Write(address, pData, length);
}

I2cMasterDriver_Status_t call_I2cMasterDriverUnit_WriteWithTimeout(I2cMasterDriver_Address_t address, const uint8_t *pData, uint16_t length, uint32_t timeoutMs)
{
    return I2cMasterDriverUnit_WriteWithTimeout(address, pData, length, timeoutMs);
}

I2cMasterDriver_Status_t call_I2cMasterDriverUnit_Read(I2cMasterDriver_Address_t address, uint8_t *pData, uint16_t length)
{
    return I2cMasterDriverUnit_Read(address, pData, length);
}

I2cMasterDriver_Status_t call_I2cMasterDriverUnit_ReadWithTimeout(I2cMasterDriver_Address_t address, uint8_t *pData, uint16_t length, uint32_t timeoutMs)
{
    return I2cMasterDriverUnit_ReadWithTimeout(address, pData, length, timeoutMs);
}

I2cMasterDriver_Status_t call_I2cMasterDriverUnit_WriteRead(I2cMasterDriver_Address_t address, const uint8_t *pWriteData, uint16_t writeLength, uint8_t *pReadData, uint16_t readLength)
{
    return I2cMasterDriverUnit_WriteRead(address, pWriteData, writeLength, pReadData, readLength);
}

I2cMasterDriver_Status_t call_I2cMasterDriverUnit_WriteRegister(I2cMasterDriver_Address_t address, uint8_t regAddress, const uint8_t *pData, uint16_t length)
{
    return I2cMasterDriverUnit_WriteRegister(address, regAddress, pData, length);
}

I2cMasterDriver_Status_t call_I2cMasterDriverUnit_ReadRegister(I2cMasterDriver_Address_t address, uint8_t regAddress, uint8_t *pData, uint16_t length)
{
    return I2cMasterDriverUnit_ReadRegister(address, regAddress, pData, length);
}

I2cMasterDriver_Status_t call_I2cMasterDriverUnit_ScanBus(I2cMasterDriver_Address_t *pFoundAddresses, uint8_t maxAddresses, uint8_t *pNumFound)
{
    return I2cMasterDriverUnit_ScanBus(pFoundAddresses, maxAddresses, pNumFound);
}

I2cMasterDriver_Status_t call_I2cMasterDriverUnit_IsBusy(bool *pIsBusy)
{
    return I2cMasterDriverUnit_IsBusy(pIsBusy);
}

I2cMasterDriver_Status_t call_I2cMasterDriverUnit_RegisterCallback(I2cMasterDriver_Callback_t callback)
{
    return I2cMasterDriverUnit_RegisterCallback(callback);
}

I2cMasterDriver_Status_t call_I2cMasterDriverUnit_DeInit(void)
{
    return I2cMasterDriverUnit_DeInit();
}
