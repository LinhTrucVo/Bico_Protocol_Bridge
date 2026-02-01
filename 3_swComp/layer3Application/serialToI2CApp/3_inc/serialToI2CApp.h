// SerialToI2CApp - Public Interface

#ifndef SERIAL_TO_I2C_APP_H
#define SERIAL_TO_I2C_APP_H

#include <stdint.h>
#include <stdbool.h>
#include "serialToI2CAppCfg.h"
#include "serialToI2CAppUnit.h"

typedef enum
{
    SERIAL_TO_I2C_APP_STATUS_OK = 0,
    SERIAL_TO_I2C_APP_STATUS_ERROR,
    SERIAL_TO_I2C_APP_STATUS_BUSY
} SerialToI2CApp_Status_t;

typedef enum
{
    SerialToI2CApp_STATE_IDLE = 0,
    SerialToI2CApp_STATE_PROCESSING,
    SerialToI2CApp_STATE_ERROR
} SerialToI2CApp_State_t;

SerialToI2CApp_Status_t SerialToI2CApp_Init(void);
SerialToI2CApp_Status_t SerialToI2CApp_Run(void);
SerialToI2CApp_Status_t SerialToI2CApp_GetState(SerialToI2CApp_State_t *pState);
SerialToI2CApp_Status_t SerialToI2CApp_DeInit(void);

#endif /* SERIAL_TO_I2C_APP_H */
