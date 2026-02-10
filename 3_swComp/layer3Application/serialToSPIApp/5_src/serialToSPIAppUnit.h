#ifndef SERIAL_TO_SPI_APPUNIT_H
#define SERIAL_TO_SPI_APPUNIT_H
#include <stdint.h>
#include "serialToSPIAppCfg.h"
typedef enum SerialToSPIApp_Status_t SerialToSPIApp_Status_t;
SerialToSPIApp_Status_t SerialToSPIAppUnit_Init(void);
SerialToSPIApp_Status_t SerialToSPIAppUnit_DeInit(void);
SerialToSPIApp_Status_t SerialToSPIAppUnit_Run(void);
SerialToSPIApp_Status_t SerialToSPIAppUnit_ProcessFrame(const uint8_t *pFrame, uint16_t frameLength, uint8_t *pResponse, uint16_t *pResponseLength);
#endif
