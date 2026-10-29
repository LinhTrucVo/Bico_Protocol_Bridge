#include "mockI2CAPP.h"
#include "../../../5_src/I2CAPPUnit.c"

DEFINE_FFF_GLOBALS;

I2cService_Status_t call_I2cServiceUnit_Init(void) { return I2cServiceUnit_Init(); }
I2cService_Status_t call_I2cServiceUnit_DeInit(void) { return I2cServiceUnit_DeInit(); }
I2cService_Status_t call_I2cServiceUnit_Write(uint16_t address, const uint8_t *pData, uint16_t length) { return I2cServiceUnit_Write(address, pData, length); }
I2cService_Status_t call_I2cServiceUnit_Read(uint16_t address, uint8_t *pData, uint16_t length) { return I2cServiceUnit_Read(address, pData, length); }