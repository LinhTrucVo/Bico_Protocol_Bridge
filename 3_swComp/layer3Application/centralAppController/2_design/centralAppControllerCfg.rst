centralAppControllerCfg.h
########################

Defines compile-time feature flags for the Central Application Controller:

- ``CAC_CFG_ENABLE_ERROR_LOGGING``: Enables error logging on dispatch failures.
- ``CAC_CFG_ENABLE_NRC_DETAIL``: Enables detailed NRC reporting (specific NRC per failure mode).
- ``CENTRAL_APP_CFG_MAX_FRAME_SIZE``: Maximum request/response frame size (default 256 bytes).
- ``CENTRAL_APP_CFG_RESPONSE_TIMEOUT_MS``: Response timeout in ms (default 10).

DID Allocation:
- 0x1001 = ADC Sample Rate
- 0x1002 = ADC Resolution
- 0x2001 = GPIO Configuration
- 0x3001 = PWM Configuration
- 0x4001 = I2C Configuration
- 0x5001 = SPI Configuration
- 0x6001 = Serial Configuration

RID Allocation:
- 0x0100 = ADC Read Channel
- 0x0200 = GPIO Write
- 0x0201 = GPIO Read
- 0x0300 = PWM Start
- 0x0301 = PWM Stop
- 0x0400 = I2C Write
- 0x0401 = I2C Read
- 0x0500 = SPI Write
- 0x0501 = SPI Transceive

..  doxygenfile::  centralAppControllerCfg.h
    :project: CentralAppController