#ifndef SPI_MASTERDRIVERUNIT_H
#define SPI_MASTERDRIVERUNIT_H

//============================================================================
// Dependencies
//============================================================================
#include <stdint.h>
#include <stdbool.h>
#include "spiMasterDriverCfg.h"

//============================================================================
// Forward declarations (types defined in spiMasterDriver.h)
//============================================================================
typedef struct SpiMasterDriver_Config_t SpiMasterDriver_Config_t;
typedef enum SpiMasterDriver_Status_t SpiMasterDriver_Status_t;
typedef enum SpiMasterDriver_Mode_t SpiMasterDriver_Mode_t;
typedef enum SpiMasterDriver_BitOrder_t SpiMasterDriver_BitOrder_t;
typedef uint8_t SpiMasterDriver_ChipSelect_t;
typedef void (*SpiMasterDriver_Callback_t)(SpiMasterDriver_Status_t status);

//============================================================================
// Public Functions
//============================================================================
SpiMasterDriver_Status_t SpiMasterDriverUnit_Init(const SpiMasterDriver_Config_t *pConfig);
SpiMasterDriver_Status_t SpiMasterDriverUnit_Configure(uint32_t clockSpeed, SpiMasterDriver_Mode_t mode, SpiMasterDriver_BitOrder_t bitOrder);
SpiMasterDriver_Status_t SpiMasterDriverUnit_SelectChip(SpiMasterDriver_ChipSelect_t cs);
SpiMasterDriver_Status_t SpiMasterDriverUnit_DeselectChip(SpiMasterDriver_ChipSelect_t cs);
SpiMasterDriver_Status_t SpiMasterDriverUnit_Transmit(const uint8_t *pData, uint16_t length);
SpiMasterDriver_Status_t SpiMasterDriverUnit_Receive(uint8_t *pData, uint16_t length);
SpiMasterDriver_Status_t SpiMasterDriverUnit_TransmitReceive(const uint8_t *pTxData, uint8_t *pRxData, uint16_t length);
SpiMasterDriver_Status_t SpiMasterDriverUnit_TransmitWithTimeout(const uint8_t *pData, uint16_t length, uint32_t timeoutMs);
SpiMasterDriver_Status_t SpiMasterDriverUnit_IsBusy(bool *pIsBusy);
SpiMasterDriver_Status_t SpiMasterDriverUnit_RegisterCallback(SpiMasterDriver_Callback_t callback);
SpiMasterDriver_Status_t SpiMasterDriverUnit_DeInit(void);

#endif /* SPI_MASTERDRIVERUNIT_H */
