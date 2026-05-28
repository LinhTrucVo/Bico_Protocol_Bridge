#include "mockI2CAPP.h"
#include "../../../5_src/I2CAPPUnit.c"

DEFINE_FFF_GLOBALS;

I2CAPP_Status_t call_I2CAPP_Init(void) { return I2CAPP_Init(); }
I2CAPP_Status_t call_I2CAPP_DeInit(void) { return I2CAPP_DeInit(); }
I2CAPP_Status_t call_I2CAPP_Write(uint16_t address, const uint8_t *pData, uint16_t length) { return I2CAPP_Write(address, pData, length); }
I2CAPP_Status_t call_I2CAPP_Read(uint16_t address, uint8_t *pData, uint16_t length) { return I2CAPP_Read(address, pData, length); }