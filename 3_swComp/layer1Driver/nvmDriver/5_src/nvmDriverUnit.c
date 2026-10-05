// NvmDriver Implementation
#include <stddef.h>
#include <string.h>
#include "nvmDriver.h"
#include "nvmDriverCfg.h"
#include "nvmDriverPorting.h"

#define NVM_CHECK_BUFFER_SIZE   32U

typedef struct
{
    bool initialized;
    bool writeProtected;
    NvmDriver_Config_t config;
    NvmDriver_OperationCallback_t callback;
} NvmDriver_Context_t;

static NvmDriver_Context_t context = {0};

static bool NvmDriver_IsAddressValid(NvmDriver_Address_t address, uint32_t length);
static NvmDriver_Status_t NvmDriver_Finish(bool done);
static NvmDriver_Status_t NvmDriver_EraseRange(NvmDriver_Address_t address, uint32_t length);

NvmDriver_Status_t NvmDriverUnit_Init(const NvmDriver_Config_t *pConfig)
{
    if (pConfig == NULL)
    {
        return NVM_STATUS_ERROR;
    }
    if (context.initialized)
    {
        NvmPort_DeInit();
    }

    (void)memset(&context, 0, sizeof(context));
    if (!NvmPort_Init())
    {
        return NVM_STATUS_ERROR;
    }

    context.config = *pConfig;
    context.initialized = true;
    context.writeProtected = pConfig->enableWriteProtection;
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

    return NvmPort_Read(address - context.config.baseAddress, pData, length) ? NVM_STATUS_OK : NVM_STATUS_ERROR;
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

    return NvmDriver_Finish(NvmPort_Write(address - context.config.baseAddress, pData, length));
}

NvmDriver_Status_t NvmDriverUnit_ErasePage(NvmDriver_Address_t address)
{
    return NvmDriver_EraseRange(address, context.config.pageSize);
}

NvmDriver_Status_t NvmDriverUnit_EraseSector(NvmDriver_Address_t address)
{
    return NvmDriver_EraseRange(address, context.config.sectorSize);
}

NvmDriver_Status_t NvmDriverUnit_EraseChip(void)
{
    return NvmDriver_EraseRange(context.config.baseAddress, context.config.totalSize);
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
    if (!context.initialized)
    {
        return NVM_STATUS_NOT_INITIALIZED;
    }
    if (pIsValid == NULL || pData == NULL)
    {
        return NVM_STATUS_ERROR;
    }
    if (!NvmDriver_IsAddressValid(address, length))
    {
        return NVM_STATUS_INVALID_ADDRESS;
    }

    uint8_t buffer[NVM_CHECK_BUFFER_SIZE];
    const uint32_t offset = address - context.config.baseAddress;
    *pIsValid = true;
    for (uint32_t done = 0; (done < length) && *pIsValid; done += NVM_CHECK_BUFFER_SIZE)
    {
        const uint32_t chunk = ((length - done) < NVM_CHECK_BUFFER_SIZE) ? (length - done) : NVM_CHECK_BUFFER_SIZE;
        if (!NvmPort_Read(offset + done, buffer, chunk))
        {
            return NVM_STATUS_ERROR;
        }
        *pIsValid = (memcmp(buffer, &pData[done], chunk) == 0);
    }
    return NVM_STATUS_OK;
}

NvmDriver_Status_t NvmDriverUnit_CalculateCrc(NvmDriver_Address_t address, uint32_t length, uint32_t *pCrc)
{
    if (!context.initialized)
    {
        return NVM_STATUS_NOT_INITIALIZED;
    }
    if (pCrc == NULL)
    {
        return NVM_STATUS_ERROR;
    }
    if (!NvmDriver_IsAddressValid(address, length))
    {
        return NVM_STATUS_INVALID_ADDRESS;
    }

    uint8_t buffer[NVM_CHECK_BUFFER_SIZE];
    const uint32_t offset = address - context.config.baseAddress;
    uint32_t crc = 0xFFFFFFFFU;
    for (uint32_t done = 0; done < length; done += NVM_CHECK_BUFFER_SIZE)
    {
        const uint32_t chunk = ((length - done) < NVM_CHECK_BUFFER_SIZE) ? (length - done) : NVM_CHECK_BUFFER_SIZE;
        if (!NvmPort_Read(offset + done, buffer, chunk))
        {
            return NVM_STATUS_ERROR;
        }
        for (uint32_t i = 0; i < chunk; i++)
        {
            crc ^= buffer[i];
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
    if (context.initialized)
    {
        NvmPort_DeInit();
    }
    (void)memset(&context, 0, sizeof(context));
    return NVM_STATUS_OK;
}

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

static NvmDriver_Status_t NvmDriver_Finish(bool done)
{
    const NvmDriver_Status_t status = done ? NVM_STATUS_OK : NVM_STATUS_ERROR;
    if (context.callback != NULL)
    {
        context.callback(status);
    }
    return status;
}

static NvmDriver_Status_t NvmDriver_EraseRange(NvmDriver_Address_t address, uint32_t length)
{
    if (!context.initialized)
    {
        return NVM_STATUS_NOT_INITIALIZED;
    }
    if (context.writeProtected)
    {
        return NVM_STATUS_WRITE_PROTECTED;
    }
    if (!NvmDriver_IsAddressValid(address, length))
    {
        return NVM_STATUS_INVALID_ADDRESS;
    }

    return NvmDriver_Finish(NvmPort_Erase(address - context.config.baseAddress, length));
}
