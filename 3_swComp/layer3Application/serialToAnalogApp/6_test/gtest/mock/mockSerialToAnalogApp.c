#include "mockSerialToAnalogApp.h"
#include "../../../5_src/serialToAnalogAppUnit.c"

DEFINE_FFF_GLOBALS;

SerialToAnalogApp_Status_t call_SerialToAnalogApp_Init(void) { return SerialToAnalogApp_Init(); }
SerialToAnalogApp_Status_t call_SerialToAnalogApp_DeInit(void) { return SerialToAnalogApp_DeInit(); }
SerialToAnalogApp_Status_t call_SerialToAnalogApp_ReadAdc(uint8_t channel, uint16_t *pRawValue) { return SerialToAnalogApp_ReadAdc(channel, pRawValue); }