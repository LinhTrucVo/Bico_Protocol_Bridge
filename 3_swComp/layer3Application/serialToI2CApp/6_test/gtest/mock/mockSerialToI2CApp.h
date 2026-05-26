#ifndef MOCKSERIALTOI2CAPP_H
#define MOCKSERIALTOI2CAPP_H
#include "fff.h"
#include "serialToI2CApp.h"
#include "serialToI2CAppUnit.h"

SerialToI2CApp_Status_t call_SerialToI2CApp_Init(void);
SerialToI2CApp_Status_t call_SerialToI2CApp_DeInit(void);
SerialToI2CApp_Status_t call_SerialToI2CApp_Write(uint16_t address, const uint8_t *pData, uint16_t length);
SerialToI2CApp_Status_t call_SerialToI2CApp_Read(uint16_t address, uint8_t *pData, uint16_t length);

#endif /* MOCKSERIALTOI2CAPP_H */