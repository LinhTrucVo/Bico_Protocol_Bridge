// ConfigService Implementation

#include <string.h>
#include "configService.h"
#include "configServiceCfg.h"
#include "nvmService.h"

/* NVM key used to persist the entire configuration block */
#define CONFIG_SERVICE_NVM_KEY  NVM_SERVICE_KEY_SYSTEM_CONFIG

/* Persistent portion of the context (everything except the initialized flag) */
typedef struct
{
    ConfigService_SerialConfig_t serialCfg;
    ConfigService_AnalogChannelConfig_t analogCfg[CONFIG_SERVICE_CFG_MAX_CHANNELS];
    ConfigService_DigitalPinConfig_t digitalCfg[CONFIG_SERVICE_CFG_MAX_PINS];
    ConfigService_PwmConfig_t pwmCfg[CONFIG_SERVICE_CFG_MAX_CHANNELS];
    ConfigService_I2cConfig_t i2cCfg;
    ConfigService_SpiConfig_t spiCfg;
} ConfigService_StorageBlock_t;

typedef struct
{
    bool initialized;
    ConfigService_StorageBlock_t cfg;
} ConfigService_Context_t;

static ConfigService_Context_t context = {0};

ConfigService_Status_t ConfigServiceUnit_Init(void)
{
    context.initialized = true;

    /* Attempt to load persisted configuration from NVM */
    if (ConfigServiceUnit_Load() == CONFIG_SERVICE_STATUS_OK)
    {
        return CONFIG_SERVICE_STATUS_OK;
    }

    /* No valid NVM data found - initialize with defaults */
    context.cfg.serialCfg.baudrate = 115200;
    context.cfg.serialCfg.dataBits = 8;
    context.cfg.serialCfg.stopBits = 1;
    context.cfg.serialCfg.parity = 0;

    for (uint8_t i = 0; i < CONFIG_SERVICE_CFG_MAX_CHANNELS; i++)
    {
        context.cfg.analogCfg[i].channelId = i;
        context.cfg.analogCfg[i].resolutionBits = 12;
        context.cfg.analogCfg[i].vRef = 3.3f;
        context.cfg.analogCfg[i].samplingFrequency = 1000;
        context.cfg.analogCfg[i].averageSamples = 1;
        context.cfg.analogCfg[i].thresholdHigh = 0.0f;
        context.cfg.analogCfg[i].thresholdLow = 0.0f;
        context.cfg.analogCfg[i].thresholdEnable = false;

        context.cfg.pwmCfg[i].channelId = i;
        context.cfg.pwmCfg[i].frequency = 1000;
        context.cfg.pwmCfg[i].dutyCycle = 5000;
    }

    for (uint8_t i = 0; i < CONFIG_SERVICE_CFG_MAX_PINS; i++)
    {
        context.cfg.digitalCfg[i].pinId = i;
        context.cfg.digitalCfg[i].direction = 0;
        context.cfg.digitalCfg[i].initialState = 0;
    }

    context.cfg.i2cCfg.speed = 100000;
    context.cfg.i2cCfg.addressMode = 0;
    context.cfg.i2cCfg.timeoutMs = 100;

    context.cfg.spiCfg.clockSpeed = 1000000;
    context.cfg.spiCfg.mode = 0;
    context.cfg.spiCfg.bitOrder = 0;

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
    context.cfg.serialCfg = *pConfig;
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
    *pConfig = context.cfg.serialCfg;
    return CONFIG_SERVICE_STATUS_OK;
}

ConfigService_Status_t ConfigServiceUnit_SetAnalogChannelConfig(uint8_t channelId, const ConfigService_AnalogChannelConfig_t *pConfig)
{
    if (channelId >= CONFIG_SERVICE_CFG_MAX_CHANNELS || pConfig == NULL)
    {
        return CONFIG_SERVICE_STATUS_INVALID_PARAM;
    }
    context.cfg.analogCfg[channelId] = *pConfig;
    return CONFIG_SERVICE_STATUS_OK;
}

ConfigService_Status_t ConfigServiceUnit_GetAnalogChannelConfig(uint8_t channelId, ConfigService_AnalogChannelConfig_t *pConfig)
{
    if (channelId >= CONFIG_SERVICE_CFG_MAX_CHANNELS || pConfig == NULL)
    {
        return CONFIG_SERVICE_STATUS_INVALID_PARAM;
    }
    *pConfig = context.cfg.analogCfg[channelId];
    return CONFIG_SERVICE_STATUS_OK;
}

ConfigService_Status_t ConfigServiceUnit_SetDigitalPinConfig(uint8_t pinId, const ConfigService_DigitalPinConfig_t *pConfig)
{
    if (pinId >= CONFIG_SERVICE_CFG_MAX_PINS || pConfig == NULL)
    {
        return CONFIG_SERVICE_STATUS_INVALID_PARAM;
    }
    context.cfg.digitalCfg[pinId] = *pConfig;
    return CONFIG_SERVICE_STATUS_OK;
}

ConfigService_Status_t ConfigServiceUnit_GetDigitalPinConfig(uint8_t pinId, ConfigService_DigitalPinConfig_t *pConfig)
{
    if (pinId >= CONFIG_SERVICE_CFG_MAX_PINS || pConfig == NULL)
    {
        return CONFIG_SERVICE_STATUS_INVALID_PARAM;
    }
    *pConfig = context.cfg.digitalCfg[pinId];
    return CONFIG_SERVICE_STATUS_OK;
}

ConfigService_Status_t ConfigServiceUnit_SetPwmConfig(uint8_t channelId, const ConfigService_PwmConfig_t *pConfig)
{
    if (channelId >= CONFIG_SERVICE_CFG_MAX_CHANNELS || pConfig == NULL)
    {
        return CONFIG_SERVICE_STATUS_INVALID_PARAM;
    }
    context.cfg.pwmCfg[channelId] = *pConfig;
    return CONFIG_SERVICE_STATUS_OK;
}

ConfigService_Status_t ConfigServiceUnit_GetPwmConfig(uint8_t channelId, ConfigService_PwmConfig_t *pConfig)
{
    if (channelId >= CONFIG_SERVICE_CFG_MAX_CHANNELS || pConfig == NULL)
    {
        return CONFIG_SERVICE_STATUS_INVALID_PARAM;
    }
    *pConfig = context.cfg.pwmCfg[channelId];
    return CONFIG_SERVICE_STATUS_OK;
}

ConfigService_Status_t ConfigServiceUnit_SetI2cConfig(const ConfigService_I2cConfig_t *pConfig)
{
    if (pConfig == NULL)
    {
        return CONFIG_SERVICE_STATUS_INVALID_PARAM;
    }
    context.cfg.i2cCfg = *pConfig;
    return CONFIG_SERVICE_STATUS_OK;
}

ConfigService_Status_t ConfigServiceUnit_GetI2cConfig(ConfigService_I2cConfig_t *pConfig)
{
    if (pConfig == NULL)
    {
        return CONFIG_SERVICE_STATUS_INVALID_PARAM;
    }
    *pConfig = context.cfg.i2cCfg;
    return CONFIG_SERVICE_STATUS_OK;
}

ConfigService_Status_t ConfigServiceUnit_SetSpiConfig(const ConfigService_SpiConfig_t *pConfig)
{
    if (pConfig == NULL)
    {
        return CONFIG_SERVICE_STATUS_INVALID_PARAM;
    }
    context.cfg.spiCfg = *pConfig;
    return CONFIG_SERVICE_STATUS_OK;
}

ConfigService_Status_t ConfigServiceUnit_GetSpiConfig(ConfigService_SpiConfig_t *pConfig)
{
    if (pConfig == NULL)
    {
        return CONFIG_SERVICE_STATUS_INVALID_PARAM;
    }
    *pConfig = context.cfg.spiCfg;
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

/*============================================================================
 * NVM Persistence
 *===========================================================================*/
ConfigService_Status_t ConfigServiceUnit_Load(void)
{
    uint16_t outLen = 0U;
    NvmService_Status_t nvmStatus = NvmServiceUnit_Load(
        CONFIG_SERVICE_NVM_KEY,
        (uint8_t *)&context.cfg,
        (uint16_t)sizeof(ConfigService_StorageBlock_t),
        &outLen);

    if (nvmStatus != NVM_SERVICE_STATUS_OK)
    {
        return CONFIG_SERVICE_STATUS_ERROR;
    }
    if (outLen != (uint16_t)sizeof(ConfigService_StorageBlock_t))
    {
        return CONFIG_SERVICE_STATUS_ERROR;
    }
    return CONFIG_SERVICE_STATUS_OK;
}

ConfigService_Status_t ConfigServiceUnit_Store(void)
{
    if (!context.initialized)
    {
        return CONFIG_SERVICE_STATUS_NOT_INITIALIZED;
    }

    NvmService_Blob_t blob;
    blob.key = CONFIG_SERVICE_NVM_KEY;
    blob.dataLength = (uint16_t)sizeof(ConfigService_StorageBlock_t);
    blob.pData = (const uint8_t *)&context.cfg;

    NvmService_Status_t nvmStatus = NvmServiceUnit_Save(&blob);
    if (nvmStatus != NVM_SERVICE_STATUS_OK)
    {
        return CONFIG_SERVICE_STATUS_ERROR;
    }
    return CONFIG_SERVICE_STATUS_OK;
}
