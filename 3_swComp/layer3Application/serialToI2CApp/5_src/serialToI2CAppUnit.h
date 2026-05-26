#ifndef SERIAL_TO_I2C_APPUNIT_H
#define SERIAL_TO_I2C_APPUNIT_H
#include <stdint.h>
#include <stdbool.h>
#include "serialToI2CAppCfg.h"

//============================================================================
// Configuration Macros
//============================================================================
#define SERIAL_TO_I2C_CFG_MAX_TRANSFER     256U

//============================================================================
// Type Definitions
//============================================================================
typedef enum
{
    SERIAL_TO_I2C_APP_STATUS_OK = 0,
    SERIAL_TO_I2C_APP_STATUS_ERROR,
    SERIAL_TO_I2C_APP_STATUS_INVALID_PARAM,
    SERIAL_TO_I2C_APP_STATUS_NOT_INITIALIZED,
    SERIAL_TO_I2C_APP_STATUS_NACK,
    SERIAL_TO_I2C_APP_STATUS_BUS_ERROR
} SerialToI2CApp_Status_t;

//============================================================================
// Public Functions - Typed API (no DID/RID awareness)
//============================================================================
SerialToI2CApp_Status_t SerialToI2CApp_Init(void);
SerialToI2CApp_Status_t SerialToI2CApp_DeInit(void);

/* I2C Write: send data to target address */
SerialToI2CApp_Status_t SerialToI2CApp_Write(uint16_t address, const uint8_t *pData, uint16_t length);

/* I2C Read: read data from target address */
SerialToI2CApp_Status_t SerialToI2CApp_Read(uint16_t address, uint8_t *pData, uint16_t length);

#endif /* SERIAL_TO_I2C_APPUNIT_H */