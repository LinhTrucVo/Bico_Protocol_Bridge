#include "mockANALOGAPP.h"
#include "../../../5_src/ANALOGAPPUnit.c"

DEFINE_FFF_GLOBALS;

ANALOGAPP_Status_t call_ANALOGAPP_Init(void) { return ANALOGAPP_Init(); }
ANALOGAPP_Status_t call_ANALOGAPP_DeInit(void) { return ANALOGAPP_DeInit(); }
ANALOGAPP_Status_t call_ANALOGAPP_ReadAdc(uint8_t channel, uint16_t *pRawValue) { return ANALOGAPP_ReadAdc(channel, pRawValue); }