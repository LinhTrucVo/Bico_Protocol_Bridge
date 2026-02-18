#ifndef SERIAL_TO_ANALOG_APPUNIT_H
#define SERIAL_TO_ANALOG_APPUNIT_H
#include <stdint.h>
#include <stdbool.h>
#include "serialToAnalogAppCfg.h"

//============================================================================
// Configuration Macros
//============================================================================
#define SERIAL_TO_ANALOG_CFG_MAX_CHANNELS      8
#define SERIAL_TO_ANALOG_CFG_DEFAULT_RES       12
#define SERIAL_TO_ANALOG_CFG_DEFAULT_RANGE     0
#define SERIAL_TO_ANALOG_CFG_MIN_SAMPLE_HZ     1
#define SERIAL_TO_ANALOG_CFG_MAX_SAMPLE_HZ     10000
#define SERIAL_TO_ANALOG_CFG_DEFAULT_AVG       1

//============================================================================
// Type Definitions
//============================================================================
typedef enum
{
    SERIAL_TO_ANALOG_APP_STATUS_OK = 0,
    SERIAL_TO_ANALOG_APP_STATUS_ERROR,
    SERIAL_TO_ANALOG_APP_STATUS_INVALID_PARAM,
    SERIAL_TO_ANALOG_APP_STATUS_NOT_INITIALIZED
} SerialToAnalogApp_Status_t;

typedef enum
{
    SerialToAnalogApp_STATE_IDLE = 0,
    SerialToAnalogApp_STATE_SAMPLING,
    SerialToAnalogApp_STATE_ERROR
} SerialToAnalogApp_State_t;

typedef enum
{
    SERIAL_TO_ANALOG_RESOLUTION_8BIT  = 8,
    SERIAL_TO_ANALOG_RESOLUTION_10BIT = 10,
    SERIAL_TO_ANALOG_RESOLUTION_12BIT = 12,
    SERIAL_TO_ANALOG_RESOLUTION_16BIT = 16
} SerialToAnalogApp_Resolution_t;

typedef enum
{
    SERIAL_TO_ANALOG_RANGE_3V3 = 0,
    SERIAL_TO_ANALOG_RANGE_5V  = 1
} SerialToAnalogApp_Range_t;

typedef struct
{
    uint8_t  channelId;
    bool     enable;
    SerialToAnalogApp_Resolution_t resolution;
    SerialToAnalogApp_Range_t      range;
    uint32_t samplingFrequency;
    uint8_t  averageSamples;
    bool     thresholdEnable;
    float    thresholdHigh;
    float    thresholdLow;
} SerialToAnalogApp_ChannelConfig_t;

typedef struct
{
    uint8_t  channelId;
    uint16_t sampleCount;
    uint16_t samples[256];
} SerialToAnalogApp_SampleBuffer_t;

typedef void (*SerialToAnalogApp_ThresholdCallback_t)(uint8_t channelId, float value);

//============================================================================
// Public Functions
//============================================================================
SerialToAnalogApp_Status_t SerialToAnalogAppUnit_Init(void);
SerialToAnalogApp_Status_t SerialToAnalogAppUnit_DeInit(void);
SerialToAnalogApp_Status_t SerialToAnalogAppUnit_Run(void);
SerialToAnalogApp_Status_t SerialToAnalogAppUnit_ProcessFrame(const uint8_t *pFrame, uint16_t frameLength, uint8_t *pResponse, uint16_t *pResponseLength);

//============================================================================
// Backward Compatibility Macros
//============================================================================
#define SerialToAnalogAppUnit_Init            SerialToAnalogApp_Init
#define SerialToAnalogAppUnit_DeInit          SerialToAnalogApp_DeInit
#define SerialToAnalogAppUnit_Run             SerialToAnalogApp_Run
#define SerialToAnalogAppUnit_ProcessFrame    SerialToAnalogApp_ProcessFrame

#endif /* SERIAL_TO_ANALOG_APPUNIT_H */
