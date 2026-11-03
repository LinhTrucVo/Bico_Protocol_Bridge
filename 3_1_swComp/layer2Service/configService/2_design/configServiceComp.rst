#################################
What is this component about?
#################################

The Config Service stores and validates configuration for analog, digital, PWM, I2C, SPI, and serial settings.
It provides centralized validation and access APIs for other modules.


#################################
Static structure
#################################

Files:
* configService.h
* configServiceCfg.h
* configServiceUnit.c

..  uml::

	@startuml
	class ConfigStore
	ConfigStore : serial
	ConfigStore : analog
	ConfigStore : digital
	ConfigStore : pwm
	ConfigStore : i2c
	ConfigStore : spi
	@enduml

Public interfaces
#################################

..  sw-if:: configServiceUnit.h
    :id: SWIF_CONFIGSERVICE

    Public interface of configServiceUnit.

    ..  sw-ifelement:: ConfigServiceUnit_Init()
        :id: SWIFE_CONFIGSERVICE_INIT
        :arguments:     return: ConfigService_Status_t;

        Initializes the Config Service and sets all configuration parameters to defaults.

        **Arguments:** None.

        **Return values:** BPB_CONFIG_SERVICE_STATUS_OK on success, BPB_CONFIG_SERVICE_STATUS_ERROR on failure.

        **Restrictions:** Must be called before any other Config Service function.

    ..  sw-ifelement:: ConfigServiceUnit_DeInit()
        :id: SWIFE_CONFIGSERVICE_DEINIT
        :arguments:     return: ConfigService_Status_t;

        De-initializes the Config Service and releases resources.

        **Arguments:** None.

        **Return values:** BPB_CONFIG_SERVICE_STATUS_OK on success.

        **Restrictions:** None.

    ..  sw-ifelement:: ConfigServiceUnit_SetSerialConfig()
        :id: SWIFE_CONFIGSERVICE_SETSERIALCONFIG
        :arguments:     return: ConfigService_Status_t;    pConfig: const ConfigService_SerialConfig_t*;

        Stores the serial port configuration (baudrate, data bits, stop bits, parity).

        **Arguments:**

        - **pConfig**: Pointer to the serial configuration structure to store.

        **Return values:** BPB_CONFIG_SERVICE_STATUS_OK on success, BPB_CONFIG_SERVICE_STATUS_INVALID_PARAM for NULL or invalid parameters.

        **Restrictions:** None.

    ..  sw-ifelement:: ConfigServiceUnit_GetSerialConfig()
        :id: SWIFE_CONFIGSERVICE_GETSERIALCONFIG
        :arguments:     return: ConfigService_Status_t;    pConfig: ConfigService_SerialConfig_t*;

        Reads back the currently stored serial port configuration.

        **Arguments:**

        - **pConfig**: Pointer to the structure to receive the serial configuration.

        **Return values:** BPB_CONFIG_SERVICE_STATUS_OK on success, BPB_CONFIG_SERVICE_STATUS_INVALID_PARAM for NULL pointer.

        **Restrictions:** None.

    ..  sw-ifelement:: ConfigServiceUnit_SetAnalogChannelConfig()
        :id: SWIFE_CONFIGSERVICE_SETANALOGCHANNELCONFIG
        :arguments:     return: ConfigService_Status_t;    channelId: uint8_t;    pConfig: const ConfigService_AnalogChannelConfig_t*;

        Stores the configuration for the specified analog input channel.

        **Arguments:**

        - **channelId**: Analog channel index (0 to BPB_CONFIG_SERVICE_CFG_MAX_CHANNELS-1).
        - **pConfig**: Pointer to the analog channel configuration structure.

        **Return values:** BPB_CONFIG_SERVICE_STATUS_OK on success, BPB_CONFIG_SERVICE_STATUS_INVALID_PARAM for invalid channel or NULL pointer.

        **Restrictions:** None.

    ..  sw-ifelement:: ConfigServiceUnit_GetAnalogChannelConfig()
        :id: SWIFE_CONFIGSERVICE_GETANALOGCHANNELCONFIG
        :arguments:     return: ConfigService_Status_t;    channelId: uint8_t;    pConfig: ConfigService_AnalogChannelConfig_t*;

        Reads back the configuration for the specified analog input channel.

        **Arguments:**

        - **channelId**: Analog channel index (0 to BPB_CONFIG_SERVICE_CFG_MAX_CHANNELS-1).
        - **pConfig**: Pointer to the structure to receive the analog channel configuration.

        **Return values:** BPB_CONFIG_SERVICE_STATUS_OK on success, BPB_CONFIG_SERVICE_STATUS_INVALID_PARAM for invalid channel or NULL pointer.

        **Restrictions:** None.

    ..  sw-ifelement:: ConfigServiceUnit_SetDigitalPinConfig()
        :id: SWIFE_CONFIGSERVICE_SETDIGITALPINCONFIG
        :arguments:     return: ConfigService_Status_t;    pinId: uint8_t;    pConfig: const ConfigService_DigitalPinConfig_t*;

        Stores the configuration for the specified digital I/O pin.

        **Arguments:**

        - **pinId**: Digital pin index (0 to BPB_CONFIG_SERVICE_CFG_MAX_PINS-1).
        - **pConfig**: Pointer to the digital pin configuration structure.

        **Return values:** BPB_CONFIG_SERVICE_STATUS_OK on success, BPB_CONFIG_SERVICE_STATUS_INVALID_PARAM for invalid pin or NULL pointer.

        **Restrictions:** None.

    ..  sw-ifelement:: ConfigServiceUnit_GetDigitalPinConfig()
        :id: SWIFE_CONFIGSERVICE_GETDIGITALPINCONFIG
        :arguments:     return: ConfigService_Status_t;    pinId: uint8_t;    pConfig: ConfigService_DigitalPinConfig_t*;

        Reads back the configuration for the specified digital I/O pin.

        **Arguments:**

        - **pinId**: Digital pin index (0 to BPB_CONFIG_SERVICE_CFG_MAX_PINS-1).
        - **pConfig**: Pointer to the structure to receive the digital pin configuration.

        **Return values:** BPB_CONFIG_SERVICE_STATUS_OK on success, BPB_CONFIG_SERVICE_STATUS_INVALID_PARAM for invalid pin or NULL pointer.

        **Restrictions:** None.

    ..  sw-ifelement:: ConfigServiceUnit_SetPwmConfig()
        :id: SWIFE_CONFIGSERVICE_SETPWMCONFIG
        :arguments:     return: ConfigService_Status_t;    channelId: uint8_t;    pConfig: const ConfigService_PwmConfig_t*;

        Stores the configuration for the specified PWM output channel.

        **Arguments:**

        - **channelId**: PWM channel index (0 to BPB_CONFIG_SERVICE_CFG_MAX_CHANNELS-1).
        - **pConfig**: Pointer to the PWM configuration structure.

        **Return values:** BPB_CONFIG_SERVICE_STATUS_OK on success, BPB_CONFIG_SERVICE_STATUS_INVALID_PARAM for invalid channel or NULL pointer.

        **Restrictions:** None.

    ..  sw-ifelement:: ConfigServiceUnit_GetPwmConfig()
        :id: SWIFE_CONFIGSERVICE_GETPWMCONFIG
        :arguments:     return: ConfigService_Status_t;    channelId: uint8_t;    pConfig: ConfigService_PwmConfig_t*;

        Reads back the configuration for the specified PWM output channel.

        **Arguments:**

        - **channelId**: PWM channel index (0 to BPB_CONFIG_SERVICE_CFG_MAX_CHANNELS-1).
        - **pConfig**: Pointer to the structure to receive the PWM configuration.

        **Return values:** BPB_CONFIG_SERVICE_STATUS_OK on success, BPB_CONFIG_SERVICE_STATUS_INVALID_PARAM for invalid channel or NULL pointer.

        **Restrictions:** None.

    ..  sw-ifelement:: ConfigServiceUnit_SetI2cConfig()
        :id: SWIFE_CONFIGSERVICE_SETI2CCONFIG
        :arguments:     return: ConfigService_Status_t;    pConfig: const ConfigService_I2cConfig_t*;

        Stores the I2C bus configuration (speed, address mode, timeout).

        **Arguments:**

        - **pConfig**: Pointer to the I2C configuration structure.

        **Return values:** BPB_CONFIG_SERVICE_STATUS_OK on success, BPB_CONFIG_SERVICE_STATUS_INVALID_PARAM for NULL or invalid parameters.

        **Restrictions:** None.

    ..  sw-ifelement:: ConfigServiceUnit_GetI2cConfig()
        :id: SWIFE_CONFIGSERVICE_GETI2CCONFIG
        :arguments:     return: ConfigService_Status_t;    pConfig: ConfigService_I2cConfig_t*;

        Reads back the currently stored I2C bus configuration.

        **Arguments:**

        - **pConfig**: Pointer to the structure to receive the I2C configuration.

        **Return values:** BPB_CONFIG_SERVICE_STATUS_OK on success, BPB_CONFIG_SERVICE_STATUS_INVALID_PARAM for NULL pointer.

        **Restrictions:** None.

    ..  sw-ifelement:: ConfigServiceUnit_SetSpiConfig()
        :id: SWIFE_CONFIGSERVICE_SETSPICONFIG
        :arguments:     return: ConfigService_Status_t;    pConfig: const ConfigService_SpiConfig_t*;

        Stores the SPI bus configuration (clock speed, mode, bit order).

        **Arguments:**

        - **pConfig**: Pointer to the SPI configuration structure.

        **Return values:** BPB_CONFIG_SERVICE_STATUS_OK on success, BPB_CONFIG_SERVICE_STATUS_INVALID_PARAM for NULL or invalid parameters.

        **Restrictions:** None.

    ..  sw-ifelement:: ConfigServiceUnit_GetSpiConfig()
        :id: SWIFE_CONFIGSERVICE_GETSPICONFIG
        :arguments:     return: ConfigService_Status_t;    pConfig: ConfigService_SpiConfig_t*;

        Reads back the currently stored SPI bus configuration.

        **Arguments:**

        - **pConfig**: Pointer to the structure to receive the SPI configuration.

        **Return values:** BPB_CONFIG_SERVICE_STATUS_OK on success, BPB_CONFIG_SERVICE_STATUS_INVALID_PARAM for NULL pointer.

        **Restrictions:** None.

    ..  sw-ifelement:: ConfigServiceUnit_ValidateAnalogChannelConfig()
        :id: SWIFE_CONFIGSERVICE_VALIDATEANALOGCHANNELCONFIG
        :arguments:     return: ConfigService_Status_t;    pConfig: const ConfigService_AnalogChannelConfig_t*;

        Validates an analog channel configuration without storing it.

        **Arguments:**

        - **pConfig**: Pointer to the analog channel configuration to validate.

        **Return values:** BPB_CONFIG_SERVICE_STATUS_OK if valid, BPB_CONFIG_SERVICE_STATUS_INVALID_PARAM if any field is out of range.

        **Restrictions:** None.

    ..  sw-ifelement:: ConfigServiceUnit_ValidatePwmConfig()
        :id: SWIFE_CONFIGSERVICE_VALIDATEPWMCONFIG
        :arguments:     return: ConfigService_Status_t;    pConfig: const ConfigService_PwmConfig_t*;

        Validates a PWM channel configuration without storing it.

        **Arguments:**

        - **pConfig**: Pointer to the PWM configuration to validate.

        **Return values:** BPB_CONFIG_SERVICE_STATUS_OK if valid, BPB_CONFIG_SERVICE_STATUS_INVALID_PARAM if any field is out of range.

        **Restrictions:** None.

    ..  sw-ifelement:: ConfigServiceUnit_ValidateI2cConfig()
        :id: SWIFE_CONFIGSERVICE_VALIDATEI2CCONFIG
        :arguments:     return: ConfigService_Status_t;    pConfig: const ConfigService_I2cConfig_t*;

        Validates an I2C configuration without storing it.

        **Arguments:**

        - **pConfig**: Pointer to the I2C configuration to validate.

        **Return values:** BPB_CONFIG_SERVICE_STATUS_OK if valid, BPB_CONFIG_SERVICE_STATUS_INVALID_PARAM if any field is out of range.

        **Restrictions:** None.

    ..  sw-ifelement:: ConfigServiceUnit_ValidateSpiConfig()
        :id: SWIFE_CONFIGSERVICE_VALIDATESPICONFIG
        :arguments:     return: ConfigService_Status_t;    pConfig: const ConfigService_SpiConfig_t*;

        Validates a SPI configuration without storing it.

        **Arguments:**

        - **pConfig**: Pointer to the SPI configuration to validate.

        **Return values:** BPB_CONFIG_SERVICE_STATUS_OK if valid, BPB_CONFIG_SERVICE_STATUS_INVALID_PARAM if any field is out of range.

        **Restrictions:** None.

#################################


Dynamic behaviour
#################################

* State machine diagram
..  uml::

	@startuml
	[*] --> Idle
	Idle --> Validating : SetConfig
	Validating --> Idle : Valid
	Validating --> Error : Invalid
	Error --> Idle
	@enduml

* Sequence diagram
..  uml::

	@startuml
	actor App
	participant Config
	App -> Config : SetAnalogChannelConfig()
	Config -> Config : Validate
	Config --> App : Status
	@enduml


#################################
What is this component about?
#################################

The Config Service manages configuration parameters across components.


#################################
Static structure
#################################

..  uml:: configServiceStaticStructure.puml


#################################
Dynamic behaviour
#################################

* State machine diagram
..  uml:: configServiceStateMachine.puml

* Sequence diagram
..  uml:: configServiceSequenceDiagram.puml


#################################
Design chooices
#################################
Description:
************
Provide centralized storage and validation for configuration parameters.

Assumptions and influencing factors:
************************************
* NVM is used for persistence when enabled.

Solutions list:
***************
Solution 1 - Key/value storage
Simple key/value with validation rules.

Solution 2 - Structured config blobs
Store binary configuration structs per module.

Solution evaluation:
********************
Key/value storage provides flexibility with small memory impact.

Final solution:
****************
Solution 1 selected for flexibility.
