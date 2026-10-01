// ESP32 implementation of the NVM port (nvmDriverPorting.h). The storage is kept in NVS as fixed size chunks.

//============================================================================
// Dependencies
//============================================================================
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include "nvmDriverPorting.h"
#include "nvmPortEsp32Cfg.h"
#include "nvs.h"
#include "nvs_flash.h"

//============================================================================
// Local Macros
//============================================================================
#define NVM_PORT_KEY_SIZE   16U
#define NVM_PORT_ERASED     0xFFU

//============================================================================
// Local Function Prototypes
//============================================================================
static void NvmPort_MakeKey(uint32_t chunkIndex, char *pKey);
static bool NvmPort_LoadChunk(nvs_handle_t handle, uint32_t chunkIndex, uint8_t *pChunk);

//============================================================================
// Public Function Implementations
//============================================================================
bool NvmPort_Init(void)
{
    esp_err_t result = nvs_flash_init();
    if ((result == ESP_ERR_NVS_NO_FREE_PAGES) || (result == ESP_ERR_NVS_NEW_VERSION_FOUND))
    {
        (void)nvs_flash_erase();
        result = nvs_flash_init();
    }
    return (result == ESP_OK);
}

void NvmPort_DeInit(void)
{
    // The NVS partition can be shared with other components, so it stays initialized.
}

bool NvmPort_Read(uint32_t offset, uint8_t *pData, uint32_t length)
{
    if (pData == NULL)
    {
        return false;
    }

    nvs_handle_t handle;
    if (nvs_open(BICO_PROTOCOL_BRIDGE_NVM_NAMESPACE, NVS_READONLY, &handle) != ESP_OK)
    {
        // Nothing was stored yet, so the namespace does not exist and everything reads as erased.
        (void)memset(pData, NVM_PORT_ERASED, length);
        return true;
    }

    uint8_t chunk[BICO_PROTOCOL_BRIDGE_NVM_CHUNK_SIZE];
    bool done = true;
    uint32_t position = 0U;
    while (done && (position < length))
    {
        const uint32_t address = offset + position;
        const uint32_t chunkIndex = address / BICO_PROTOCOL_BRIDGE_NVM_CHUNK_SIZE;
        const uint32_t chunkOffset = address % BICO_PROTOCOL_BRIDGE_NVM_CHUNK_SIZE;
        uint32_t count = BICO_PROTOCOL_BRIDGE_NVM_CHUNK_SIZE - chunkOffset;
        if (count > (length - position))
        {
            count = length - position;
        }

        done = NvmPort_LoadChunk(handle, chunkIndex, chunk);
        if (done)
        {
            (void)memcpy(&pData[position], &chunk[chunkOffset], count);
        }
        position += count;
    }

    nvs_close(handle);
    return done;
}

bool NvmPort_Write(uint32_t offset, const uint8_t *pData, uint32_t length)
{
    if (pData == NULL)
    {
        return false;
    }

    nvs_handle_t handle;
    if (nvs_open(BICO_PROTOCOL_BRIDGE_NVM_NAMESPACE, NVS_READWRITE, &handle) != ESP_OK)
    {
        return false;
    }

    uint8_t chunk[BICO_PROTOCOL_BRIDGE_NVM_CHUNK_SIZE];
    char key[NVM_PORT_KEY_SIZE];
    bool done = true;
    uint32_t position = 0U;
    while (done && (position < length))
    {
        const uint32_t address = offset + position;
        const uint32_t chunkIndex = address / BICO_PROTOCOL_BRIDGE_NVM_CHUNK_SIZE;
        const uint32_t chunkOffset = address % BICO_PROTOCOL_BRIDGE_NVM_CHUNK_SIZE;
        uint32_t count = BICO_PROTOCOL_BRIDGE_NVM_CHUNK_SIZE - chunkOffset;
        if (count > (length - position))
        {
            count = length - position;
        }

        done = NvmPort_LoadChunk(handle, chunkIndex, chunk);
        if (done)
        {
            (void)memcpy(&chunk[chunkOffset], &pData[position], count);
            NvmPort_MakeKey(chunkIndex, key);
            done = (nvs_set_blob(handle, key, chunk, BICO_PROTOCOL_BRIDGE_NVM_CHUNK_SIZE) == ESP_OK);
        }
        position += count;
    }

    if (done)
    {
        done = (nvs_commit(handle) == ESP_OK);
    }
    nvs_close(handle);
    return done;
}

bool NvmPort_Erase(uint32_t offset, uint32_t length)
{
    nvs_handle_t handle;
    if (nvs_open(BICO_PROTOCOL_BRIDGE_NVM_NAMESPACE, NVS_READWRITE, &handle) != ESP_OK)
    {
        return false;
    }

    uint8_t chunk[BICO_PROTOCOL_BRIDGE_NVM_CHUNK_SIZE];
    char key[NVM_PORT_KEY_SIZE];
    bool done = true;
    uint32_t position = 0U;
    while (done && (position < length))
    {
        const uint32_t address = offset + position;
        const uint32_t chunkIndex = address / BICO_PROTOCOL_BRIDGE_NVM_CHUNK_SIZE;
        const uint32_t chunkOffset = address % BICO_PROTOCOL_BRIDGE_NVM_CHUNK_SIZE;
        uint32_t count = BICO_PROTOCOL_BRIDGE_NVM_CHUNK_SIZE - chunkOffset;
        if (count > (length - position))
        {
            count = length - position;
        }

        NvmPort_MakeKey(chunkIndex, key);
        if (count == BICO_PROTOCOL_BRIDGE_NVM_CHUNK_SIZE)
        {
            const esp_err_t result = nvs_erase_key(handle, key);
            done = (result == ESP_OK) || (result == ESP_ERR_NVS_NOT_FOUND);
        }
        else
        {
            done = NvmPort_LoadChunk(handle, chunkIndex, chunk);
            if (done)
            {
                (void)memset(&chunk[chunkOffset], NVM_PORT_ERASED, count);
                done = (nvs_set_blob(handle, key, chunk, BICO_PROTOCOL_BRIDGE_NVM_CHUNK_SIZE) == ESP_OK);
            }
        }
        position += count;
    }

    if (done)
    {
        done = (nvs_commit(handle) == ESP_OK);
    }
    nvs_close(handle);
    return done;
}

//============================================================================
// Local Function Implementations
//============================================================================
static void NvmPort_MakeKey(uint32_t chunkIndex, char *pKey)
{
    (void)snprintf(pKey, NVM_PORT_KEY_SIZE, "c%05lu", (unsigned long)chunkIndex);
}

// A chunk that was never written or that was erased reads as 0xFF.
static bool NvmPort_LoadChunk(nvs_handle_t handle, uint32_t chunkIndex, uint8_t *pChunk)
{
    char key[NVM_PORT_KEY_SIZE];
    NvmPort_MakeKey(chunkIndex, key);

    size_t size = BICO_PROTOCOL_BRIDGE_NVM_CHUNK_SIZE;
    const esp_err_t result = nvs_get_blob(handle, key, pChunk, &size);
    if (result == ESP_ERR_NVS_NOT_FOUND)
    {
        (void)memset(pChunk, NVM_PORT_ERASED, BICO_PROTOCOL_BRIDGE_NVM_CHUNK_SIZE);
        return true;
    }
    return (result == ESP_OK) && (size == BICO_PROTOCOL_BRIDGE_NVM_CHUNK_SIZE);
}
