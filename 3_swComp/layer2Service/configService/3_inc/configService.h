// ConfigService - Public Interface

#ifndef CONFIG_SERVICE_H
#define CONFIG_SERVICE_H

#include <stdint.h>
#include <stdbool.h>
#include "configServiceCfg.h"
#include "configServiceUnit.h"

typedef enum
{
    CONFIG_SERVICE_STATUS_OK = 0,
    CONFIG_SERVICE_STATUS_ERROR,
    CONFIG_SERVICE_STATUS_BUSY
} ConfigService_Status_t;

ConfigService_Status_t ConfigService_Init(void);
ConfigService_Status_t ConfigService_Process(void);
ConfigService_Status_t ConfigService_DeInit(void);

#endif /* CONFIG_SERVICE_H */
