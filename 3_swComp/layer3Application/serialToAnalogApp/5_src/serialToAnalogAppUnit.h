#ifndef SERIAL_TO_ANALOG_APPUNIT_H
#define SERIAL_TO_ANALOG_APPUNIT_H
#include <stdint.h>
#include "serialToAnalogAppCfg.h"
typedef enum SerialToAnalogApp_Status_t SerialToAnalogApp_Status_t;
SerialToAnalogApp_Status_t SerialToAnalogAppUnit_Init(void);
SerialToAnalogApp_Status_t SerialToAnalogAppUnit_DeInit(void);
SerialToAnalogApp_Status_t SerialToAnalogAppUnit_Run(void);
SerialToAnalogApp_Status_t SerialToAnalogAppUnit_ProcessFrame(const uint8_t *pFrame, uint16_t frameLength, uint8_t *pResponse, uint16_t *pResponseLength);
#endif
