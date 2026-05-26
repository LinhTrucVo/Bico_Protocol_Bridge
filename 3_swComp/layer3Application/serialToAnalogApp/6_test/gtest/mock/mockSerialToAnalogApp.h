#ifndef MOCKSERIALTOANALOGAPP_H
#define MOCKSERIALTOANALOGAPP_H
#include "fff.h"
#include "serialToAnalogApp.h"
#include "serialToAnalogAppUnit.h"

SerialToAnalogApp_Status_t call_SerialToAnalogApp_Init(void);
SerialToAnalogApp_Status_t call_SerialToAnalogApp_DeInit(void);
SerialToAnalogApp_Status_t call_SerialToAnalogApp_ReadAdc(uint8_t channel, uint16_t *pRawValue);

#endif /* MOCKSERIALTOANALOGAPP_H */