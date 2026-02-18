#ifndef SERIAL_TO_SPI_APPUNIT_H
#define SERIAL_TO_SPI_APPUNIT_H
#include <stdint.h>
#include <stdbool.h>
#include "serialToSPIAppCfg.h"

//============================================================================
// Configuration Macros
//============================================================================
#define SERIAL_TO_SPI_CFG_DEFAULT_SPEED    1000000
#define SERIAL_TO_SPI_CFG_DEFAULT_MODE     0
#define SERIAL_TO_SPI_CFG_DEFAULT_BITORDER 0
#define SERIAL_TO_SPI_CFG_MAX_TRANSFER     1024

//============================================================================
// Type Definitions
//============================================================================
typedef enum
{
    SERIAL_TO_SPI_APP_STATUS_OK = 0,
    SERIAL_TO_SPI_APP_STATUS_ERROR,
    SERIAL_TO_SPI_APP_STATUS_INVALID_PARAM,
    SERIAL_TO_SPI_APP_STATUS_NOT_INITIALIZED
} SerialToSPIApp_Status_t;

typedef enum
{
    SerialToSPIApp_STATE_IDLE = 0,
    SerialToSPIApp_STATE_BUSY,
    SerialToSPIApp_STATE_ERROR
} SerialToSPIApp_State_t;

typedef enum
{
    SERIAL_TO_SPI_MODE_0 = 0,
    SERIAL_TO_SPI_MODE_1 = 1,
    SERIAL_TO_SPI_MODE_2 = 2,
    SERIAL_TO_SPI_MODE_3 = 3
} SerialToSPIApp_Mode_t;

typedef enum
{
    SERIAL_TO_SPI_BITORDER_MSB_FIRST = 0,
    SERIAL_TO_SPI_BITORDER_LSB_FIRST = 1
} SerialToSPIApp_BitOrder_t;

typedef struct
{
    uint32_t clockSpeed;
    SerialToSPIApp_Mode_t     mode;
    SerialToSPIApp_BitOrder_t bitOrder;
} SerialToSPIApp_Config_t;

typedef struct
{
    const uint8_t *pTxData;
    uint8_t       *pRxData;
    uint16_t       length;
} SerialToSPIApp_Transfer_t;

//============================================================================
// Public Functions
//============================================================================
SerialToSPIApp_Status_t SerialToSPIAppUnit_Init(void);
SerialToSPIApp_Status_t SerialToSPIAppUnit_DeInit(void);
SerialToSPIApp_Status_t SerialToSPIAppUnit_Run(void);
SerialToSPIApp_Status_t SerialToSPIAppUnit_ProcessFrame(const uint8_t *pFrame, uint16_t frameLength, uint8_t *pResponse, uint16_t *pResponseLength);

//============================================================================
// Backward Compatibility Macros
//============================================================================
#define SerialToSPIAppUnit_Init           SerialToSPIApp_Init
#define SerialToSPIAppUnit_DeInit         SerialToSPIApp_DeInit
#define SerialToSPIAppUnit_Run            SerialToSPIApp_Run
#define SerialToSPIAppUnit_ProcessFrame   SerialToSPIApp_ProcessFrame

#endif /* SERIAL_TO_SPI_APPUNIT_H */
