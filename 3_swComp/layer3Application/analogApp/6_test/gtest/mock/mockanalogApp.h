#ifndef MOCKANALOGAPP_H
#define MOCKANALOGAPP_H
#include "fff.h"
#include "ANALOGAPP.h"
#include "ANALOGAPPUnit.h"

ANALOGAPP_Status_t call_ANALOGAPP_Init(void);
ANALOGAPP_Status_t call_ANALOGAPP_DeInit(void);
ANALOGAPP_Status_t call_ANALOGAPP_ReadAdc(uint8_t channel, uint16_t *pRawValue);

#endif /* MOCKANALOGAPP_H */