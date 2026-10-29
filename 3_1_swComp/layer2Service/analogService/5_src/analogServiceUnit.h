#ifndef BPB_ANALOGSERVICEUNIT_H
#define BPB_ANALOGSERVICEUNIT_H
#include <stdint.h>
#include <stdbool.h>
#include "analogServiceCfg.h"

//============================================================================
// Configuration Macros
//============================================================================
#define BPB_ANALOG_SERVICE_CFG_MAX_CHANNELS      8U

//============================================================================
// Type Definitions
//============================================================================
typedef enum
{
    BPB_ANALOGSERVICE_STATUS_OK = 0,
    BPB_ANALOGSERVICE_STATUS_ERROR,
    BPB_ANALOGSERVICE_STATUS_INVALID_PARAM,
    BPB_ANALOGSERVICE_STATUS_NOT_INITIALIZED
} AnalogService_Status_t;

//============================================================================
// Public Functions - Typed API (no DID/RID awareness)
//============================================================================
AnalogService_Status_t AnalogServiceUnit_Init(void);
AnalogService_Status_t AnalogServiceUnit_DeInit(void);

/* Read a single ADC conversion from the specified channel */
AnalogService_Status_t AnalogServiceUnit_ReadAdc(uint8_t channel, uint16_t *pRawValue);

#endif /* BPB_ANALOGSERVICEUNIT_H */