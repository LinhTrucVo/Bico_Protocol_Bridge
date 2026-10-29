// NvmService Implementation

#include <stddef.h>
#include "nvmService.h"
#include "nvmServiceCfg.h"
#include "nvmDriver.h"

typedef struct
{
    bool valid;
    uint16_t length;
    uint32_t crc;
    uint8_t data[BPB_NVM_SERVICE_CFG_MAX_BLOB_SIZE];
} NvmService_Record_t;

typedef struct
{
    bool initialized;
    NvmService_Record_t records[BPB_NVM_SERVICE_CFG_MAX_KEYS];
} NvmService_Context_t;

static NvmService_Context_t context = {0};

static uint32_t NvmService_CalcCrc(const uint8_t *pData, uint16_t length)
{
    uint32_t crc = 0xFFFFFFFFU;
    for (uint16_t i = 0; i < length; i++)
    {
        crc ^= pData[i];
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
    return crc;
}

NvmService_Status_t NvmServiceUnit_Init(void)
{
    /* Initialize the underlying NVM Driver */
    NvmDriver_Config_t nvmCfg = {0};
    nvmCfg.type = BPB_NVM_TYPE_FLASH;
    nvmCfg.baseAddress = 0x08010000U;
    nvmCfg.totalSize = BPB_NVM_CFG_TOTAL_SIZE;
    nvmCfg.pageSize = 256U;
    nvmCfg.sectorSize = 4096U;
    nvmCfg.enableWriteProtection = false;

    if (NvmDriverUnit_Init(&nvmCfg) != BPB_NVMDRIVER_OK)
    {
        return BPB_NVM_SERVICE_STATUS_ERROR;
    }

    context.initialized = true;
    for (uint8_t i = 0; i < BPB_NVM_SERVICE_CFG_MAX_KEYS; i++)
    {
        context.records[i].valid = false;
        context.records[i].length = 0;
        context.records[i].crc = 0;
    }
    return BPB_NVM_SERVICE_STATUS_OK;
}

NvmService_Status_t NvmServiceUnit_DeInit(void)
{
    (void)NvmDriverUnit_DeInit();
    context.initialized = false;
    return BPB_NVM_SERVICE_STATUS_OK;
}

static bool NvmService_IsKeyValid(NvmService_Key_t key)
{
    return ((uint8_t)key < BPB_NVM_SERVICE_CFG_MAX_KEYS);
}

NvmService_Status_t NvmServiceUnit_Save(const NvmService_Blob_t *pBlob)
{
    if (!context.initialized)
    {
        return BPB_NVM_SERVICE_STATUS_NOT_INITIALIZED;
    }
    if (pBlob == NULL || pBlob->pData == NULL || pBlob->dataLength == 0)
    {
        return BPB_NVM_SERVICE_STATUS_INVALID_PARAM;
    }
    if (!NvmService_IsKeyValid(pBlob->key) || pBlob->dataLength > BPB_NVM_SERVICE_CFG_MAX_BLOB_SIZE)
    {
        return BPB_NVM_SERVICE_STATUS_INVALID_PARAM;
    }

    NvmService_Record_t *rec = &context.records[pBlob->key];
    rec->length = pBlob->dataLength;
    for (uint16_t i = 0; i < pBlob->dataLength; i++)
    {
        rec->data[i] = pBlob->pData[i];
    }
    rec->crc = NvmService_CalcCrc(rec->data, rec->length);
    rec->valid = true;
    return BPB_NVM_SERVICE_STATUS_OK;
}

NvmService_Status_t NvmServiceUnit_Load(NvmService_Key_t key, uint8_t *pData, uint16_t maxLength, uint16_t *pOutLength)
{
    if (!context.initialized)
    {
        return BPB_NVM_SERVICE_STATUS_NOT_INITIALIZED;
    }
    if (pData == NULL || pOutLength == NULL)
    {
        return BPB_NVM_SERVICE_STATUS_INVALID_PARAM;
    }
    if (!NvmService_IsKeyValid(key))
    {
        return BPB_NVM_SERVICE_STATUS_INVALID_PARAM;
    }

    NvmService_Record_t *rec = &context.records[key];
    if (!rec->valid)
    {
        return BPB_NVM_SERVICE_STATUS_NOT_FOUND;
    }
    if (rec->length > maxLength)
    {
        return BPB_NVM_SERVICE_STATUS_INVALID_PARAM;
    }

    uint32_t crc = NvmService_CalcCrc(rec->data, rec->length);
    if (crc != rec->crc)
    {
        return BPB_NVM_SERVICE_STATUS_CRC_ERROR;
    }

    for (uint16_t i = 0; i < rec->length; i++)
    {
        pData[i] = rec->data[i];
    }
    *pOutLength = rec->length;
    return BPB_NVM_SERVICE_STATUS_OK;
}

NvmService_Status_t NvmServiceUnit_Erase(NvmService_Key_t key)
{
    if (!context.initialized)
    {
        return BPB_NVM_SERVICE_STATUS_NOT_INITIALIZED;
    }
    if (!NvmService_IsKeyValid(key))
    {
        return BPB_NVM_SERVICE_STATUS_INVALID_PARAM;
    }

    context.records[key].valid = false;
    context.records[key].length = 0;
    context.records[key].crc = 0;
    return BPB_NVM_SERVICE_STATUS_OK;
}

NvmService_Status_t NvmServiceUnit_EraseAll(void)
{
    if (!context.initialized)
    {
        return BPB_NVM_SERVICE_STATUS_NOT_INITIALIZED;
    }
    for (uint8_t i = 0; i < BPB_NVM_SERVICE_CFG_MAX_KEYS; i++)
    {
        context.records[i].valid = false;
        context.records[i].length = 0;
        context.records[i].crc = 0;
    }
    return BPB_NVM_SERVICE_STATUS_OK;
}

NvmService_Status_t NvmServiceUnit_Exists(NvmService_Key_t key, bool *pExists)
{
    if (pExists == NULL)
    {
        return BPB_NVM_SERVICE_STATUS_INVALID_PARAM;
    }
    if (!NvmService_IsKeyValid(key))
    {
        return BPB_NVM_SERVICE_STATUS_INVALID_PARAM;
    }
    *pExists = context.records[key].valid;
    return BPB_NVM_SERVICE_STATUS_OK;
}

NvmService_Status_t NvmServiceUnit_ComputeCrc(const uint8_t *pData, uint16_t length, uint32_t *pCrc)
{
    if (pData == NULL || pCrc == NULL)
    {
        return BPB_NVM_SERVICE_STATUS_INVALID_PARAM;
    }
    *pCrc = NvmService_CalcCrc(pData, length);
    return BPB_NVM_SERVICE_STATUS_OK;
}
