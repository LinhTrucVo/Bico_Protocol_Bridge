// This file defines the FFF for functions and MOCK functions for ConfigService testing

//============================================================================
// Dependencies
//============================================================================
#include "mockConfigService.h"

// Include the .c file to get access to static variables and functions
#include "configServiceUnit.c"

//============================================================================
// Mock function definitions
//============================================================================

// Required for FFF
DEFINE_FFF_GLOBALS;

// DEFINE_FAKE_VALUE_FUNC(int, ExternalFunction, int);

//============================================================================
// Static function wrapper definitions
//============================================================================

ConfigService_Status_t call_ConfigServiceUnit_Init(void)
{
    return ConfigServiceUnit_Init();
}

ConfigService_Status_t call_ConfigServiceUnit_DeInit(void)
{
    return ConfigServiceUnit_DeInit();
}

ConfigService_Status_t call_ConfigServiceUnit_SetSerialConfig(const ConfigService_SerialConfig_t *pConfig)
{
    return ConfigServiceUnit_SetSerialConfig(pConfig);
}

ConfigService_Status_t call_ConfigServiceUnit_GetSerialConfig(ConfigService_SerialConfig_t *pConfig)
{
    return ConfigServiceUnit_GetSerialConfig(pConfig);
}

ConfigService_Status_t call_ConfigServiceUnit_SetAnalogChannelConfig(uint8_t channelId, const ConfigService_AnalogChannelConfig_t *pConfig)
{
    return ConfigServiceUnit_SetAnalogChannelConfig(channelId, pConfig);
}

ConfigService_Status_t call_ConfigServiceUnit_GetAnalogChannelConfig(uint8_t channelId, ConfigService_AnalogChannelConfig_t *pConfig)
{
    return ConfigServiceUnit_GetAnalogChannelConfig(channelId, pConfig);
}

ConfigService_Status_t call_ConfigServiceUnit_SetDigitalPinConfig(uint8_t pinId, const ConfigService_DigitalPinConfig_t *pConfig)
{
    return ConfigServiceUnit_SetDigitalPinConfig(pinId, pConfig);
}

ConfigService_Status_t call_ConfigServiceUnit_GetDigitalPinConfig(uint8_t pinId, ConfigService_DigitalPinConfig_t *pConfig)
{
    return ConfigServiceUnit_GetDigitalPinConfig(pinId, pConfig);
}

ConfigService_Status_t call_ConfigServiceUnit_SetPwmConfig(uint8_t channelId, const ConfigService_PwmConfig_t *pConfig)
{
    return ConfigServiceUnit_SetPwmConfig(channelId, pConfig);
}

ConfigService_Status_t call_ConfigServiceUnit_GetPwmConfig(uint8_t channelId, ConfigService_PwmConfig_t *pConfig)
{
    return ConfigServiceUnit_GetPwmConfig(channelId, pConfig);
}

ConfigService_Status_t call_ConfigServiceUnit_SetI2cConfig(const ConfigService_I2cConfig_t *pConfig)
{
    return ConfigServiceUnit_SetI2cConfig(pConfig);
}

ConfigService_Status_t call_ConfigServiceUnit_GetI2cConfig(ConfigService_I2cConfig_t *pConfig)
{
    return ConfigServiceUnit_GetI2cConfig(pConfig);
}

ConfigService_Status_t call_ConfigServiceUnit_SetSpiConfig(const ConfigService_SpiConfig_t *pConfig)
{
    return ConfigServiceUnit_SetSpiConfig(pConfig);
}

ConfigService_Status_t call_ConfigServiceUnit_GetSpiConfig(ConfigService_SpiConfig_t *pConfig)
{
    return ConfigServiceUnit_GetSpiConfig(pConfig);
}

ConfigService_Status_t call_ConfigServiceUnit_ValidateAnalogChannelConfig(const ConfigService_AnalogChannelConfig_t *pConfig)
{
    return ConfigServiceUnit_ValidateAnalogChannelConfig(pConfig);
}

ConfigService_Status_t call_ConfigServiceUnit_ValidatePwmConfig(const ConfigService_PwmConfig_t *pConfig)
{
    return ConfigServiceUnit_ValidatePwmConfig(pConfig);
}

ConfigService_Status_t call_ConfigServiceUnit_ValidateI2cConfig(const ConfigService_I2cConfig_t *pConfig)
{
    return ConfigServiceUnit_ValidateI2cConfig(pConfig);
}

ConfigService_Status_t call_ConfigServiceUnit_ValidateSpiConfig(const ConfigService_SpiConfig_t *pConfig)
{
    return ConfigServiceUnit_ValidateSpiConfig(pConfig);
}
