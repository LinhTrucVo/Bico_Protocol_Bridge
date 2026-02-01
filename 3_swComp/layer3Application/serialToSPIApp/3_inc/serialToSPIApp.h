// SerialToSPIApp - Public Interface

#ifndef SERIAL_TO_SPI_APP_H
#define SERIAL_TO_SPI_APP_H

#include <stdint.h>
#include <stdbool.h>
#include "serialToSPIAppCfg.h"
#include "serialToSPIAppUnit.h"

typedef enum
{
    SERIAL_TO_SPI_APP_STATUS_OK = 0,
    SERIAL_TO_SPI_APP_STATUS_ERROR,
    SERIAL_TO_SPI_APP_STATUS_BUSY
} SerialToSPIApp_Status_t;

typedef enum
{
    SerialToSPIApp_STATE_IDLE = 0,
    SerialToSPIApp_STATE_PROCESSING,
    SerialToSPIApp_STATE_ERROR
} SerialToSPIApp_State_t;

SerialToSPIApp_Status_t SerialToSPIApp_Init(void);
SerialToSPIApp_Status_t SerialToSPIApp_Run(void);
SerialToSPIApp_Status_t SerialToSPIApp_GetState(SerialToSPIApp_State_t *pState);
SerialToSPIApp_Status_t SerialToSPIApp_DeInit(void);

#endif /* SERIAL_TO_SPI_APP_H */
