#ifndef DATA_CONVERSION_SERVICEUNIT_H
#define DATA_CONVERSION_SERVICEUNIT_H
#include <stdint.h>
#include "dataConversionServiceCfg.h"
typedef enum DataConversionService_Status_t DataConversionService_Status_t;
DataConversionService_Status_t DataConversionServiceUnit_Init(void);
DataConversionService_Status_t DataConversionServiceUnit_DeInit(void);
DataConversionService_Status_t DataConversionServiceUnit_AdcToVoltage(uint16_t adcValue, uint16_t maxAdcValue, float vRef, float *pVoltage);
DataConversionService_Status_t DataConversionServiceUnit_VoltageToAdc(float voltage, uint16_t maxAdcValue, float vRef, uint16_t *pAdcValue);
DataConversionService_Status_t DataConversionServiceUnit_DacToVoltage(uint16_t dacValue, uint16_t maxDacValue, float vRef, float *pVoltage);
DataConversionService_Status_t DataConversionServiceUnit_VoltageToDac(float voltage, uint16_t maxDacValue, float vRef, uint16_t *pDacValue);
DataConversionService_Status_t DataConversionServiceUnit_CelsiusToFahrenheit(float celsius, float *pFahrenheit);
DataConversionService_Status_t DataConversionServiceUnit_FahrenheitToCelsius(float fahrenheit, float *pCelsius);
#endif
