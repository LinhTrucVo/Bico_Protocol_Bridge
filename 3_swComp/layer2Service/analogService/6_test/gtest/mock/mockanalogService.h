#ifndef MOCKANALOGAPP_H
#define MOCKANALOGAPP_H
#include "fff.h"
#include "analogService.h"
#include "analogServiceUnit.h"

AnalogService_Status_t call_AnalogServiceUnit_Init(void);
AnalogService_Status_t call_AnalogServiceUnit_DeInit(void);
AnalogService_Status_t call_AnalogServiceUnit_ReadAdc(uint8_t channel, uint16_t *pRawValue);

#endif /* MOCKANALOGAPP_H */