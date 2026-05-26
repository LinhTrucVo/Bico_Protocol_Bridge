#include "mockSerialToDigitalApp.h"
#include "../../../5_src/serialToDigitalAppUnit.c"

DEFINE_FFF_GLOBALS;

SerialToDigitalApp_Status_t call_SerialToDigitalApp_Init(void) { return SerialToDigitalApp_Init(); }
SerialToDigitalApp_Status_t call_SerialToDigitalApp_DeInit(void) { return SerialToDigitalApp_DeInit(); }
SerialToDigitalApp_Status_t call_SerialToDigitalApp_WriteGpio(uint8_t pin, uint8_t state) { return SerialToDigitalApp_WriteGpio(pin, state); }
SerialToDigitalApp_Status_t call_SerialToDigitalApp_ReadGpio(uint8_t pin, uint8_t *pState) { return SerialToDigitalApp_ReadGpio(pin, pState); }
SerialToDigitalApp_Status_t call_SerialToDigitalApp_StartPwm(uint8_t channel) { return SerialToDigitalApp_StartPwm(channel); }
SerialToDigitalApp_Status_t call_SerialToDigitalApp_StopPwm(uint8_t channel) { return SerialToDigitalApp_StopPwm(channel); }