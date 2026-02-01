// I2C Master Driver - Public Interface

#ifndef I2CMASTERDRIVER_H
#define I2CMASTERDRIVER_H

#include <stdint.h>
#include <stdbool.h>
#include "i2cMasterDriverCfg.h"
#include "i2cMasterDriverUnit.h"

#define I2C_MAX_TRANSFER_SIZE    256

typedef enum
{
    I2C_MASTER_STATUS_OK = 0,
    I2C_MASTER_STATUS_ERROR,
    I2C_MASTER_STATUS_BUSY,
    I2C_MASTER_STATUS_TIMEOUT,
    I2C_MASTER_STATUS_NACK
} I2cMasterDriver_Status_t;

typedef uint8_t I2cMasterDriver_Address_t;

I2cMasterDriver_Status_t I2cMasterDriver_Init(void);
I2cMasterDriver_Status_t I2cMasterDriver_Write(I2cMasterDriver_Address_t address, const uint8_t *pData, uint16_t length);
I2cMasterDriver_Status_t I2cMasterDriver_Read(I2cMasterDriver_Address_t address, uint8_t *pData, uint16_t length);
I2cMasterDriver_Status_t I2cMasterDriver_WriteRead(I2cMasterDriver_Address_t address, const uint8_t *pWriteData, uint16_t writeLength, uint8_t *pReadData, uint16_t readLength);
I2cMasterDriver_Status_t I2cMasterDriver_DeInit(void);

#endif /* I2CMASTERDRIVER_H */
