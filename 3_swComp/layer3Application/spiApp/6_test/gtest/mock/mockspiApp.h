#ifndef MOCKSPIAPP_H
#define MOCKSPIAPP_H
#include "fff.h"
#include "SPIAPP.h"
#include "SPIAPPUnit.h"

SPIAPP_Status_t call_SPIAPP_Init(void);
SPIAPP_Status_t call_SPIAPP_DeInit(void);
SPIAPP_Status_t call_SPIAPP_Write(uint8_t device, const uint8_t *pData, uint16_t length);
SPIAPP_Status_t call_SPIAPP_Transceive(uint8_t device, const uint8_t *pTxData, uint16_t txLength, uint8_t *pRxData, uint16_t rxLength);

#endif /* MOCKSPIAPP_H */