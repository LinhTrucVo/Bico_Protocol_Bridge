// NvmDriver Implementation
#include "nvmDriver.h"
#include "nvmDriverCfg.h"

typedef struct
{
    bool initialized;
    bool writeProtected;
    NvmDriver_Config_t config;
    NvmDriver_OperationCallback_t callback;
} NvmDriver_Context_t;

static NvmDriver_Context_t context = {0};
static uint8_t nvmStorage[NVM_CFG_TOTAL_SIZE];

static bool NvmDriver_IsAddressValid(NvmDriver_Address_t address, uint32_t length)
{
    if (address < context.config.baseAddress)
    {
        return false;
    }
    if ((address - context.config.baseAddress) + length > context.config.totalSize)
    {
        return false;
    }
    return true;
}

NvmDriver_Status_t NvmDriverUnit_Init(const NvmDriver_Config_t *pConfig)
{
    if (pConfig == NULL)
    {
        return NVM_STATUS_ERROR;
    }

    // TODO: Add vendor-specific HAL initialization here
    context.config = *pConfig;
    context.initialized = true;
    context.writeProtected = pConfig->enableWriteProtection;
    context.callback = NULL;
    return NVM_STATUS_OK;
}

NvmDriver_Status_t NvmDriverUnit_Read(NvmDriver_Address_t address, uint8_t *pData, uint32_t length)
{
    if (!context.initialized)
    {
        return NVM_STATUS_NOT_INITIALIZED;
    }
    if (pData == NULL || length == 0)
    {
        return NVM_STATUS_ERROR;
    }
    if (!NvmDriver_IsAddressValid(address, length))
    {
        return NVM_STATUS_INVALID_ADDRESS;
    }

    uint32_t offset = address - context.config.baseAddress;
    for (uint32_t i = 0; i < length; i++)
    {
        pData[i] = nvmStorage[offset + i];
    }
    return NVM_STATUS_OK;
}

NvmDriver_Status_t NvmDriverUnit_Write(NvmDriver_Address_t address, const uint8_t *pData, uint32_t length)
{
    if (!context.initialized)
    {
        return NVM_STATUS_NOT_INITIALIZED;
    }
    if (context.writeProtected)
    {
        return NVM_STATUS_WRITE_PROTECTED;
    }
    if (pData == NULL || length == 0)
    {
        return NVM_STATUS_ERROR;
    }
    if (!NvmDriver_IsAddressValid(address, length))
    {
        return NVM_STATUS_INVALID_ADDRESS;
    }

    uint32_t offset = address - context.config.baseAddress;
    for (uint32_t i = 0; i < length; i++)
    {
        nvmStorage[offset + i] = pData[i];
    }
    if (context.callback != NULL)
    {
        context.callback(NVM_STATUS_OK);
    }
    return NVM_STATUS_OK;
}

NvmDriver_Status_t NvmDriverUnit_ErasePage(NvmDriver_Address_t address)
{
    if (!context.initialized)
    {
        return NVM_STATUS_NOT_INITIALIZED;
    }
    if (!NvmDriver_IsAddressValid(address, context.config.pageSize))
    {
        return NVM_STATUS_INVALID_ADDRESS;
    }

    uint32_t offset = address - context.config.baseAddress;
    for (uint32_t i = 0; i < context.config.pageSize; i++)
    {
        nvmStorage[offset + i] = 0xFF;
    }
    return NVM_STATUS_OK;
}

NvmDriver_Status_t NvmDriverUnit_EraseSector(NvmDriver_Address_t address)
{
    if (!context.initialized)
    {
        return NVM_STATUS_NOT_INITIALIZED;
    }
    if (!NvmDriver_IsAddressValid(address, context.config.sectorSize))
    {
        return NVM_STATUS_INVALID_ADDRESS;
    }

    uint32_t offset = address - context.config.baseAddress;
    for (uint32_t i = 0; i < context.config.sectorSize; i++)
    {
        nvmStorage[offset + i] = 0xFF;
    }
    return NVM_STATUS_OK;
}

NvmDriver_Status_t NvmDriverUnit_EraseChip(void)
{
    if (!context.initialized)
    {
        return NVM_STATUS_NOT_INITIALIZED;
    }
    for (uint32_t i = 0; i < context.config.totalSize; i++)
    {
        nvmStorage[i] = 0xFF;
    }
    return NVM_STATUS_OK;
}

NvmDriver_Status_t NvmDriverUnit_WriteWithErase(NvmDriver_Address_t address, const uint8_t *pData, uint32_t length)
{
    NvmDriver_Status_t status = NvmDriverUnit_ErasePage(address);
    if (status != NVM_STATUS_OK)
    {
        return status;
    }
    return NvmDriverUnit_Write(address, pData, length);
}

NvmDriver_Status_t NvmDriverUnit_Verify(NvmDriver_Address_t address, const uint8_t *pData, uint32_t length, bool *pIsValid)
{
    if (pIsValid == NULL || pData == NULL)
    {
        return NVM_STATUS_ERROR;
    }
    if (!NvmDriver_IsAddressValid(address, length))
    {
        return NVM_STATUS_INVALID_ADDRESS;
    }

    uint32_t offset = address - context.config.baseAddress;
    *pIsValid = true;
    for (uint32_t i = 0; i < length; i++)
    {
        if (nvmStorage[offset + i] != pData[i])
        {
            *pIsValid = false;
            break;
        }
    }
    return NVM_STATUS_OK;
}

NvmDriver_Status_t NvmDriverUnit_CalculateCrc(NvmDriver_Address_t address, uint32_t length, uint32_t *pCrc)
{
    if (pCrc == NULL)
    {
        return NVM_STATUS_ERROR;
    }
    if (!NvmDriver_IsAddressValid(address, length))
    {
        return NVM_STATUS_INVALID_ADDRESS;
    }

    uint32_t crc = 0xFFFFFFFFU;
    uint32_t offset = address - context.config.baseAddress;
    for (uint32_t i = 0; i < length; i++)
    {
        crc ^= nvmStorage[offset + i];
        for (uint8_t j = 0; j < 8; j++)
        {
            if (crc & 1U)
            {
                crc = (crc >> 1U) ^ 0xEDB88320U;
            }
            else
            {
                crc >>= 1U;
            }
        }
    }
    *pCrc = crc;
    return NVM_STATUS_OK;
}

NvmDriver_Status_t NvmDriverUnit_IsBusy(bool *pIsBusy)
{
    if (pIsBusy == NULL)
    {
        return NVM_STATUS_ERROR;
    }
    *pIsBusy = false;
    return NVM_STATUS_OK;
}

NvmDriver_Status_t NvmDriverUnit_GetInfo(NvmDriver_Config_t *pConfig)
{
    if (pConfig == NULL)
    {
        return NVM_STATUS_ERROR;
    }
    *pConfig = context.config;
    return NVM_STATUS_OK;
}

NvmDriver_Status_t NvmDriverUnit_EnableWriteProtection(void)
{
    context.writeProtected = true;
    return NVM_STATUS_OK;
}

NvmDriver_Status_t NvmDriverUnit_DisableWriteProtection(void)
{
    context.writeProtected = false;
    return NVM_STATUS_OK;
}

NvmDriver_Status_t NvmDriverUnit_RegisterCallback(NvmDriver_OperationCallback_t callback)
{
    context.callback = callback;
    return NVM_STATUS_OK;
}

NvmDriver_Status_t NvmDriverUnit_DeInit(void)
{
    // TODO: Add vendor-specific HAL deinitialization here
    context.initialized = false;
    context.callback = NULL;
    return NVM_STATUS_OK;
}
