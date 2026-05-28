#ifndef SPI_APPUNIT_H
#define SPI_APPUNIT_H
#include <stdint.h>
#include <stdbool.h>
#include "SPIAPPCfg.h"

//============================================================================
// Configuration Macros
//============================================================================
#define SERIAL_TO_SPI_CFG_MAX_TRANSFER     1024U

//============================================================================
// Type Definitions
//============================================================================
typedef enum
{
    SPI_APP_STATUS_OK = 0,
    SPI_APP_STATUS_ERROR,
    SPI_APP_STATUS_INVALID_PARAM,
    SPI_APP_STATUS_NOT_INITIALIZED,
    SPI_APP_STATUS_BUS_ERROR
} SPIAPP_Status_t;

//============================================================================
// Public Functions - Typed API (no DID/RID awareness)
//============================================================================
SPIAPP_Status_t SPIAPP_Init(void);
SPIAPP_Status_t SPIAPP_DeInit(void);

/* SPI Write: transmit data to device (CS managed internally) */
SPIAPP_Status_t SPIAPP_Write(uint8_t device, const uint8_t *pData, uint16_t length);

/* SPI Transceive: simultaneous transmit and receive (CS managed internally) */
SPIAPP_Status_t SPIAPP_Transceive(uint8_t device, const uint8_t *pTxData, uint16_t txLength, uint8_t *pRxData, uint16_t rxLength);

#endif /* SPI_APPUNIT_H */