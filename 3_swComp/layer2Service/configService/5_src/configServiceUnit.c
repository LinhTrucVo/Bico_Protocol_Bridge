// ConfigService Implementation

#include "configService.h"
#include "configServiceCfg.h"

typedef struct
{
    bool initialized;
    ConfigService_SerialConfig_t serialCfg;
    ConfigService_AnalogChannelConfig_t analogCfg[CONFIG_SERVICE_CFG_MAX_CHANNELS];
    ConfigService_DigitalPinConfig_t digitalCfg[CONFIG_SERVICE_CFG_MAX_PINS];
    ConfigService_PwmConfig_t pwmCfg[CONFIG_SERVICE_CFG_MAX_CHANNELS];
    ConfigService_I2cConfig_t i2cCfg;
    ConfigService_SpiConfig_t spiCfg;
} ConfigService_Context_t;

static ConfigService_Context_t context = {0};

ConfigService_Status_t ConfigServiceUnit_Init(void)
{
    context.initialized = true;
    context.serialCfg.baudrate = 115200;
    context.serialCfg.dataBits = 8;
    context.serialCfg.stopBits = 1;
    context.serialCfg.parity = 0;

    for (uint8_t i = 0; i < CONFIG_SERVICE_CFG_MAX_CHANNELS; i++)
    {
        context.analogCfg[i].channelId = i;
        context.analogCfg[i].resolutionBits = 12;
        context.analogCfg[i].vRef = 3.3f;
        context.analogCfg[i].samplingFrequency = 1000;
        context.analogCfg[i].averageSamples = 1;
        context.analogCfg[i].thresholdHigh = 0.0f;
        context.analogCfg[i].thresholdLow = 0.0f;
        context.analogCfg[i].thresholdEnable = false;

        context.pwmCfg[i].channelId = i;
        context.pwmCfg[i].frequency = 1000;
        context.pwmCfg[i].dutyCycle = 5000;
    }

    for (uint8_t i = 0; i < CONFIG_SERVICE_CFG_MAX_PINS; i++)
    {
        context.digitalCfg[i].pinId = i;
        context.digitalCfg[i].direction = 0;
        context.digitalCfg[i].initialState = 0;
    }

    context.i2cCfg.speed = 100000;
    context.i2cCfg.addressMode = 0;
    context.i2cCfg.timeoutMs = 100;

    context.spiCfg.clockSpeed = 1000000;
    context.spiCfg.mode = 0;
    context.spiCfg.bitOrder = 0;

    return CONFIG_SERVICE_STATUS_OK;
}

ConfigService_Status_t ConfigServiceUnit_DeInit(void)
{
    context.initialized = false;
    return CONFIG_SERVICE_STATUS_OK;
}

ConfigService_Status_t ConfigServiceUnit_SetSerialConfig(const ConfigService_SerialConfig_t *pConfig)
{
    if (!context.initialized)
    {
        return CONFIG_SERVICE_STATUS_NOT_INITIALIZED;
    }
    if (pConfig == NULL)
    {
        return CONFIG_SERVICE_STATUS_INVALID_PARAM;
    }
    context.serialCfg = *pConfig;
    return CONFIG_SERVICE_STATUS_OK;
}

ConfigService_Status_t ConfigServiceUnit_GetSerialConfig(ConfigService_SerialConfig_t *pConfig)
{
    if (!context.initialized)
    {
        return CONFIG_SERVICE_STATUS_NOT_INITIALIZED;
    }
    if (pConfig == NULL)
    {
        return CONFIG_SERVICE_STATUS_INVALID_PARAM;
    }
    *pConfig = context.serialCfg;
    return CONFIG_SERVICE_STATUS_OK;
}

ConfigService_Status_t ConfigServiceUnit_SetAnalogChannelConfig(uint8_t channelId, const ConfigService_AnalogChannelConfig_t *pConfig)
{
    if (channelId >= CONFIG_SERVICE_CFG_MAX_CHANNELS || pConfig == NULL)
    {
        return CONFIG_SERVICE_STATUS_INVALID_PARAM;
    }
    context.analogCfg[channelId] = *pConfig;
    return CONFIG_SERVICE_STATUS_OK;
}

ConfigService_Status_t ConfigServiceUnit_GetAnalogChannelConfig(uint8_t channelId, ConfigService_AnalogChannelConfig_t *pConfig)
{
    if (channelId >= CONFIG_SERVICE_CFG_MAX_CHANNELS || pConfig == NULL)
    {
        return CONFIG_SERVICE_STATUS_INVALID_PARAM;
    }
    *pConfig = context.analogCfg[channelId];
    return CONFIG_SERVICE_STATUS_OK;
}

ConfigService_Status_t ConfigServiceUnit_SetDigitalPinConfig(uint8_t pinId, const ConfigService_DigitalPinConfig_t *pConfig)
{
    if (pinId >= CONFIG_SERVICE_CFG_MAX_PINS || pConfig == NULL)
    {
        return CONFIG_SERVICE_STATUS_INVALID_PARAM;
    }
    context.digitalCfg[pinId] = *pConfig;
    return CONFIG_SERVICE_STATUS_OK;
}

ConfigService_Status_t ConfigServiceUnit_GetDigitalPinConfig(uint8_t pinId, ConfigService_DigitalPinConfig_t *pConfig)
{
    if (pinId >= CONFIG_SERVICE_CFG_MAX_PINS || pConfig == NULL)
    {
        return CONFIG_SERVICE_STATUS_INVALID_PARAM;
    }
    *pConfig = context.digitalCfg[pinId];
    return CONFIG_SERVICE_STATUS_OK;
}

ConfigService_Status_t ConfigServiceUnit_SetPwmConfig(uint8_t channelId, const ConfigService_PwmConfig_t *pConfig)
{
    if (channelId >= CONFIG_SERVICE_CFG_MAX_CHANNELS || pConfig == NULL)
    {
        return CONFIG_SERVICE_STATUS_INVALID_PARAM;
    }
    context.pwmCfg[channelId] = *pConfig;
    return CONFIG_SERVICE_STATUS_OK;
}

ConfigService_Status_t ConfigServiceUnit_GetPwmConfig(uint8_t channelId, ConfigService_PwmConfig_t *pConfig)
{
    if (channelId >= CONFIG_SERVICE_CFG_MAX_CHANNELS || pConfig == NULL)
    {
        return CONFIG_SERVICE_STATUS_INVALID_PARAM;
    }
    *pConfig = context.pwmCfg[channelId];
    return CONFIG_SERVICE_STATUS_OK;
}

ConfigService_Status_t ConfigServiceUnit_SetI2cConfig(const ConfigService_I2cConfig_t *pConfig)
{
    if (pConfig == NULL)
    {
        return CONFIG_SERVICE_STATUS_INVALID_PARAM;
    }
    context.i2cCfg = *pConfig;
    return CONFIG_SERVICE_STATUS_OK;
}

ConfigService_Status_t ConfigServiceUnit_GetI2cConfig(ConfigService_I2cConfig_t *pConfig)
{
    if (pConfig == NULL)
    {
        return CONFIG_SERVICE_STATUS_INVALID_PARAM;
    }
    *pConfig = context.i2cCfg;
    return CONFIG_SERVICE_STATUS_OK;
}

ConfigService_Status_t ConfigServiceUnit_SetSpiConfig(const ConfigService_SpiConfig_t *pConfig)
{
    if (pConfig == NULL)
    {
        return CONFIG_SERVICE_STATUS_INVALID_PARAM;
    }
    context.spiCfg = *pConfig;
    return CONFIG_SERVICE_STATUS_OK;
}

ConfigService_Status_t ConfigServiceUnit_GetSpiConfig(ConfigService_SpiConfig_t *pConfig)
{
    if (pConfig == NULL)
    {
        return CONFIG_SERVICE_STATUS_INVALID_PARAM;
    }
    *pConfig = context.spiCfg;
    return CONFIG_SERVICE_STATUS_OK;
}

ConfigService_Status_t ConfigServiceUnit_ValidateAnalogChannelConfig(const ConfigService_AnalogChannelConfig_t *pConfig)
{
    if (pConfig == NULL)
    {
        return CONFIG_SERVICE_STATUS_INVALID_PARAM;
    }
    if (pConfig->samplingFrequency < CONFIG_SERVICE_CFG_MIN_SAMPLE_HZ || pConfig->samplingFrequency > CONFIG_SERVICE_CFG_MAX_SAMPLE_HZ)
    {
        return CONFIG_SERVICE_STATUS_INVALID_PARAM;
    }
    return CONFIG_SERVICE_STATUS_OK;
}

ConfigService_Status_t ConfigServiceUnit_ValidatePwmConfig(const ConfigService_PwmConfig_t *pConfig)
{
    if (pConfig == NULL)
    {
        return CONFIG_SERVICE_STATUS_INVALID_PARAM;
    }
    if (pConfig->frequency < CONFIG_SERVICE_CFG_MIN_PWM_HZ || pConfig->frequency > CONFIG_SERVICE_CFG_MAX_PWM_HZ)
    {
        return CONFIG_SERVICE_STATUS_INVALID_PARAM;
    }
    if (pConfig->dutyCycle > CONFIG_SERVICE_CFG_MAX_DUTY)
    {
        return CONFIG_SERVICE_STATUS_INVALID_PARAM;
    }
    return CONFIG_SERVICE_STATUS_OK;
}

ConfigService_Status_t ConfigServiceUnit_ValidateI2cConfig(const ConfigService_I2cConfig_t *pConfig)
{
    if (pConfig == NULL)
    {
        return CONFIG_SERVICE_STATUS_INVALID_PARAM;
    }
    return CONFIG_SERVICE_STATUS_OK;
}

ConfigService_Status_t ConfigServiceUnit_ValidateSpiConfig(const ConfigService_SpiConfig_t *pConfig)
{
    if (pConfig == NULL)
    {
        return CONFIG_SERVICE_STATUS_INVALID_PARAM;
    }
    return CONFIG_SERVICE_STATUS_OK;
}
