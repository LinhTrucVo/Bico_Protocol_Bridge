// NvmDriver - Public Interface
#ifndef NVMDRIVER_H
#define NVMDRIVER_H
#include <stdint.h>
#include <stdbool.h>
#include "nvmDriverCfg.h"
#include "nvmDriverUnit.h"
typedef enum
{
    NVM_STATUS_OK = 0,
    NVM_STATUS_ERROR,
    NVM_STATUS_BUSY
} NvmDriver_Status_t;
NvmDriver_Status_t NvmDriver_Init(void);
NvmDriver_Status_t NvmDriver_DeInit(void);
#endif /* NVMDRIVER_H */
