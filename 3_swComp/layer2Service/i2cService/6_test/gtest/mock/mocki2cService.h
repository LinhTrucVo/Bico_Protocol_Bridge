#ifndef MOCKI2CAPP_H
#define MOCKI2CAPP_H
#include "fff.h"
#include "i2cService.h"
#include "i2cServiceUnit.h"

I2cService_Status_t call_I2cServiceUnit_Init(void);
I2cService_Status_t call_I2cServiceUnit_DeInit(void);
I2cService_Status_t call_I2cServiceUnit_Write(uint16_t address, const uint8_t *pData, uint16_t length);
I2cService_Status_t call_I2cServiceUnit_Read(uint16_t address, uint8_t *pData, uint16_t length);

#endif /* MOCKI2CAPP_H */