// Serial Driver Component - Public Interface

#ifndef SERIALDRIVER_H
#define SERIALDRIVER_H

//============================================================================
// Dependencies
//============================================================================
#include <stdint.h>
#include <stdbool.h>
#include "serialDriverCfg.h"
#include "serialDriverUnit.h"

//============================================================================
// Public Macros
//============================================================================
#define SERIAL_MAX_BUFFER_SIZE    256

//============================================================================
// Public Types
//============================================================================
typedef enum
{
    SERIAL_STATUS_OK = 0,
    SERIAL_STATUS_ERROR,
    SERIAL_STATUS_BUSY,
    SERIAL_STATUS_TIMEOUT
} SerialDriver_Status_t;

typedef enum
{
    SERIAL_BAUDRATE_9600 = 9600,
    SERIAL_BAUDRATE_115200 = 115200
} SerialDriver_Baudrate_t;

//============================================================================
// Public Functions
//============================================================================
SerialDriver_Status_t SerialDriver_Init(SerialDriver_Baudrate_t baudrate);
SerialDriver_Status_t SerialDriver_Send(const uint8_t *pData, uint16_t length);
SerialDriver_Status_t SerialDriver_Receive(uint8_t *pData, uint16_t length, uint16_t *pReceivedLength);
SerialDriver_Status_t SerialDriver_DeInit(void);

#endif /* SERIALDRIVER_H */
