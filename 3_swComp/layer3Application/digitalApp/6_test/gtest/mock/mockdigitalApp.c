#include "mockDIGITALAPP.h"
#include "../../../5_src/DIGITALAPPUnit.c"

DEFINE_FFF_GLOBALS;

DIGITALAPP_Status_t call_DIGITALAPP_Init(void) { return DIGITALAPP_Init(); }
DIGITALAPP_Status_t call_DIGITALAPP_DeInit(void) { return DIGITALAPP_DeInit(); }
DIGITALAPP_Status_t call_DIGITALAPP_WriteGpio(uint8_t pin, uint8_t state) { return DIGITALAPP_WriteGpio(pin, state); }
DIGITALAPP_Status_t call_DIGITALAPP_ReadGpio(uint8_t pin, uint8_t *pState) { return DIGITALAPP_ReadGpio(pin, pState); }
DIGITALAPP_Status_t call_DIGITALAPP_StartPwm(uint8_t channel) { return DIGITALAPP_StartPwm(channel); }
DIGITALAPP_Status_t call_DIGITALAPP_StopPwm(uint8_t channel) { return DIGITALAPP_StopPwm(channel); }