#include "mockANALOGAPP.h"
#include "../../../5_src/ANALOGAPPUnit.c"

DEFINE_FFF_GLOBALS;

AnalogService_Status_t call_AnalogServiceUnit_Init(void) { return AnalogServiceUnit_Init(); }
AnalogService_Status_t call_AnalogServiceUnit_DeInit(void) { return AnalogServiceUnit_DeInit(); }
AnalogService_Status_t call_AnalogServiceUnit_ReadAdc(uint8_t channel, uint16_t *pRawValue) { return AnalogServiceUnit_ReadAdc(channel, pRawValue); }