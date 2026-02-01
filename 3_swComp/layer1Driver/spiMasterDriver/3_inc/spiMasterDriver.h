// SpiMasterDriver - Public Interface
#ifndef SPI_MASTERDRIVER_H
#define SPI_MASTERDRIVER_H
#include <stdint.h>
#include <stdbool.h>
#include "spiMasterDriverCfg.h"
#include "spiMasterDriverUnit.h"
typedef enum
{
    SPI_MASTER_STATUS_OK = 0,
    SPI_MASTER_STATUS_ERROR,
    SPI_MASTER_STATUS_BUSY
} SpiMasterDriver_Status_t;
SpiMasterDriver_Status_t SpiMasterDriver_Init(void);
SpiMasterDriver_Status_t SpiMasterDriver_DeInit(void);
#endif /* SPI_MASTERDRIVER_H */
