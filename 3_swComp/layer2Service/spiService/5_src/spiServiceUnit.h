#ifndef SPISERVICEUNIT_H
#define SPISERVICEUNIT_H
#include <stdint.h>
#include <stdbool.h>
#include "spiServiceCfg.h"

//============================================================================
// Configuration Macros
//============================================================================
#define SPI_SERVICE_CFG_MAX_TRANSFER     1024U

//============================================================================
// Type Definitions
//============================================================================
typedef enum
{
    SPISERVICE_STATUS_OK = 0,
    SPISERVICE_STATUS_ERROR,
    SPISERVICE_STATUS_INVALID_PARAM,
    SPISERVICE_STATUS_NOT_INITIALIZED,
    SPISERVICE_STATUS_BUS_ERROR
} SpiService_Status_t;

//============================================================================
// Public Functions - Typed API (no DID/RID awareness)
//============================================================================
SpiService_Status_t SpiServiceUnit_Init(void);
SpiService_Status_t SpiServiceUnit_DeInit(void);

/* SPI Write: transmit data to device (CS managed internally) */
SpiService_Status_t SpiServiceUnit_Write(uint8_t device, const uint8_t *pData, uint16_t length);

/* SPI Transceive: simultaneous transmit and receive (CS managed internally) */
SpiService_Status_t SpiServiceUnit_Transceive(uint8_t device, const uint8_t *pTxData, uint16_t txLength, uint8_t *pRxData, uint16_t rxLength);

#endif /* SPISERVICEUNIT_H */