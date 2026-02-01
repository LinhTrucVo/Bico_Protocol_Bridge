// DataConversionService - Public Interface

#ifndef DATA_CONVERSION_SERVICE_H
#define DATA_CONVERSION_SERVICE_H

#include <stdint.h>
#include <stdbool.h>
#include "dataConversionServiceCfg.h"
#include "dataConversionServiceUnit.h"

typedef enum
{
    DATA_CONVERSION_SERVICE_STATUS_OK = 0,
    DATA_CONVERSION_SERVICE_STATUS_ERROR,
    DATA_CONVERSION_SERVICE_STATUS_BUSY
} DataConversionService_Status_t;

DataConversionService_Status_t DataConversionService_Init(void);
DataConversionService_Status_t DataConversionService_Process(void);
DataConversionService_Status_t DataConversionService_DeInit(void);

#endif /* DATA_CONVERSION_SERVICE_H */
