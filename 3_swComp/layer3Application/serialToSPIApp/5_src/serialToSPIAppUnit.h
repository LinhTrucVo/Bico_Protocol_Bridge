#ifndef SERIAL_TO_SPI_APPUNIT_H
#define SERIAL_TO_SPI_APPUNIT_H
#include <stdint.h>
#include <stdbool.h>
#include "serialToSPIAppCfg.h"

//============================================================================
// Configuration Macros
//============================================================================
#define SERIAL_TO_SPI_CFG_MAX_TRANSFER     1024U

//============================================================================
// Type Definitions
//============================================================================
typedef enum
{
    SERIAL_TO_SPI_APP_STATUS_OK = 0,
    SERIAL_TO_SPI_APP_STATUS_ERROR,
    SERIAL_TO_SPI_APP_STATUS_INVALID_PARAM,
    SERIAL_TO_SPI_APP_STATUS_NOT_INITIALIZED,
    SERIAL_TO_SPI_APP_STATUS_BUS_ERROR
} SerialToSPIApp_Status_t;

//============================================================================
// Public Functions - Typed API (no DID/RID awareness)
//============================================================================
SerialToSPIApp_Status_t SerialToSPIApp_Init(void);
SerialToSPIApp_Status_t SerialToSPIApp_DeInit(void);

/* SPI Write: transmit data to device (CS managed internally) */
SerialToSPIApp_Status_t SerialToSPIApp_Write(uint8_t device, const uint8_t *pData, uint16_t length);

/* SPI Transceive: simultaneous transmit and receive (CS managed internally) */
SerialToSPIApp_Status_t SerialToSPIApp_Transceive(uint8_t device, const uint8_t *pTxData, uint16_t txLength, uint8_t *pRxData, uint16_t rxLength);

#endif /* SERIAL_TO_SPI_APPUNIT_H */