#ifndef SERIAL_TO_I2C_APPUNIT_H
#define SERIAL_TO_I2C_APPUNIT_H
#include <stdint.h>
#include "serialToI2CAppCfg.h"
typedef enum SerialToI2CApp_Status_t SerialToI2CApp_Status_t;
SerialToI2CApp_Status_t SerialToI2CAppUnit_Init(void);
SerialToI2CApp_Status_t SerialToI2CAppUnit_DeInit(void);
SerialToI2CApp_Status_t SerialToI2CAppUnit_Run(void);
SerialToI2CApp_Status_t SerialToI2CAppUnit_ProcessFrame(const uint8_t *pFrame, uint16_t frameLength, uint8_t *pResponse, uint16_t *pResponseLength);
#endif
