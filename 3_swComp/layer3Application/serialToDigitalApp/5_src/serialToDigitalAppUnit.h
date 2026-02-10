#ifndef SERIAL_TO_DIGITAL_APPUNIT_H
#define SERIAL_TO_DIGITAL_APPUNIT_H
#include <stdint.h>
#include "serialToDigitalAppCfg.h"
typedef enum SerialToDigitalApp_Status_t SerialToDigitalApp_Status_t;
SerialToDigitalApp_Status_t SerialToDigitalAppUnit_Init(void);
SerialToDigitalApp_Status_t SerialToDigitalAppUnit_DeInit(void);
SerialToDigitalApp_Status_t SerialToDigitalAppUnit_Run(void);
SerialToDigitalApp_Status_t SerialToDigitalAppUnit_ProcessFrame(const uint8_t *pFrame, uint16_t frameLength, uint8_t *pResponse, uint16_t *pResponseLength);
#endif
