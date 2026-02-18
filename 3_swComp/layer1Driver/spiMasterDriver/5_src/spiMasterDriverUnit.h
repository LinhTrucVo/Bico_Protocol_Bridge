#ifndef SPI_MASTERDRIVERUNIT_H
#define SPI_MASTERDRIVERUNIT_H

//============================================================================
// Dependencies
//============================================================================
#include <stdint.h>
#include <stdbool.h>
#include "spiMasterDriverCfg.h"

//============================================================================
// Configuration Macros
//============================================================================
#define SPI_MASTER_CFG_DEFAULT_SPEED    1000000
#define SPI_MASTER_CFG_DEFAULT_MODE     0
#define SPI_MASTER_CFG_DEFAULT_BITORDER 0
#define SPI_MASTER_CFG_MAX_TRANSFER     1024
#define SPI_MAX_TRANSFER_SIZE           256

//============================================================================
// Status Enums
//============================================================================
#define SPI_MASTER_STATUS_OK           SPIMASTERDRIVERSTATUS_OK
#define SPI_MASTER_STATUS_ERROR        SPIMASTERDRIVERSTATUS_ERROR
#define SPI_MASTER_STATUS_BUSY         SPIMASTERDRIVERSTATUS_BUSY
#define SPI_MASTER_STATUS_TIMEOUT      SPIMASTERDRIVERSTATUS_TIMEOUT
#define SPI_MASTER_STATUS_INVALID_PARAM SPIMASTERDRIVERSTATUS_INVALID_PARAM
#define SPI_MASTER_STATUS_NOT_INITIALIZED SPIMASTERDRIVERSTATUS_NOT_INITIALIZED

//============================================================================
// Public Types
//============================================================================
typedef enum
{
    SPIMASTERDRIVERSTATUS_OK = 0,
    SPIMASTERDRIVERSTATUS_ERROR,
    SPIMASTERDRIVERSTATUS_BUSY,
    SPIMASTERDRIVERSTATUS_TIMEOUT,
    SPIMASTERDRIVERSTATUS_INVALID_PARAM,
    SPIMASTERDRIVERSTATUS_NOT_INITIALIZED
} SpiMasterDriver_Status_t;

typedef enum
{
    SPI_MODE_0 = 0,
    SPI_MODE_1,
    SPI_MODE_2,
    SPI_MODE_3
} SpiMasterDriver_Mode_t;

typedef enum
{
    SPI_BITORDER_MSB_FIRST = 0,
    SPI_BITORDER_LSB_FIRST
} SpiMasterDriver_BitOrder_t;

typedef enum
{
    SPI_DATASIZE_8BIT = 8,
    SPI_DATASIZE_16BIT = 16
} SpiMasterDriver_DataSize_t;

typedef enum
{
    SPI_CS_MODE_MANUAL = 0,
    SPI_CS_MODE_AUTO
} SpiMasterDriver_CSMode_t;

typedef struct
{
    uint32_t clockSpeed;
    SpiMasterDriver_Mode_t mode;
    SpiMasterDriver_BitOrder_t bitOrder;
    SpiMasterDriver_DataSize_t dataSize;
    SpiMasterDriver_CSMode_t csMode;
    bool dmaEnabled;
    bool interruptEnabled;
} SpiMasterDriver_Config_t;

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
