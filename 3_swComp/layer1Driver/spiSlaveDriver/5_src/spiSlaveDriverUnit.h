#ifndef SPI_SLAVEDRIVERUNIT_H
#define SPI_SLAVEDRIVERUNIT_H

//============================================================================
// Dependencies
//============================================================================
#include <stdint.h>
#include <stdbool.h>
#include "spiSlaveDriverCfg.h"

//============================================================================
// Forward declarations (types defined in spiSlaveDriver.h)
//============================================================================
typedef struct SpiSlaveDriver_Config_t SpiSlaveDriver_Config_t;
typedef enum SpiSlaveDriver_Status_t SpiSlaveDriver_Status_t;
typedef void (*SpiSlaveDriver_RxCallback_t)(const uint8_t *pData, uint16_t length);
typedef void (*SpiSlaveDriver_TxCallback_t)(uint8_t *pData, uint16_t *pLength);

//============================================================================
// Public Functions
//============================================================================
SpiSlaveDriver_Status_t SpiSlaveDriverUnit_Init(const SpiSlaveDriver_Config_t *pConfig);
SpiSlaveDriver_Status_t SpiSlaveDriverUnit_SetTxBuffer(const uint8_t *pData, uint16_t length);
SpiSlaveDriver_Status_t SpiSlaveDriverUnit_SetRxBuffer(uint8_t *pData, uint16_t maxLength);
SpiSlaveDriver_Status_t SpiSlaveDriverUnit_GetRxLength(uint16_t *pLength);
SpiSlaveDriver_Status_t SpiSlaveDriverUnit_IsSelected(bool *pIsSelected);
SpiSlaveDriver_Status_t SpiSlaveDriverUnit_RegisterRxCallback(SpiSlaveDriver_RxCallback_t callback);
SpiSlaveDriver_Status_t SpiSlaveDriverUnit_RegisterTxCallback(SpiSlaveDriver_TxCallback_t callback);
SpiSlaveDriver_Status_t SpiSlaveDriverUnit_DeInit(void);

#endif /* SPI_SLAVEDRIVERUNIT_H */
