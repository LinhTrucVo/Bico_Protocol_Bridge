// NvmDriver Implementation
#include "nvmDriver.h"
typedef struct
{
    uint8_t initialized;
} NvmDriver_Context_t;
static NvmDriver_Context_t context = {0};
NvmDriver_Status_t NvmDriver_Init(void)
{
    // TODO: Add vendor-specific HAL initialization here
    context.initialized = 1;
    return NVM_STATUS_OK;
}
NvmDriver_Status_t NvmDriver_DeInit(void)
{
    // TODO: Add vendor-specific HAL deinitialization here
    context.initialized = 0;
    return NVM_STATUS_OK;
}
