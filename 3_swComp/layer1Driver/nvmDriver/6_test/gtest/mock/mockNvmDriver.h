// This file declares the FFF for functions and MOCK functions for NvmDriver testing

#ifndef MOCKNVMDRIVER_H
#define MOCKNVMDRIVER_H

//============================================================================
// Dependencies
//============================================================================
#include "fff.h"

#include "nvmDriver.h"
#include "nvmDriverUnit.h"

//============================================================================
// Mock function declarations
//============================================================================
// Declare fake functions for external dependencies if any
// DECLARE_FAKE_VALUE_FUNC(int, ExternalFunction, int);

//============================================================================
// Static function wrapper declarations
//============================================================================

NvmDriver_Status_t call_NvmDriverUnit_Init(const NvmDriver_Config_t *pConfig);
NvmDriver_Status_t call_NvmDriverUnit_Read(NvmDriver_Address_t address, uint8_t *pData, uint32_t length);
NvmDriver_Status_t call_NvmDriverUnit_Write(NvmDriver_Address_t address, const uint8_t *pData, uint32_t length);
NvmDriver_Status_t call_NvmDriverUnit_ErasePage(NvmDriver_Address_t address);
NvmDriver_Status_t call_NvmDriverUnit_EraseSector(NvmDriver_Address_t address);
NvmDriver_Status_t call_NvmDriverUnit_EraseChip(void);
NvmDriver_Status_t call_NvmDriverUnit_WriteWithErase(NvmDriver_Address_t address, const uint8_t *pData, uint32_t length);
NvmDriver_Status_t call_NvmDriverUnit_Verify(NvmDriver_Address_t address, const uint8_t *pData, uint32_t length, bool *pIsValid);
NvmDriver_Status_t call_NvmDriverUnit_CalculateCrc(NvmDriver_Address_t address, uint32_t length, uint32_t *pCrc);
NvmDriver_Status_t call_NvmDriverUnit_IsBusy(bool *pIsBusy);
NvmDriver_Status_t call_NvmDriverUnit_GetInfo(NvmDriver_Config_t *pConfig);
NvmDriver_Status_t call_NvmDriverUnit_EnableWriteProtection(void);
NvmDriver_Status_t call_NvmDriverUnit_DisableWriteProtection(void);
NvmDriver_Status_t call_NvmDriverUnit_RegisterCallback(NvmDriver_OperationCallback_t callback);
NvmDriver_Status_t call_NvmDriverUnit_DeInit(void);

#endif /* MOCKNVMDRIVER_H */
