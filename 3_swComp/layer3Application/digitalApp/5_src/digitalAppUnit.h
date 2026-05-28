#ifndef DIGITAL_APPUNIT_H
#define DIGITAL_APPUNIT_H
#include <stdint.h>
#include <stdbool.h>
#include "DIGITALAPPCfg.h"

//============================================================================
// Configuration Macros
//============================================================================
#define SERIAL_TO_DIGITAL_CFG_MAX_PINS        32U
#define SERIAL_TO_DIGITAL_CFG_MAX_PWM_CH      8U

//============================================================================
// Type Definitions
//============================================================================
typedef enum
{
    DIGITAL_APP_STATUS_OK = 0,
    DIGITAL_APP_STATUS_ERROR,
    DIGITAL_APP_STATUS_INVALID_PARAM,
    DIGITAL_APP_STATUS_NOT_INITIALIZED
} DIGITALAPP_Status_t;

//============================================================================
// Public Functions - Typed API (no DID/RID awareness)
//============================================================================
DIGITALAPP_Status_t DIGITALAPP_Init(void);
DIGITALAPP_Status_t DIGITALAPP_DeInit(void);

/* GPIO operations */
DIGITALAPP_Status_t DIGITALAPP_WriteGpio(uint8_t pin, uint8_t state);
DIGITALAPP_Status_t DIGITALAPP_ReadGpio(uint8_t pin, uint8_t *pState);

/* PWM operations */
DIGITALAPP_Status_t DIGITALAPP_StartPwm(uint8_t channel);
DIGITALAPP_Status_t DIGITALAPP_StopPwm(uint8_t channel);

#endif /* DIGITAL_APPUNIT_H */