// SerialToDigitalApp - Public Interface

#ifndef SERIAL_TO_DIGITAL_APP_H
#define SERIAL_TO_DIGITAL_APP_H

#include <stdint.h>
#include <stdbool.h>
#include "serialToDigitalAppCfg.h"
#include "serialToDigitalAppUnit.h"

typedef enum
{
    SERIAL_TO_DIGITAL_APP_STATUS_OK = 0,
    SERIAL_TO_DIGITAL_APP_STATUS_ERROR,
    SERIAL_TO_DIGITAL_APP_STATUS_BUSY
} SerialToDigitalApp_Status_t;

typedef enum
{
    SerialToDigitalApp_STATE_IDLE = 0,
    SerialToDigitalApp_STATE_PROCESSING,
    SerialToDigitalApp_STATE_ERROR
} SerialToDigitalApp_State_t;

SerialToDigitalApp_Status_t SerialToDigitalApp_Init(void);
SerialToDigitalApp_Status_t SerialToDigitalApp_Run(void);
SerialToDigitalApp_Status_t SerialToDigitalApp_GetState(SerialToDigitalApp_State_t *pState);
SerialToDigitalApp_Status_t SerialToDigitalApp_DeInit(void);

#endif /* SERIAL_TO_DIGITAL_APP_H */
