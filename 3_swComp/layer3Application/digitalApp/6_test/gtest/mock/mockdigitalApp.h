#ifndef MOCKDIGITALAPP_H
#define MOCKDIGITALAPP_H
#include "fff.h"
#include "DIGITALAPP.h"
#include "DIGITALAPPUnit.h"

DIGITALAPP_Status_t call_DIGITALAPP_Init(void);
DIGITALAPP_Status_t call_DIGITALAPP_DeInit(void);
DIGITALAPP_Status_t call_DIGITALAPP_WriteGpio(uint8_t pin, uint8_t state);
DIGITALAPP_Status_t call_DIGITALAPP_ReadGpio(uint8_t pin, uint8_t *pState);
DIGITALAPP_Status_t call_DIGITALAPP_StartPwm(uint8_t channel);
DIGITALAPP_Status_t call_DIGITALAPP_StopPwm(uint8_t channel);

#endif /* MOCKDIGITALAPP_H */