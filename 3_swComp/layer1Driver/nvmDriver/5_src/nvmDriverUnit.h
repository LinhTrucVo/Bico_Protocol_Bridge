#ifndef NVMDRIVERUNIT_H
#define NVMDRIVERUNIT_H

//============================================================================
// Dependencies
//============================================================================
#include <stdint.h>
#include <stdbool.h>
#include "nvmDriverCfg.h"

//============================================================================
// Configuration Macros
//============================================================================
#define NVM_CFG_TOTAL_SIZE              4096

//============================================================================
// Type Definitions
//============================================================================
typedef enum
{
    NVM_TYPE_FLASH,
    NVM_TYPE_EEPROM,
    NVM_TYPE_SRAM
} NvmDriver_Type_t;

typedef struct
{
    NvmDriver_Type_t type;
    uint32_t baseAddress;
    uint32_t totalSize;
    uint32_t pageSize;
    uint32_t sectorSize;
    bool enableWriteProtection;
} NvmDriver_Config_t;

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

//============================================================================
// Status Enum Mappings
//============================================================================
#define NVM_STATUS_OK                   NVMDRIVER_OK
#define NVM_STATUS_ERROR                NVMDRIVER_ERROR
#define NVM_STATUS_BUSY                 NVMDRIVER_BUSY
#define NVM_STATUS_INVALID_ADDRESS      NVMDRIVER_INVALID_ADDRESS
#define NVM_STATUS_INVALID_LENGTH       NVMDRIVER_INVALID_LENGTH
#define NVM_STATUS_WRITE_PROTECTED      NVMDRIVER_WRITE_PROTECTED
#define NVM_STATUS_VERIFY_FAILED        NVMDRIVER_VERIFY_FAILED
#define NVM_STATUS_TIMEOUT              NVMDRIVER_TIMEOUT
#define NVM_STATUS_NOT_INITIALIZED      NVMDRIVER_NOT_INITIALIZED

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
