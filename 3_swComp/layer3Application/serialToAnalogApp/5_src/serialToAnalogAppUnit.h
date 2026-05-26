#ifndef SERIAL_TO_ANALOG_APPUNIT_H
#define SERIAL_TO_ANALOG_APPUNIT_H
#include <stdint.h>
#include <stdbool.h>
#include "serialToAnalogAppCfg.h"

//============================================================================
// Configuration Macros
//============================================================================
#define SERIAL_TO_ANALOG_CFG_MAX_CHANNELS      8U

//============================================================================
// Type Definitions
//============================================================================
typedef enum
{
    SERIAL_TO_ANALOG_APP_STATUS_OK = 0,
    SERIAL_TO_ANALOG_APP_STATUS_ERROR,
    SERIAL_TO_ANALOG_APP_STATUS_INVALID_PARAM,
    SERIAL_TO_ANALOG_APP_STATUS_NOT_INITIALIZED
} SerialToAnalogApp_Status_t;

//============================================================================
// Public Functions - Typed API (no DID/RID awareness)
//============================================================================
SerialToAnalogApp_Status_t SerialToAnalogApp_Init(void);
SerialToAnalogApp_Status_t SerialToAnalogApp_DeInit(void);

/* Read a single ADC conversion from the specified channel */
SerialToAnalogApp_Status_t SerialToAnalogApp_ReadAdc(uint8_t channel, uint16_t *pRawValue);

#endif /* SERIAL_TO_ANALOG_APPUNIT_H */