#ifndef MOCKSERIALTOSPIAPP_H
#define MOCKSERIALTOSPIAPP_H
#include "fff.h"
#include "serialToSPIApp.h"
#include "serialToSPIAppUnit.h"

SerialToSPIApp_Status_t call_SerialToSPIApp_Init(void);
SerialToSPIApp_Status_t call_SerialToSPIApp_DeInit(void);
SerialToSPIApp_Status_t call_SerialToSPIApp_Write(uint8_t device, const uint8_t *pData, uint16_t length);
SerialToSPIApp_Status_t call_SerialToSPIApp_Transceive(uint8_t device, const uint8_t *pTxData, uint16_t txLength, uint8_t *pRxData, uint16_t rxLength);

#endif /* MOCKSERIALTOSPIAPP_H */