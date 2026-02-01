// I2cSlaveDriver - Public Interface
#ifndef I2C_SLAVEDRIVER_H
#define I2C_SLAVEDRIVER_H
#include <stdint.h>
#include <stdbool.h>
#include "i2cSlaveDriverCfg.h"
#include "i2cSlaveDriverUnit.h"
typedef enum
{
    I2C_SLAVE_STATUS_OK = 0,
    I2C_SLAVE_STATUS_ERROR,
    I2C_SLAVE_STATUS_BUSY
} I2cSlaveDriver_Status_t;
I2cSlaveDriver_Status_t I2cSlaveDriver_Init(void);
I2cSlaveDriver_Status_t I2cSlaveDriver_DeInit(void);
#endif /* I2C_SLAVEDRIVER_H */
