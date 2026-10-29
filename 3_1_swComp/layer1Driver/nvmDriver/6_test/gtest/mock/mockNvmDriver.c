// This file defines the FFF for functions and MOCK functions for NvmDriver testing

//============================================================================
// Dependencies
//============================================================================
#include "mockNvmDriver.h"

// Include the .c file to get access to static variables and functions
#include "nvmDriverUnit.c"

//============================================================================
// Mock function definitions
//============================================================================

// Required for FFF
DEFINE_FFF_GLOBALS;

// DEFINE_FAKE_VALUE_FUNC(int, ExternalFunction, int);

//============================================================================
// Static function wrapper definitions
//============================================================================

NvmDriver_Status_t call_NvmDriverUnit_Init(const NvmDriver_Config_t *pConfig)
{
    return NvmDriverUnit_Init(pConfig);
}

NvmDriver_Status_t call_NvmDriverUnit_Read(NvmDriver_Address_t address, uint8_t *pData, uint32_t length)
{
    return NvmDriverUnit_Read(address, pData, length);
}

NvmDriver_Status_t call_NvmDriverUnit_Write(NvmDriver_Address_t address, const uint8_t *pData, uint32_t length)
{
    return NvmDriverUnit_Write(address, pData, length);
}

NvmDriver_Status_t call_NvmDriverUnit_ErasePage(NvmDriver_Address_t address)
{
    return NvmDriverUnit_ErasePage(address);
}

NvmDriver_Status_t call_NvmDriverUnit_EraseSector(NvmDriver_Address_t address)
{
    return NvmDriverUnit_EraseSector(address);
}

NvmDriver_Status_t call_NvmDriverUnit_EraseChip(void)
{
    return NvmDriverUnit_EraseChip();
}

NvmDriver_Status_t call_NvmDriverUnit_WriteWithErase(NvmDriver_Address_t address, const uint8_t *pData, uint32_t length)
{
    return NvmDriverUnit_WriteWithErase(address, pData, length);
}

NvmDriver_Status_t call_NvmDriverUnit_Verify(NvmDriver_Address_t address, const uint8_t *pData, uint32_t length, bool *pIsValid)
{
    return NvmDriverUnit_Verify(address, pData, length, pIsValid);
}

NvmDriver_Status_t call_NvmDriverUnit_CalculateCrc(NvmDriver_Address_t address, uint32_t length, uint32_t *pCrc)
{
    return NvmDriverUnit_CalculateCrc(address, length, pCrc);
}

NvmDriver_Status_t call_NvmDriverUnit_IsBusy(bool *pIsBusy)
{
    return NvmDriverUnit_IsBusy(pIsBusy);
}

NvmDriver_Status_t call_NvmDriverUnit_GetInfo(NvmDriver_Config_t *pConfig)
{
    return NvmDriverUnit_GetInfo(pConfig);
}

NvmDriver_Status_t call_NvmDriverUnit_EnableWriteProtection(void)
{
    return NvmDriverUnit_EnableWriteProtection();
}

NvmDriver_Status_t call_NvmDriverUnit_DisableWriteProtection(void)
{
    return NvmDriverUnit_DisableWriteProtection();
}

NvmDriver_Status_t call_NvmDriverUnit_RegisterCallback(NvmDriver_OperationCallback_t callback)
{
    return NvmDriverUnit_RegisterCallback(callback);
}

NvmDriver_Status_t call_NvmDriverUnit_DeInit(void)
{
    return NvmDriverUnit_DeInit();
}
