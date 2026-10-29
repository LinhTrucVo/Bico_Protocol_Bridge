#ifndef BPB_DIGITALSERVICEUNIT_H
#define BPB_DIGITALSERVICEUNIT_H
#include <stdint.h>
#include <stdbool.h>
#include "digitalServiceCfg.h"

//============================================================================
// Configuration Macros
//============================================================================
#define BPB_DIGITAL_SERVICE_CFG_MAX_PINS        32U
#define BPB_DIGITAL_SERVICE_CFG_MAX_PWM_CH      8U

//============================================================================
// Type Definitions
//============================================================================
typedef enum
{
    BPB_DIGITALSERVICE_STATUS_OK = 0,
    BPB_DIGITALSERVICE_STATUS_ERROR,
    BPB_DIGITALSERVICE_STATUS_INVALID_PARAM,
    BPB_DIGITALSERVICE_STATUS_NOT_INITIALIZED
} DigitalService_Status_t;

//============================================================================
// Public Functions - Typed API (no DID/RID awareness)
//============================================================================
DigitalService_Status_t DigitalServiceUnit_Init(void);
DigitalService_Status_t DigitalServiceUnit_DeInit(void);

/* GPIO operations */
DigitalService_Status_t DigitalServiceUnit_WriteGpio(uint8_t pin, uint8_t state);
DigitalService_Status_t DigitalServiceUnit_ReadGpio(uint8_t pin, uint8_t *pState);

/* PWM operations */
DigitalService_Status_t DigitalServiceUnit_StartPwm(uint8_t channel);
DigitalService_Status_t DigitalServiceUnit_StopPwm(uint8_t channel);

#endif /* BPB_DIGITALSERVICEUNIT_H */