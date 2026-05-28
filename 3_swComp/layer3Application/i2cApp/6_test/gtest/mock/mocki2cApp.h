#ifndef MOCKI2CAPP_H
#define MOCKI2CAPP_H
#include "fff.h"
#include "I2CAPP.h"
#include "I2CAPPUnit.h"

I2CAPP_Status_t call_I2CAPP_Init(void);
I2CAPP_Status_t call_I2CAPP_DeInit(void);
I2CAPP_Status_t call_I2CAPP_Write(uint16_t address, const uint8_t *pData, uint16_t length);
I2CAPP_Status_t call_I2CAPP_Read(uint16_t address, uint8_t *pData, uint16_t length);

#endif /* MOCKI2CAPP_H */