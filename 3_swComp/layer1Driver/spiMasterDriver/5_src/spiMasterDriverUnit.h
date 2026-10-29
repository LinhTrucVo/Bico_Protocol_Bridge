#ifndef BPB_SPI_MASTERDRIVERUNIT_H
#define BPB_SPI_MASTERDRIVERUNIT_H

//============================================================================
// Dependencies
//============================================================================
#include <stdint.h>
#include <stdbool.h>
#include "spiMasterDriverCfg.h"

//============================================================================
// Configuration Macros
//============================================================================
#define BPB_SPI_MASTER_CFG_DEFAULT_SPEED    1000000
#define BPB_SPI_MASTER_CFG_DEFAULT_MODE     0
#define BPB_SPI_MASTER_CFG_DEFAULT_BITORDER 0
#define BPB_SPI_MASTER_CFG_MAX_TRANSFER     1024
#define BPB_SPI_MAX_TRANSFER_SIZE           256

//============================================================================
// Status Enums
//============================================================================
#define BPB_SPI_MASTER_STATUS_OK           BPB_SPIMASTERDRIVERSTATUS_OK
#define BPB_SPI_MASTER_STATUS_ERROR        BPB_SPIMASTERDRIVERSTATUS_ERROR
#define BPB_SPI_MASTER_STATUS_BUSY         BPB_SPIMASTERDRIVERSTATUS_BUSY
#define BPB_SPI_MASTER_STATUS_TIMEOUT      BPB_SPIMASTERDRIVERSTATUS_TIMEOUT
#define BPB_SPI_MASTER_STATUS_INVALID_PARAM BPB_SPIMASTERDRIVERSTATUS_INVALID_PARAM
#define BPB_SPI_MASTER_STATUS_NOT_INITIALIZED BPB_SPIMASTERDRIVERSTATUS_NOT_INITIALIZED

//============================================================================
// Public Types
//============================================================================
typedef enum
{
    BPB_SPIMASTERDRIVERSTATUS_OK = 0,
    BPB_SPIMASTERDRIVERSTATUS_ERROR,
    BPB_SPIMASTERDRIVERSTATUS_BUSY,
    BPB_SPIMASTERDRIVERSTATUS_TIMEOUT,
    BPB_SPIMASTERDRIVERSTATUS_INVALID_PARAM,
    BPB_SPIMASTERDRIVERSTATUS_NOT_INITIALIZED
} SpiMasterDriver_Status_t;

typedef enum
{
    BPB_SPI_MODE_0 = 0,
    BPB_SPI_MODE_1,
    BPB_SPI_MODE_2,
    BPB_SPI_MODE_3
} SpiMasterDriver_Mode_t;

typedef enum
{
    BPB_SPI_BITORDER_MSB_FIRST = 0,
    BPB_SPI_BITORDER_LSB_FIRST
} SpiMasterDriver_BitOrder_t;

typedef enum
{
    BPB_SPI_DATASIZE_8BIT = 8,
    BPB_SPI_DATASIZE_16BIT = 16
} SpiMasterDriver_DataSize_t;

typedef enum
{
    BPB_SPI_CS_MODE_MANUAL = 0,
    BPB_SPI_CS_MODE_AUTO
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

#endif /* BPB_SPI_MASTERDRIVERUNIT_H */
