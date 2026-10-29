#ifndef BPB_SPI_SLAVEDRIVERUNIT_H
#define BPB_SPI_SLAVEDRIVERUNIT_H

//============================================================================
// Dependencies
//============================================================================
#include <stdint.h>
#include <stdbool.h>
#include "spiSlaveDriverCfg.h"

//============================================================================
// Configuration Macros
//============================================================================
#define BPB_SPI_SLAVE_CFG_DEFAULT_MODE     0
#define BPB_SPI_SLAVE_CFG_DEFAULT_BITORDER 0
#define BPB_SPI_SLAVE_CFG_MAX_BUFFER       512
#define BPB_SPI_SLAVE_MAX_BUFFER           512

//============================================================================
// Status Enums
//============================================================================
#define BPB_SPI_SLAVE_STATUS_OK            BPB_SPISLAVEDRIVERSTATUS_OK
#define BPB_SPI_SLAVE_STATUS_ERROR         BPB_SPISLAVEDRIVERSTATUS_ERROR
#define BPB_SPI_SLAVE_STATUS_BUSY          BPB_SPISLAVEDRIVERSTATUS_BUSY
#define BPB_SPI_SLAVE_STATUS_INVALID_PARAM BPB_SPISLAVEDRIVERSTATUS_INVALID_PARAM
#define BPB_SPI_SLAVE_STATUS_NOT_INITIALIZED BPB_SPISLAVEDRIVERSTATUS_NOT_INITIALIZED

//============================================================================
// Public Types
//============================================================================
typedef enum
{
    BPB_SPISLAVEDRIVERSTATUS_OK = 0,
    BPB_SPISLAVEDRIVERSTATUS_ERROR,
    BPB_SPISLAVEDRIVERSTATUS_BUSY,
    BPB_SPISLAVEDRIVERSTATUS_INVALID_PARAM,
    BPB_SPISLAVEDRIVERSTATUS_NOT_INITIALIZED
} SpiSlaveDriver_Status_t;

typedef enum
{
    BPB_SPI_SLAVE_MODE_0 = 0,
    BPB_SPI_SLAVE_MODE_1,
    BPB_SPI_SLAVE_MODE_2,
    BPB_SPI_SLAVE_MODE_3
} SpiSlaveDriver_Mode_t;

typedef enum
{
    BPB_SPI_SLAVE_BITORDER_MSB_FIRST = 0,
    BPB_SPI_SLAVE_BITORDER_LSB_FIRST
} SpiSlaveDriver_BitOrder_t;

typedef struct
{
    SpiSlaveDriver_Mode_t mode;
    SpiSlaveDriver_BitOrder_t bitOrder;
    bool dmaEnabled;
    bool interruptEnabled;
} SpiSlaveDriver_Config_t;

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

#endif /* BPB_SPI_SLAVEDRIVERUNIT_H */
