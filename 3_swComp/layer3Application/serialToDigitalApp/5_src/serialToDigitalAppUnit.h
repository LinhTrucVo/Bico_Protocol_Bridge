#ifndef SERIAL_TO_DIGITAL_APPUNIT_H
#define SERIAL_TO_DIGITAL_APPUNIT_H
#include <stdint.h>
#include <stdbool.h>
#include "serialToDigitalAppCfg.h"

//============================================================================
// Configuration Macros
//============================================================================
#define SERIAL_TO_DIGITAL_CFG_MAX_PINS        32
#define SERIAL_TO_DIGITAL_CFG_MAX_PWM_CH      8
#define SERIAL_TO_DIGITAL_CFG_DEFAULT_PWM_HZ  1000
#define SERIAL_TO_DIGITAL_CFG_DEFAULT_DUTY    5000

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

typedef enum
{
    SerialToDigitalApp_STATE_IDLE = 0,
    SerialToDigitalApp_STATE_PROCESSING,
    SerialToDigitalApp_STATE_ERROR
} SerialToDigitalApp_State_t;

typedef enum
{
    SERIAL_TO_DIGITAL_DIR_INPUT  = 0,
    SERIAL_TO_DIGITAL_DIR_OUTPUT = 1
} SerialToDigitalApp_Direction_t;

typedef enum
{
    SERIAL_TO_DIGITAL_STATE_LOW  = 0,
    SERIAL_TO_DIGITAL_STATE_HIGH = 1
} SerialToDigitalApp_StateValue_t;

typedef struct
{
    uint8_t  pinId;
    SerialToDigitalApp_Direction_t   direction;
    SerialToDigitalApp_StateValue_t  initialState;
    bool     enablePullup;
} SerialToDigitalApp_PinConfig_t;

typedef struct
{
    uint8_t  channelId;
    uint32_t frequency;
    uint16_t dutyCycle;
    bool     enable;
} SerialToDigitalApp_PwmConfig_t;

//============================================================================
// Public Functions
//============================================================================
SerialToDigitalApp_Status_t SerialToDigitalAppUnit_Init(void);
SerialToDigitalApp_Status_t SerialToDigitalAppUnit_DeInit(void);
SerialToDigitalApp_Status_t SerialToDigitalAppUnit_Run(void);
SerialToDigitalApp_Status_t SerialToDigitalAppUnit_ProcessFrame(const uint8_t *pFrame, uint16_t frameLength, uint8_t *pResponse, uint16_t *pResponseLength);

//============================================================================
// Backward Compatibility Macros
//============================================================================
#define SerialToDigitalAppUnit_Init           SerialToDigitalApp_Init
#define SerialToDigitalAppUnit_DeInit         SerialToDigitalApp_DeInit
#define SerialToDigitalAppUnit_Run            SerialToDigitalApp_Run
#define SerialToDigitalAppUnit_ProcessFrame   SerialToDigitalApp_ProcessFrame

#endif /* SERIAL_TO_DIGITAL_APPUNIT_H */
