configService Software Component
##################################

Introduction
************

The Config Service provides a centralized interface for storing and retrieving configuration
parameters for all protocol bridge channels: serial port, analog inputs, digital pins, PWM outputs,
I2C, and SPI. It validates parameters before applying them and serves as the single source of truth
for runtime configuration.


References
**********

Other relevant documents, e.g. ISO standards, whitepapers, etc.


Static architecture
*******************

Component
=========

..  swc:: configService
    :provides: configService.h – get/set and validate configuration for serial, analog, digital, PWM, I2C, and SPI channels.
    :requires: No lower-layer driver dependency; persistence is delegated to nvmService.

Public interfaces
=================

..  sw-if:: configServiceUnit.h

    Public interface of configServiceUnit.

    ..  sw-ifelement:: ConfigServiceUnit_Init()
        :arguments:     return: ConfigService_Status_t;

        Initializes the Config Service and sets all configuration parameters to defaults.

        **Arguments:** None.

        **Return values:** CONFIG_SERVICE_STATUS_OK on success, CONFIG_SERVICE_STATUS_ERROR on failure.

        **Restrictions:** Must be called before any other Config Service function.

    ..  sw-ifelement:: ConfigServiceUnit_DeInit()
        :arguments:     return: ConfigService_Status_t;

        De-initializes the Config Service and releases resources.

        **Arguments:** None.

        **Return values:** CONFIG_SERVICE_STATUS_OK on success.

        **Restrictions:** None.

    ..  sw-ifelement:: ConfigServiceUnit_SetSerialConfig()
        :arguments:     return: ConfigService_Status_t;    pConfig: const ConfigService_SerialConfig_t*;

        Stores the serial port configuration (baudrate, data bits, stop bits, parity).

        **Arguments:**

        - **pConfig**: Pointer to the serial configuration structure to store.

        **Return values:** CONFIG_SERVICE_STATUS_OK on success, CONFIG_SERVICE_STATUS_INVALID_PARAM for NULL or invalid parameters.

        **Restrictions:** None.

    ..  sw-ifelement:: ConfigServiceUnit_GetSerialConfig()
        :arguments:     return: ConfigService_Status_t;    pConfig: ConfigService_SerialConfig_t*;

        Reads back the currently stored serial port configuration.

        **Arguments:**

        - **pConfig**: Pointer to the structure to receive the serial configuration.

        **Return values:** CONFIG_SERVICE_STATUS_OK on success, CONFIG_SERVICE_STATUS_INVALID_PARAM for NULL pointer.

        **Restrictions:** None.

    ..  sw-ifelement:: ConfigServiceUnit_SetAnalogChannelConfig()
        :arguments:     return: ConfigService_Status_t;    channelId: uint8_t;    pConfig: const ConfigService_AnalogChannelConfig_t*;

        Stores the configuration for the specified analog input channel.

        **Arguments:**

        - **channelId**: Analog channel index (0 to CONFIG_SERVICE_CFG_MAX_CHANNELS-1).
        - **pConfig**: Pointer to the analog channel configuration structure.

        **Return values:** CONFIG_SERVICE_STATUS_OK on success, CONFIG_SERVICE_STATUS_INVALID_PARAM for invalid channel or NULL pointer.

        **Restrictions:** None.

    ..  sw-ifelement:: ConfigServiceUnit_GetAnalogChannelConfig()
        :arguments:     return: ConfigService_Status_t;    channelId: uint8_t;    pConfig: ConfigService_AnalogChannelConfig_t*;

        Reads back the configuration for the specified analog input channel.

        **Arguments:**

        - **channelId**: Analog channel index (0 to CONFIG_SERVICE_CFG_MAX_CHANNELS-1).
        - **pConfig**: Pointer to the structure to receive the analog channel configuration.

        **Return values:** CONFIG_SERVICE_STATUS_OK on success, CONFIG_SERVICE_STATUS_INVALID_PARAM for invalid channel or NULL pointer.

        **Restrictions:** None.

    ..  sw-ifelement:: ConfigServiceUnit_SetDigitalPinConfig()
        :arguments:     return: ConfigService_Status_t;    pinId: uint8_t;    pConfig: const ConfigService_DigitalPinConfig_t*;

        Stores the configuration for the specified digital I/O pin.

        **Arguments:**

        - **pinId**: Digital pin index (0 to CONFIG_SERVICE_CFG_MAX_PINS-1).
        - **pConfig**: Pointer to the digital pin configuration structure.

        **Return values:** CONFIG_SERVICE_STATUS_OK on success, CONFIG_SERVICE_STATUS_INVALID_PARAM for invalid pin or NULL pointer.

        **Restrictions:** None.

    ..  sw-ifelement:: ConfigServiceUnit_GetDigitalPinConfig()
        :arguments:     return: ConfigService_Status_t;    pinId: uint8_t;    pConfig: ConfigService_DigitalPinConfig_t*;

        Reads back the configuration for the specified digital I/O pin.

        **Arguments:**

        - **pinId**: Digital pin index (0 to CONFIG_SERVICE_CFG_MAX_PINS-1).
        - **pConfig**: Pointer to the structure to receive the digital pin configuration.

        **Return values:** CONFIG_SERVICE_STATUS_OK on success, CONFIG_SERVICE_STATUS_INVALID_PARAM for invalid pin or NULL pointer.

        **Restrictions:** None.

    ..  sw-ifelement:: ConfigServiceUnit_SetPwmConfig()
        :arguments:     return: ConfigService_Status_t;    channelId: uint8_t;    pConfig: const ConfigService_PwmConfig_t*;

        Stores the configuration for the specified PWM output channel.

        **Arguments:**

        - **channelId**: PWM channel index (0 to CONFIG_SERVICE_CFG_MAX_CHANNELS-1).
        - **pConfig**: Pointer to the PWM configuration structure.

        **Return values:** CONFIG_SERVICE_STATUS_OK on success, CONFIG_SERVICE_STATUS_INVALID_PARAM for invalid channel or NULL pointer.

        **Restrictions:** None.

    ..  sw-ifelement:: ConfigServiceUnit_GetPwmConfig()
        :arguments:     return: ConfigService_Status_t;    channelId: uint8_t;    pConfig: ConfigService_PwmConfig_t*;

        Reads back the configuration for the specified PWM output channel.

        **Arguments:**

        - **channelId**: PWM channel index (0 to CONFIG_SERVICE_CFG_MAX_CHANNELS-1).
        - **pConfig**: Pointer to the structure to receive the PWM configuration.

        **Return values:** CONFIG_SERVICE_STATUS_OK on success, CONFIG_SERVICE_STATUS_INVALID_PARAM for invalid channel or NULL pointer.

        **Restrictions:** None.

    ..  sw-ifelement:: ConfigServiceUnit_SetI2cConfig()
        :arguments:     return: ConfigService_Status_t;    pConfig: const ConfigService_I2cConfig_t*;

        Stores the I2C bus configuration (speed, address mode, timeout).

        **Arguments:**

        - **pConfig**: Pointer to the I2C configuration structure.

        **Return values:** CONFIG_SERVICE_STATUS_OK on success, CONFIG_SERVICE_STATUS_INVALID_PARAM for NULL or invalid parameters.

        **Restrictions:** None.

    ..  sw-ifelement:: ConfigServiceUnit_GetI2cConfig()
        :arguments:     return: ConfigService_Status_t;    pConfig: ConfigService_I2cConfig_t*;

        Reads back the currently stored I2C bus configuration.

        **Arguments:**

        - **pConfig**: Pointer to the structure to receive the I2C configuration.

        **Return values:** CONFIG_SERVICE_STATUS_OK on success, CONFIG_SERVICE_STATUS_INVALID_PARAM for NULL pointer.

        **Restrictions:** None.

    ..  sw-ifelement:: ConfigServiceUnit_SetSpiConfig()
        :arguments:     return: ConfigService_Status_t;    pConfig: const ConfigService_SpiConfig_t*;

        Stores the SPI bus configuration (clock speed, mode, bit order).

        **Arguments:**

        - **pConfig**: Pointer to the SPI configuration structure.

        **Return values:** CONFIG_SERVICE_STATUS_OK on success, CONFIG_SERVICE_STATUS_INVALID_PARAM for NULL or invalid parameters.

        **Restrictions:** None.

    ..  sw-ifelement:: ConfigServiceUnit_GetSpiConfig()
        :arguments:     return: ConfigService_Status_t;    pConfig: ConfigService_SpiConfig_t*;

        Reads back the currently stored SPI bus configuration.

        **Arguments:**

        - **pConfig**: Pointer to the structure to receive the SPI configuration.

        **Return values:** CONFIG_SERVICE_STATUS_OK on success, CONFIG_SERVICE_STATUS_INVALID_PARAM for NULL pointer.

        **Restrictions:** None.

    ..  sw-ifelement:: ConfigServiceUnit_ValidateAnalogChannelConfig()
        :arguments:     return: ConfigService_Status_t;    pConfig: const ConfigService_AnalogChannelConfig_t*;

        Validates an analog channel configuration without storing it.

        **Arguments:**

        - **pConfig**: Pointer to the analog channel configuration to validate.

        **Return values:** CONFIG_SERVICE_STATUS_OK if valid, CONFIG_SERVICE_STATUS_INVALID_PARAM if any field is out of range.

        **Restrictions:** None.

    ..  sw-ifelement:: ConfigServiceUnit_ValidatePwmConfig()
        :arguments:     return: ConfigService_Status_t;    pConfig: const ConfigService_PwmConfig_t*;

        Validates a PWM channel configuration without storing it.

        **Arguments:**

        - **pConfig**: Pointer to the PWM configuration to validate.

        **Return values:** CONFIG_SERVICE_STATUS_OK if valid, CONFIG_SERVICE_STATUS_INVALID_PARAM if any field is out of range.

        **Restrictions:** None.

    ..  sw-ifelement:: ConfigServiceUnit_ValidateI2cConfig()
        :arguments:     return: ConfigService_Status_t;    pConfig: const ConfigService_I2cConfig_t*;

        Validates an I2C configuration without storing it.

        **Arguments:**

        - **pConfig**: Pointer to the I2C configuration to validate.

        **Return values:** CONFIG_SERVICE_STATUS_OK if valid, CONFIG_SERVICE_STATUS_INVALID_PARAM if any field is out of range.

        **Restrictions:** None.

    ..  sw-ifelement:: ConfigServiceUnit_ValidateSpiConfig()
        :arguments:     return: ConfigService_Status_t;    pConfig: const ConfigService_SpiConfig_t*;

        Validates a SPI configuration without storing it.

        **Arguments:**

        - **pConfig**: Pointer to the SPI configuration to validate.

        **Return values:** CONFIG_SERVICE_STATUS_OK if valid, CONFIG_SERVICE_STATUS_INVALID_PARAM if any field is out of range.

        **Restrictions:** None.


Requirements
************

.. toctree::
    :maxdepth: 1

    ./1_swcReq/configServiceReq.rst


Design documentation
********************

.. toctree::
    :maxdepth: 1

    ./2_design/configServiceComp.rst


Code documentation
******************

.. toctree::
    :maxdepth: 1

    ./2_design/configServiceCfg.rst
    ./2_design/configServiceUnit.rst
