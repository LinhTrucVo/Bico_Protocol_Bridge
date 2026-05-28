#ifndef MOCKSPIAPP_H
#define MOCKSPIAPP_H
#include "fff.h"
#include "spiService.h"
#include "spiServiceUnit.h"

SpiService_Status_t call_SpiServiceUnit_Init(void);
SpiService_Status_t call_SpiServiceUnit_DeInit(void);
SpiService_Status_t call_SpiServiceUnit_Write(uint8_t device, const uint8_t *pData, uint16_t length);
SpiService_Status_t call_SpiServiceUnit_Transceive(uint8_t device, const uint8_t *pTxData, uint16_t txLength, uint8_t *pRxData, uint16_t rxLength);

#endif /* MOCKSPIAPP_H */