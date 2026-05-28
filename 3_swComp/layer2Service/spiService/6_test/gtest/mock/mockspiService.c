#include "mockSPIAPP.h"
#include "../../../5_src/SPIAPPUnit.c"

DEFINE_FFF_GLOBALS;

SpiService_Status_t call_SpiServiceUnit_Init(void) { return SpiServiceUnit_Init(); }
SpiService_Status_t call_SpiServiceUnit_DeInit(void) { return SpiServiceUnit_DeInit(); }
SpiService_Status_t call_SpiServiceUnit_Write(uint8_t device, const uint8_t *pData, uint16_t length) { return SpiServiceUnit_Write(device, pData, length); }
SpiService_Status_t call_SpiServiceUnit_Transceive(uint8_t device, const uint8_t *pTxData, uint16_t txLength, uint8_t *pRxData, uint16_t rxLength) { return SpiServiceUnit_Transceive(device, pTxData, txLength, pRxData, rxLength); }