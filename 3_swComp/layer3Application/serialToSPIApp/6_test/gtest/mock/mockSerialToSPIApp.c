#include "mockSerialToSPIApp.h"
#include "../../../5_src/serialToSPIAppUnit.c"

DEFINE_FFF_GLOBALS;

SerialToSPIApp_Status_t call_SerialToSPIApp_Init(void) { return SerialToSPIApp_Init(); }
SerialToSPIApp_Status_t call_SerialToSPIApp_DeInit(void) { return SerialToSPIApp_DeInit(); }
SerialToSPIApp_Status_t call_SerialToSPIApp_Write(uint8_t device, const uint8_t *pData, uint16_t length) { return SerialToSPIApp_Write(device, pData, length); }
SerialToSPIApp_Status_t call_SerialToSPIApp_Transceive(uint8_t device, const uint8_t *pTxData, uint16_t txLength, uint8_t *pRxData, uint16_t rxLength) { return SerialToSPIApp_Transceive(device, pTxData, txLength, pRxData, rxLength); }