#ifndef CONFIG_SERVICEUNIT_H
#define CONFIG_SERVICEUNIT_H
#include <stdint.h>
#include <stdbool.h>
#include "configServiceCfg.h"

//============================================================================
// Configuration Macros
//============================================================================
#define CONFIG_SERVICE_CFG_MAX_CHANNELS      8
#define CONFIG_SERVICE_CFG_MAX_PINS          32
#define CONFIG_SERVICE_CFG_MIN_SAMPLE_HZ     1
#define CONFIG_SERVICE_CFG_MAX_SAMPLE_HZ     10000
#define CONFIG_SERVICE_CFG_MIN_PWM_HZ        1
#define CONFIG_SERVICE_CFG_MAX_PWM_HZ        100000
#define CONFIG_SERVICE_CFG_MAX_DUTY          10000

//============================================================================
// Status Codes
//============================================================================
typedef enum
{
    CONFIG_SERVICE_STATUS_OK = 0,
    CONFIG_SERVICE_STATUS_ERROR,
    CONFIG_SERVICE_STATUS_INVALID_PARAM,
    CONFIG_SERVICE_STATUS_NOT_INITIALIZED
} ConfigService_Status_t;

//============================================================================
// Configuration Structures
//============================================================================
typedef struct
{
    uint32_t baudrate;
    uint8_t dataBits;
    uint8_t stopBits;
    uint8_t parity;
} ConfigService_SerialConfig_t;

typedef struct
{
    uint8_t channelId;
    uint8_t resolutionBits;
    float vRef;
    uint32_t samplingFrequency;
    uint8_t averageSamples;
    float thresholdHigh;
    float thresholdLow;
    bool thresholdEnable;
} ConfigService_AnalogChannelConfig_t;

typedef struct
{
    uint8_t pinId;
    uint8_t direction;
    uint8_t initialState;
} ConfigService_DigitalPinConfig_t;

typedef struct
{
    uint8_t channelId;
    uint32_t frequency;
    uint16_t dutyCycle;
} ConfigService_PwmConfig_t;

typedef struct
{
    uint32_t speed;
    uint8_t addressMode;
    uint16_t timeoutMs;
} ConfigService_I2cConfig_t;

typedef struct
{
    uint32_t clockSpeed;
    uint8_t mode;
    uint8_t bitOrder;
} ConfigService_SpiConfig_t;

//============================================================================
// Function declarations
//============================================================================
ConfigService_Status_t ConfigServiceUnit_Init(void);
ConfigService_Status_t ConfigServiceUnit_DeInit(void);
ConfigService_Status_t ConfigServiceUnit_SetSerialConfig(const ConfigService_SerialConfig_t *pConfig);
ConfigService_Status_t ConfigServiceUnit_GetSerialConfig(ConfigService_SerialConfig_t *pConfig);
ConfigService_Status_t ConfigServiceUnit_SetAnalogChannelConfig(uint8_t channelId, const ConfigService_AnalogChannelConfig_t *pConfig);
ConfigService_Status_t ConfigServiceUnit_GetAnalogChannelConfig(uint8_t channelId, ConfigService_AnalogChannelConfig_t *pConfig);
ConfigService_Status_t ConfigServiceUnit_SetDigitalPinConfig(uint8_t pinId, const ConfigService_DigitalPinConfig_t *pConfig);
ConfigService_Status_t ConfigServiceUnit_GetDigitalPinConfig(uint8_t pinId, ConfigService_DigitalPinConfig_t *pConfig);
ConfigService_Status_t ConfigServiceUnit_SetPwmConfig(uint8_t channelId, const ConfigService_PwmConfig_t *pConfig);
ConfigService_Status_t ConfigServiceUnit_GetPwmConfig(uint8_t channelId, ConfigService_PwmConfig_t *pConfig);
ConfigService_Status_t ConfigServiceUnit_SetI2cConfig(const ConfigService_I2cConfig_t *pConfig);
ConfigService_Status_t ConfigServiceUnit_GetI2cConfig(ConfigService_I2cConfig_t *pConfig);
ConfigService_Status_t ConfigServiceUnit_SetSpiConfig(const ConfigService_SpiConfig_t *pConfig);
ConfigService_Status_t ConfigServiceUnit_GetSpiConfig(ConfigService_SpiConfig_t *pConfig);
ConfigService_Status_t ConfigServiceUnit_ValidateAnalogChannelConfig(const ConfigService_AnalogChannelConfig_t *pConfig);
ConfigService_Status_t ConfigServiceUnit_ValidatePwmConfig(const ConfigService_PwmConfig_t *pConfig);
ConfigService_Status_t ConfigServiceUnit_ValidateI2cConfig(const ConfigService_I2cConfig_t *pConfig);
ConfigService_Status_t ConfigServiceUnit_ValidateSpiConfig(const ConfigService_SpiConfig_t *pConfig);

#endif
