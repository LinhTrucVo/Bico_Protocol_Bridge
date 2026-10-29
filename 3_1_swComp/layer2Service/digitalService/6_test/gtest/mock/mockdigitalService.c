#include "mockDIGITALAPP.h"
#include "../../../5_src/DIGITALAPPUnit.c"

DEFINE_FFF_GLOBALS;

DigitalService_Status_t call_DigitalServiceUnit_Init(void) { return DigitalServiceUnit_Init(); }
DigitalService_Status_t call_DigitalServiceUnit_DeInit(void) { return DigitalServiceUnit_DeInit(); }
DigitalService_Status_t call_DigitalServiceUnit_WriteGpio(uint8_t pin, uint8_t state) { return DigitalServiceUnit_WriteGpio(pin, state); }
DigitalService_Status_t call_DigitalServiceUnit_ReadGpio(uint8_t pin, uint8_t *pState) { return DigitalServiceUnit_ReadGpio(pin, pState); }
DigitalService_Status_t call_DigitalServiceUnit_StartPwm(uint8_t channel) { return DigitalServiceUnit_StartPwm(channel); }
DigitalService_Status_t call_DigitalServiceUnit_StopPwm(uint8_t channel) { return DigitalServiceUnit_StopPwm(channel); }