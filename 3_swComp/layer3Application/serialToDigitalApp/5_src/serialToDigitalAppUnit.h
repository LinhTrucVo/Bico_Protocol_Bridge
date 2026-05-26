#ifndef SERIAL_TO_DIGITAL_APPUNIT_H
#define SERIAL_TO_DIGITAL_APPUNIT_H
#include <stdint.h>
#include <stdbool.h>
#include "serialToDigitalAppCfg.h"

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
    SERIAL_TO_DIGITAL_APP_STATUS_OK = 0,
    SERIAL_TO_DIGITAL_APP_STATUS_ERROR,
    SERIAL_TO_DIGITAL_APP_STATUS_INVALID_PARAM,
    SERIAL_TO_DIGITAL_APP_STATUS_NOT_INITIALIZED
} SerialToDigitalApp_Status_t;

//============================================================================
// Public Functions - Typed API (no DID/RID awareness)
//============================================================================
SerialToDigitalApp_Status_t SerialToDigitalApp_Init(void);
SerialToDigitalApp_Status_t SerialToDigitalApp_DeInit(void);

/* GPIO operations */
SerialToDigitalApp_Status_t SerialToDigitalApp_WriteGpio(uint8_t pin, uint8_t state);
SerialToDigitalApp_Status_t SerialToDigitalApp_ReadGpio(uint8_t pin, uint8_t *pState);

/* PWM operations */
SerialToDigitalApp_Status_t SerialToDigitalApp_StartPwm(uint8_t channel);
SerialToDigitalApp_Status_t SerialToDigitalApp_StopPwm(uint8_t channel);

#endif /* SERIAL_TO_DIGITAL_APPUNIT_H */