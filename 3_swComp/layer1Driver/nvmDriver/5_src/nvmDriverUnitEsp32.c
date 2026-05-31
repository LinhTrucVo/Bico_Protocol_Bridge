// ESP32 variant implementation for NvmDriver. (nvmDriverUnitEsp32.c)
// This file provides the ESP32-specific implementation of the NvmDriver interface.
// Selected when L1_VARIANT is set to "Esp32" in the CMake build configuration.

//============================================================================
// Dependencies
//============================================================================
#include "nvmDriver.h"
#include "nvmDriverCfg.h"
#include "nvmDriverUnit.h"
#include "nvs_flash.h"
#include "nvs.h"
#include "esp_crc.h"
#include <string.h>
#include <stdio.h>

//============================================================================
// Internal Defines
//============================================================================
#define NVM_ESP32_NAMESPACE     "bicoNvm"
#define NVM_ESP32_KEY_MAX_LEN   15U
/* Address → NVS key format: "k%05lu" (max key length = NVS_KEY_NAME_MAX_SIZE - 1) */

//============================================================================
// Internal Types
//============================================================================
typedef struct
{
    bool                    initialized;
    bool                    writeProtected;
    NvmDriver_Callback_t    callback;
    NvmDriver_Info_t        info;
} NvmDriver_Context_t;

static NvmDriver_Context_t context = {0};

//============================================================================
// Internal Functions
//============================================================================
static void AddrToKey(NvmDriver_Address_t address, char *pKey)
{
    (void)snprintf(pKey, NVM_ESP32_KEY_MAX_LEN, "k%05lu", (unsigned long)address);
}

//============================================================================
// Public Functions
//============================================================================
NvmDriver_Status_t NvmDriverUnit_Init(const NvmDriver_Config_t *pConfig)
{
    if (pConfig == NULL) { return NVMDRIVER_ERROR; }

    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND)
    {
        (void)nvs_flash_erase();
        ret = nvs_flash_init();
    }
    if (ret != ESP_OK) { return NVMDRIVER_ERROR; }

    context.initialized   = true;
    context.writeProtected = false;
    context.info.totalSize = NVM_CFG_TOTAL_SIZE;
    context.info.pageSize  = NVM_CFG_PAGE_SIZE;
    context.info.sectorSize = NVM_CFG_SECTOR_SIZE;
    return NVMDRIVER_OK;
}

NvmDriver_Status_t NvmDriverUnit_Read(NvmDriver_Address_t address, uint8_t *pData, uint32_t length)
{
    if (!context.initialized) { return NVMDRIVER_NOT_INITIALIZED; }
    if (pData == NULL || length == 0U) { return NVMDRIVER_ERROR; }

    nvs_handle_t handle;
    char key[NVM_ESP32_KEY_MAX_LEN];
    AddrToKey(address, key);

    if (nvs_open(NVM_ESP32_NAMESPACE, NVS_READONLY, &handle) != ESP_OK) { return NVMDRIVER_ERROR; }
    size_t len = length;
    esp_err_t ret = nvs_get_blob(handle, key, pData, &len);
    nvs_close(handle);

    if (ret == ESP_ERR_NVS_NOT_FOUND)
    {
        /* Key never written — treat as erased (0xFF) */
        (void)memset(pData, 0xFFU, length);
        return NVMDRIVER_OK;
    }
    return (ret == ESP_OK) ? NVMDRIVER_OK : NVMDRIVER_ERROR;
}

NvmDriver_Status_t NvmDriverUnit_Write(NvmDriver_Address_t address, const uint8_t *pData, uint32_t length)
{
    if (!context.initialized) { return NVMDRIVER_NOT_INITIALIZED; }
    if (pData == NULL || length == 0U) { return NVMDRIVER_ERROR; }
    if (context.writeProtected) { return NVMDRIVER_WRITE_PROTECTED; }

    nvs_handle_t handle;
    char key[NVM_ESP32_KEY_MAX_LEN];
    AddrToKey(address, key);

    if (nvs_open(NVM_ESP32_NAMESPACE, NVS_READWRITE, &handle) != ESP_OK) { return NVMDRIVER_ERROR; }
    esp_err_t ret = nvs_set_blob(handle, key, pData, length);
    if (ret == ESP_OK) { ret = nvs_commit(handle); }
    nvs_close(handle);

    if (context.callback != NULL)
    {
        context.callback((ret == ESP_OK) ? NVMDRIVER_OK : NVMDRIVER_ERROR);
    }
    return (ret == ESP_OK) ? NVMDRIVER_OK : NVMDRIVER_ERROR;
}

NvmDriver_Status_t NvmDriverUnit_ErasePage(uint32_t pageNumber)
{
    if (!context.initialized) { return NVMDRIVER_NOT_INITIALIZED; }
    if (context.writeProtected) { return NVMDRIVER_WRITE_PROTECTED; }
    /* NVS abstraction: erase by address range is not directly supported per-page */
    /* Erase the key corresponding to the page start address */
    char key[NVM_ESP32_KEY_MAX_LEN];
    nvs_handle_t handle;
    AddrToKey((NvmDriver_Address_t)(pageNumber * NVM_CFG_PAGE_SIZE), key);

    if (nvs_open(NVM_ESP32_NAMESPACE, NVS_READWRITE, &handle) != ESP_OK) { return NVMDRIVER_ERROR; }
    esp_err_t ret = nvs_erase_key(handle, key);
    if (ret == ESP_ERR_NVS_NOT_FOUND) { ret = ESP_OK; } /* Already empty */
    if (ret == ESP_OK) { ret = nvs_commit(handle); }
    nvs_close(handle);
    return (ret == ESP_OK) ? NVMDRIVER_OK : NVMDRIVER_ERROR;
}

NvmDriver_Status_t NvmDriverUnit_EraseSector(uint32_t sectorNumber)
{
    if (!context.initialized) { return NVMDRIVER_NOT_INITIALIZED; }
    if (context.writeProtected) { return NVMDRIVER_WRITE_PROTECTED; }
    nvs_handle_t handle;
    if (nvs_open(NVM_ESP32_NAMESPACE, NVS_READWRITE, &handle) != ESP_OK) { return NVMDRIVER_ERROR; }
    esp_err_t ret = nvs_erase_all(handle);
    if (ret == ESP_OK) { ret = nvs_commit(handle); }
    nvs_close(handle);
    (void)sectorNumber;
    return (ret == ESP_OK) ? NVMDRIVER_OK : NVMDRIVER_ERROR;
}

NvmDriver_Status_t NvmDriverUnit_EraseChip(void)
{
    if (!context.initialized) { return NVMDRIVER_NOT_INITIALIZED; }
    if (context.writeProtected) { return NVMDRIVER_WRITE_PROTECTED; }
    if (nvs_flash_erase() != ESP_OK) { return NVMDRIVER_ERROR; }
    if (nvs_flash_init() != ESP_OK) { return NVMDRIVER_ERROR; }
    return NVMDRIVER_OK;
}

NvmDriver_Status_t NvmDriverUnit_WriteWithErase(NvmDriver_Address_t address, const uint8_t *pData, uint32_t length)
{
    /* NVS handles erase-before-write internally */
    return NvmDriverUnit_Write(address, pData, length);
}

NvmDriver_Status_t NvmDriverUnit_Verify(NvmDriver_Address_t address, const uint8_t *pData,
                                         uint32_t length, bool *pResult)
{
    if (!context.initialized) { return NVMDRIVER_NOT_INITIALIZED; }
    if (pData == NULL || pResult == NULL || length == 0U) { return NVMDRIVER_ERROR; }

    uint8_t readBuf[NVM_CFG_PAGE_SIZE];
    NvmDriver_Status_t status = NvmDriverUnit_Read(address, readBuf, length);
    if (status != NVMDRIVER_OK) { return status; }
    *pResult = (memcmp(pData, readBuf, length) == 0);
    return NVMDRIVER_OK;
}

NvmDriver_Status_t NvmDriverUnit_CalculateCrc(NvmDriver_Address_t address, uint32_t length, uint32_t *pCrc)
{
    if (!context.initialized) { return NVMDRIVER_NOT_INITIALIZED; }
    if (pCrc == NULL || length == 0U) { return NVMDRIVER_ERROR; }

    uint8_t readBuf[NVM_CFG_PAGE_SIZE];
    NvmDriver_Status_t status = NvmDriverUnit_Read(address, readBuf, length);
    if (status != NVMDRIVER_OK) { return status; }
    *pCrc = (uint32_t)esp_crc32_le(0U, readBuf, length);
    return NVMDRIVER_OK;
}

NvmDriver_Status_t NvmDriverUnit_IsBusy(bool *pIsBusy)
{
    if (!context.initialized) { return NVMDRIVER_NOT_INITIALIZED; }
    if (pIsBusy == NULL) { return NVMDRIVER_ERROR; }
    *pIsBusy = false; /* NVS operations on ESP32 are synchronous */
    return NVMDRIVER_OK;
}

NvmDriver_Status_t NvmDriverUnit_GetInfo(NvmDriver_Info_t *pInfo)
{
    if (!context.initialized) { return NVMDRIVER_NOT_INITIALIZED; }
    if (pInfo == NULL) { return NVMDRIVER_ERROR; }
    (void)memcpy(pInfo, &context.info, sizeof(NvmDriver_Info_t));
    return NVMDRIVER_OK;
}

NvmDriver_Status_t NvmDriverUnit_EnableWriteProtection(void)
{
    if (!context.initialized) { return NVMDRIVER_NOT_INITIALIZED; }
    context.writeProtected = true;
    return NVMDRIVER_OK;
}

NvmDriver_Status_t NvmDriverUnit_DisableWriteProtection(void)
{
    if (!context.initialized) { return NVMDRIVER_NOT_INITIALIZED; }
    context.writeProtected = false;
    return NVMDRIVER_OK;
}

NvmDriver_Status_t NvmDriverUnit_RegisterCallback(NvmDriver_Callback_t callback)
{
    if (!context.initialized) { return NVMDRIVER_NOT_INITIALIZED; }
    context.callback = callback;
    return NVMDRIVER_OK;
}

NvmDriver_Status_t NvmDriverUnit_DeInit(void)
{
    if (!context.initialized) { return NVMDRIVER_NOT_INITIALIZED; }
    (void)nvs_flash_deinit();
    (void)memset(&context, 0, sizeof(context));
    return NVMDRIVER_OK;
}
