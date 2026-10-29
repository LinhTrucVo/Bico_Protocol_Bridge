#ifndef BPB_I2CSERVICEUNIT_H
#define BPB_I2CSERVICEUNIT_H
#include <stdint.h>
#include <stdbool.h>
#include "i2cServiceCfg.h"

//============================================================================
// Configuration Macros
//============================================================================
#define BPB_I2C_SERVICE_CFG_MAX_TRANSFER     256U

//============================================================================
// Type Definitions
//============================================================================
typedef enum
{
    BPB_I2CSERVICE_STATUS_OK = 0,
    BPB_I2CSERVICE_STATUS_ERROR,
    BPB_I2CSERVICE_STATUS_INVALID_PARAM,
    BPB_I2CSERVICE_STATUS_NOT_INITIALIZED,
    BPB_I2CSERVICE_STATUS_NACK,
    BPB_I2CSERVICE_STATUS_BUS_ERROR
} I2cService_Status_t;

//============================================================================
// Public Functions - Typed API (no DID/RID awareness)
//============================================================================
I2cService_Status_t I2cServiceUnit_Init(void);
I2cService_Status_t I2cServiceUnit_DeInit(void);

/* I2C Write: send data to target address */
I2cService_Status_t I2cServiceUnit_Write(uint16_t address, const uint8_t *pData, uint16_t length);

/* I2C Read: read data from target address */
I2cService_Status_t I2cServiceUnit_Read(uint16_t address, uint8_t *pData, uint16_t length);

#endif /* BPB_I2CSERVICEUNIT_H */