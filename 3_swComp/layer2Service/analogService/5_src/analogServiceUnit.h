#ifndef ANALOGSERVICEUNIT_H
#define ANALOGSERVICEUNIT_H
#include <stdint.h>
#include <stdbool.h>
#include "analogServiceCfg.h"

//============================================================================
// Configuration Macros
//============================================================================
#define ANALOG_SERVICE_CFG_MAX_CHANNELS      8U

//============================================================================
// Type Definitions
//============================================================================
typedef enum
{
    ANALOGSERVICE_STATUS_OK = 0,
    ANALOGSERVICE_STATUS_ERROR,
    ANALOGSERVICE_STATUS_INVALID_PARAM,
    ANALOGSERVICE_STATUS_NOT_INITIALIZED
} AnalogService_Status_t;

//============================================================================
// Public Functions - Typed API (no DID/RID awareness)
//============================================================================
AnalogService_Status_t AnalogServiceUnit_Init(void);
AnalogService_Status_t AnalogServiceUnit_DeInit(void);

/* Read a single ADC conversion from the specified channel */
AnalogService_Status_t AnalogServiceUnit_ReadAdc(uint8_t channel, uint16_t *pRawValue);

#endif /* ANALOGSERVICEUNIT_H */