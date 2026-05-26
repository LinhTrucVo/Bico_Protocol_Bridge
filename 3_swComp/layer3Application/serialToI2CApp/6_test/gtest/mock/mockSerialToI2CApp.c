#include "mockSerialToI2CApp.h"
#include "../../../5_src/serialToI2CAppUnit.c"

DEFINE_FFF_GLOBALS;

SerialToI2CApp_Status_t call_SerialToI2CApp_Init(void) { return SerialToI2CApp_Init(); }
SerialToI2CApp_Status_t call_SerialToI2CApp_DeInit(void) { return SerialToI2CApp_DeInit(); }
SerialToI2CApp_Status_t call_SerialToI2CApp_Write(uint16_t address, const uint8_t *pData, uint16_t length) { return SerialToI2CApp_Write(address, pData, length); }
SerialToI2CApp_Status_t call_SerialToI2CApp_Read(uint16_t address, uint8_t *pData, uint16_t length) { return SerialToI2CApp_Read(address, pData, length); }