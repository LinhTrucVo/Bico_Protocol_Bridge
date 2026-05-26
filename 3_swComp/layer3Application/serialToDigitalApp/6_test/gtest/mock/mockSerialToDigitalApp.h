#ifndef MOCKSERIALTODIGITALAPP_H
#define MOCKSERIALTODIGITALAPP_H
#include "fff.h"
#include "serialToDigitalApp.h"
#include "serialToDigitalAppUnit.h"

SerialToDigitalApp_Status_t call_SerialToDigitalApp_Init(void);
SerialToDigitalApp_Status_t call_SerialToDigitalApp_DeInit(void);
SerialToDigitalApp_Status_t call_SerialToDigitalApp_WriteGpio(uint8_t pin, uint8_t state);
SerialToDigitalApp_Status_t call_SerialToDigitalApp_ReadGpio(uint8_t pin, uint8_t *pState);
SerialToDigitalApp_Status_t call_SerialToDigitalApp_StartPwm(uint8_t channel);
SerialToDigitalApp_Status_t call_SerialToDigitalApp_StopPwm(uint8_t channel);

#endif /* MOCKSERIALTODIGITALAPP_H */