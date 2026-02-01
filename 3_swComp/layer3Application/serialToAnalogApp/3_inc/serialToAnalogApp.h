// SerialToAnalogApp - Public Interface

#ifndef SERIAL_TO_ANALOG_APP_H
#define SERIAL_TO_ANALOG_APP_H

#include <stdint.h>
#include <stdbool.h>
#include "serialToAnalogAppCfg.h"
#include "serialToAnalogAppUnit.h"

typedef enum
{
    SERIAL_TO_ANALOG_APP_STATUS_OK = 0,
    SERIAL_TO_ANALOG_APP_STATUS_ERROR,
    SERIAL_TO_ANALOG_APP_STATUS_BUSY
} SerialToAnalogApp_Status_t;

typedef enum
{
    SerialToAnalogApp_STATE_IDLE = 0,
    SerialToAnalogApp_STATE_PROCESSING,
    SerialToAnalogApp_STATE_ERROR
} SerialToAnalogApp_State_t;

SerialToAnalogApp_Status_t SerialToAnalogApp_Init(void);
SerialToAnalogApp_Status_t SerialToAnalogApp_Run(void);
SerialToAnalogApp_Status_t SerialToAnalogApp_GetState(SerialToAnalogApp_State_t *pState);
SerialToAnalogApp_Status_t SerialToAnalogApp_DeInit(void);

#endif /* SERIAL_TO_ANALOG_APP_H */
