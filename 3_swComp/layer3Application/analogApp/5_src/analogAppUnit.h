#ifndef ANALOG_APPUNIT_H
#define ANALOG_APPUNIT_H
#include <stdint.h>
#include <stdbool.h>
#include "ANALOGAPPCfg.h"

//============================================================================
// Configuration Macros
//============================================================================
#define SERIAL_TO_ANALOG_CFG_MAX_CHANNELS      8U

//============================================================================
// Type Definitions
//============================================================================
typedef enum
{
    ANALOG_APP_STATUS_OK = 0,
    ANALOG_APP_STATUS_ERROR,
    ANALOG_APP_STATUS_INVALID_PARAM,
    ANALOG_APP_STATUS_NOT_INITIALIZED
} ANALOGAPP_Status_t;

//============================================================================
// Public Functions - Typed API (no DID/RID awareness)
//============================================================================
ANALOGAPP_Status_t ANALOGAPP_Init(void);
ANALOGAPP_Status_t ANALOGAPP_DeInit(void);

/* Read a single ADC conversion from the specified channel */
ANALOGAPP_Status_t ANALOGAPP_ReadAdc(uint8_t channel, uint16_t *pRawValue);

#endif /* ANALOG_APPUNIT_H */