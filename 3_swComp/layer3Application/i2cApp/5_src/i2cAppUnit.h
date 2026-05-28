#ifndef I2C_APPUNIT_H
#define I2C_APPUNIT_H
#include <stdint.h>
#include <stdbool.h>
#include "I2CAPPCfg.h"

//============================================================================
// Configuration Macros
//============================================================================
#define SERIAL_TO_I2C_CFG_MAX_TRANSFER     256U

//============================================================================
// Type Definitions
//============================================================================
typedef enum
{
    I2C_APP_STATUS_OK = 0,
    I2C_APP_STATUS_ERROR,
    I2C_APP_STATUS_INVALID_PARAM,
    I2C_APP_STATUS_NOT_INITIALIZED,
    I2C_APP_STATUS_NACK,
    I2C_APP_STATUS_BUS_ERROR
} I2CAPP_Status_t;

//============================================================================
// Public Functions - Typed API (no DID/RID awareness)
//============================================================================
I2CAPP_Status_t I2CAPP_Init(void);
I2CAPP_Status_t I2CAPP_DeInit(void);

/* I2C Write: send data to target address */
I2CAPP_Status_t I2CAPP_Write(uint16_t address, const uint8_t *pData, uint16_t length);

/* I2C Read: read data from target address */
I2CAPP_Status_t I2CAPP_Read(uint16_t address, uint8_t *pData, uint16_t length);

#endif /* I2C_APPUNIT_H */