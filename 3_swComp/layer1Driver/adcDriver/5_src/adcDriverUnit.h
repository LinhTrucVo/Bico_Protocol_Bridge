// This file is used to define the public interface of the component unit.
// It contains public macros, types, variables, and function prototypes that shall be included in component headers file (adcDriver.h)

#ifndef BPB_ADCDRIVERUNIT_H
#define BPB_ADCDRIVERUNIT_H

//============================================================================
// Dependencies
//============================================================================
#include <stdint.h>
#include <stdbool.h>
#include "adcDriverCfg.h"

//============================================================================
// Public Macros
//============================================================================
#define BPB_ADC_MAX_CHANNELS            8
#define BPB_ADC_RESOLUTION_BITS         12
#define BPB_ADC_MAX_VALUE               ((1U << BPB_ADC_RESOLUTION_BITS) - 1)
#define BPB_ADC_DEFAULT_SAMPLE_HZ       1000

//============================================================================
// Public Types
//============================================================================
typedef enum
{
    BPB_ADC_STATUS_OK = 0,
    BPB_ADC_STATUS_ERROR,
    BPB_ADC_STATUS_BUSY,
    BPB_ADC_STATUS_TIMEOUT,
    BPB_ADC_STATUS_INVALID_PARAM,
    BPB_ADC_STATUS_NOT_INITIALIZED
} AdcDriver_Status_t;

typedef enum
{
    BPB_ADC_CHANNEL_0 = 0,
    BPB_ADC_CHANNEL_1,
    BPB_ADC_CHANNEL_2,
    BPB_ADC_CHANNEL_3,
    BPB_ADC_CHANNEL_4,
    BPB_ADC_CHANNEL_5,
    BPB_ADC_CHANNEL_6,
    BPB_ADC_CHANNEL_7
} AdcDriver_Channel_t;

typedef enum
{
    BPB_ADC_RESOLUTION_8BIT = 8,
    BPB_ADC_RESOLUTION_10BIT = 10,
    BPB_ADC_RESOLUTION_12BIT = 12,
    BPB_ADC_RESOLUTION_16BIT = 16
} AdcDriver_Resolution_t;

typedef enum
{
    BPB_ADC_VREF_3V3 = 0,
    BPB_ADC_VREF_5V,
    BPB_ADC_VREF_10V,
    BPB_ADC_VREF_EXTERNAL
} AdcDriver_VoltageRef_t;

typedef enum
{
    BPB_ADC_MODE_SINGLE = 0,
    BPB_ADC_MODE_CONTINUOUS,
    BPB_ADC_MODE_SCAN
} AdcDriver_ConversionMode_t;

typedef struct
{
    AdcDriver_Resolution_t resolution;
    AdcDriver_VoltageRef_t voltageReference;
    AdcDriver_ConversionMode_t conversionMode;
    uint32_t samplingFrequency;
    bool enableDMA;
    bool enableInterrupt;
} AdcDriver_Config_t;

typedef void (*AdcDriver_ConversionCallback_t)(AdcDriver_Channel_t channel, uint16_t value);

//============================================================================
// Public Variables
//============================================================================

//============================================================================
// Public Functions
//============================================================================
AdcDriver_Status_t AdcDriverUnit_Init(const AdcDriver_Config_t *pConfig);
AdcDriver_Status_t AdcDriverUnit_ConfigureChannel(AdcDriver_Channel_t channel, bool enable);
AdcDriver_Status_t AdcDriverUnit_SetResolution(AdcDriver_Resolution_t resolution);
AdcDriver_Status_t AdcDriverUnit_SetVoltageReference(AdcDriver_VoltageRef_t voltageRef);
AdcDriver_Status_t AdcDriverUnit_SetSamplingFrequency(uint32_t frequency);
AdcDriver_Status_t AdcDriverUnit_StartConversion(AdcDriver_Channel_t channel);
AdcDriver_Status_t AdcDriverUnit_StopConversion(void);
AdcDriver_Status_t AdcDriverUnit_ReadValue(AdcDriver_Channel_t channel, uint16_t *pValue);
AdcDriver_Status_t AdcDriverUnit_IsConversionComplete(AdcDriver_Channel_t channel, bool *pComplete);
AdcDriver_Status_t AdcDriverUnit_RegisterCallback(AdcDriver_ConversionCallback_t callback);
AdcDriver_Status_t AdcDriverUnit_GetStatus(AdcDriver_Status_t *pStatus);
AdcDriver_Status_t AdcDriverUnit_DeInit(void);

#endif /* BPB_ADCDRIVERUNIT_H */
