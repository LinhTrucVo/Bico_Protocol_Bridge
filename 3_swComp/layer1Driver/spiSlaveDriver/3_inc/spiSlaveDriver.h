// SpiSlaveDriver - Public Interface
#ifndef SPI_SLAVEDRIVER_H
#define SPI_SLAVEDRIVER_H
#include <stdint.h>
#include <stdbool.h>
#include "spiSlaveDriverCfg.h"
#include "spiSlaveDriverUnit.h"
typedef enum
{
    SPI_SLAVE_STATUS_OK = 0,
    SPI_SLAVE_STATUS_ERROR,
    SPI_SLAVE_STATUS_BUSY
} SpiSlaveDriver_Status_t;
SpiSlaveDriver_Status_t SpiSlaveDriver_Init(void);
SpiSlaveDriver_Status_t SpiSlaveDriver_DeInit(void);
#endif /* SPI_SLAVEDRIVER_H */
