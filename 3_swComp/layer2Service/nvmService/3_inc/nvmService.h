// NvmService - Public Interface

#ifndef NVM_SERVICE_H
#define NVM_SERVICE_H

#include <stdint.h>
#include <stdbool.h>
#include "nvmServiceCfg.h"
#include "nvmServiceUnit.h"

typedef enum
{
    NVM_SERVICE_STATUS_OK = 0,
    NVM_SERVICE_STATUS_ERROR,
    NVM_SERVICE_STATUS_BUSY
} NvmService_Status_t;

NvmService_Status_t NvmService_Init(void);
NvmService_Status_t NvmService_Process(void);
NvmService_Status_t NvmService_DeInit(void);

#endif /* NVM_SERVICE_H */
