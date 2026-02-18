// This file declares the FFF for functions and MOCK functions for ConfigService testing

#ifndef MOCKCONFIGSERVICE_H
#define MOCKCONFIGSERVICE_H

//============================================================================
// Dependencies
//============================================================================
#include "fff.h"

#include "configService.h"
#include "configServiceUnit.h"

//============================================================================
// Mock function declarations
//============================================================================
// Declare fake functions for external dependencies if any
// DECLARE_FAKE_VALUE_FUNC(int, ExternalFunction, int);

//============================================================================
// Static function wrapper declarations
//============================================================================

ConfigService_Status_t call_ConfigServiceUnit_Init(void);
ConfigService_Status_t call_ConfigServiceUnit_DeInit(void);
ConfigService_Status_t call_ConfigServiceUnit_SetSerialConfig(const ConfigService_SerialConfig_t *pConfig);
ConfigService_Status_t call_ConfigServiceUnit_GetSerialConfig(ConfigService_SerialConfig_t *pConfig);
ConfigService_Status_t call_ConfigServiceUnit_SetAnalogChannelConfig(uint8_t channelId, const ConfigService_AnalogChannelConfig_t *pConfig);
ConfigService_Status_t call_ConfigServiceUnit_GetAnalogChannelConfig(uint8_t channelId, ConfigService_AnalogChannelConfig_t *pConfig);
ConfigService_Status_t call_ConfigServiceUnit_SetDigitalPinConfig(uint8_t pinId, const ConfigService_DigitalPinConfig_t *pConfig);
ConfigService_Status_t call_ConfigServiceUnit_GetDigitalPinConfig(uint8_t pinId, ConfigService_DigitalPinConfig_t *pConfig);
ConfigService_Status_t call_ConfigServiceUnit_SetPwmConfig(uint8_t channelId, const ConfigService_PwmConfig_t *pConfig);
ConfigService_Status_t call_ConfigServiceUnit_GetPwmConfig(uint8_t channelId, ConfigService_PwmConfig_t *pConfig);
ConfigService_Status_t call_ConfigServiceUnit_SetI2cConfig(const ConfigService_I2cConfig_t *pConfig);
ConfigService_Status_t call_ConfigServiceUnit_GetI2cConfig(ConfigService_I2cConfig_t *pConfig);
ConfigService_Status_t call_ConfigServiceUnit_SetSpiConfig(const ConfigService_SpiConfig_t *pConfig);
ConfigService_Status_t call_ConfigServiceUnit_GetSpiConfig(ConfigService_SpiConfig_t *pConfig);
ConfigService_Status_t call_ConfigServiceUnit_ValidateAnalogChannelConfig(const ConfigService_AnalogChannelConfig_t *pConfig);
ConfigService_Status_t call_ConfigServiceUnit_ValidatePwmConfig(const ConfigService_PwmConfig_t *pConfig);
ConfigService_Status_t call_ConfigServiceUnit_ValidateI2cConfig(const ConfigService_I2cConfig_t *pConfig);
ConfigService_Status_t call_ConfigServiceUnit_ValidateSpiConfig(const ConfigService_SpiConfig_t *pConfig);

#endif /* MOCKCONFIGSERVICE_H */
