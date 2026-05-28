#ifndef MOCKDIGITALAPP_H
#define MOCKDIGITALAPP_H
#include "fff.h"
#include "digitalService.h"
#include "digitalServiceUnit.h"

DigitalService_Status_t call_DigitalServiceUnit_Init(void);
DigitalService_Status_t call_DigitalServiceUnit_DeInit(void);
DigitalService_Status_t call_DigitalServiceUnit_WriteGpio(uint8_t pin, uint8_t state);
DigitalService_Status_t call_DigitalServiceUnit_ReadGpio(uint8_t pin, uint8_t *pState);
DigitalService_Status_t call_DigitalServiceUnit_StartPwm(uint8_t channel);
DigitalService_Status_t call_DigitalServiceUnit_StopPwm(uint8_t channel);

#endif /* MOCKDIGITALAPP_H */