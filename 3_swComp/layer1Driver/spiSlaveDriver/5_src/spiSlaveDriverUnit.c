// SpiSlaveDriver Implementation
#include "spiSlaveDriver.h"
typedef struct
{
    uint8_t initialized;
} SpiSlaveDriver_Context_t;
static SpiSlaveDriver_Context_t context = {0};
SpiSlaveDriver_Status_t SpiSlaveDriver_Init(void)
{
    // TODO: Add vendor-specific HAL initialization here
    context.initialized = 1;
    return SPI_SLAVE_STATUS_OK;
}
SpiSlaveDriver_Status_t SpiSlaveDriver_DeInit(void)
{
    // TODO: Add vendor-specific HAL deinitialization here
    context.initialized = 0;
    return SPI_SLAVE_STATUS_OK;
}
