#ifndef NVMDRIVERUNIT_H
#define NVMDRIVERUNIT_H

//============================================================================
// Dependencies
//============================================================================
#include <stdint.h>
#include <stdbool.h>
#include "nvmDriverCfg.h"

//============================================================================
// Type Definitions
//============================================================================
typedef struct NvmDriver_Config_t NvmDriver_Config_t;

typedef enum
{
    NVMDRIVER_OK,
    NVMDRIVER_ERROR,
    NVMDRIVER_BUSY,
    NVMDRIVER_INVALID_ADDRESS,
    NVMDRIVER_INVALID_LENGTH,
    NVMDRIVER_WRITE_PROTECTED,
    NVMDRIVER_VERIFY_FAILED,
    NVMDRIVER_TIMEOUT,
    NVMDRIVER_NOT_INITIALIZED
} NvmDriver_Status_t;

typedef uint32_t NvmDriver_Address_t;
typedef void (*NvmDriver_OperationCallback_t)(NvmDriver_Status_t status);

//============================================================================
// Public Functions
//============================================================================
NvmDriver_Status_t NvmDriverUnit_Init(const NvmDriver_Config_t *pConfig);
NvmDriver_Status_t NvmDriverUnit_Read(NvmDriver_Address_t address, uint8_t *pData, uint32_t length);
NvmDriver_Status_t NvmDriverUnit_Write(NvmDriver_Address_t address, const uint8_t *pData, uint32_t length);
NvmDriver_Status_t NvmDriverUnit_ErasePage(NvmDriver_Address_t address);
NvmDriver_Status_t NvmDriverUnit_EraseSector(NvmDriver_Address_t address);
NvmDriver_Status_t NvmDriverUnit_EraseChip(void);
NvmDriver_Status_t NvmDriverUnit_WriteWithErase(NvmDriver_Address_t address, const uint8_t *pData, uint32_t length);
NvmDriver_Status_t NvmDriverUnit_Verify(NvmDriver_Address_t address, const uint8_t *pData, uint32_t length, bool *pIsValid);
NvmDriver_Status_t NvmDriverUnit_CalculateCrc(NvmDriver_Address_t address, uint32_t length, uint32_t *pCrc);
NvmDriver_Status_t NvmDriverUnit_IsBusy(bool *pIsBusy);
NvmDriver_Status_t NvmDriverUnit_GetInfo(NvmDriver_Config_t *pConfig);
NvmDriver_Status_t NvmDriverUnit_EnableWriteProtection(void);
NvmDriver_Status_t NvmDriverUnit_DisableWriteProtection(void);
NvmDriver_Status_t NvmDriverUnit_RegisterCallback(NvmDriver_OperationCallback_t callback);
NvmDriver_Status_t NvmDriverUnit_DeInit(void);

#endif /* NVMDRIVERUNIT_H */
