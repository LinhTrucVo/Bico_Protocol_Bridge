// SpiMasterDriver Implementation
#include "spiMasterDriver.h"
typedef struct
{
    uint8_t initialized;
} SpiMasterDriver_Context_t;
static SpiMasterDriver_Context_t context = {0};
SpiMasterDriver_Status_t SpiMasterDriver_Init(void)
{
    // TODO: Add vendor-specific HAL initialization here
    context.initialized = 1;
    return SPI_MASTER_STATUS_OK;
}
SpiMasterDriver_Status_t SpiMasterDriver_DeInit(void)
{
    // TODO: Add vendor-specific HAL deinitialization here
    context.initialized = 0;
    return SPI_MASTER_STATUS_OK;
}
