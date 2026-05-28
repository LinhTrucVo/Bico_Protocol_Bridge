#include "mockSPIAPP.h"
#include "../../../5_src/SPIAPPUnit.c"

DEFINE_FFF_GLOBALS;

SPIAPP_Status_t call_SPIAPP_Init(void) { return SPIAPP_Init(); }
SPIAPP_Status_t call_SPIAPP_DeInit(void) { return SPIAPP_DeInit(); }
SPIAPP_Status_t call_SPIAPP_Write(uint8_t device, const uint8_t *pData, uint16_t length) { return SPIAPP_Write(device, pData, length); }
SPIAPP_Status_t call_SPIAPP_Transceive(uint8_t device, const uint8_t *pTxData, uint16_t txLength, uint8_t *pRxData, uint16_t rxLength) { return SPIAPP_Transceive(device, pTxData, txLength, pRxData, rxLength); }