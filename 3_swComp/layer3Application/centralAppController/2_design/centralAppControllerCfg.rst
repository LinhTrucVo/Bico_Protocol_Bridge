centralAppControllerCfg.h
########################

Defines compile-time feature flags for the Central Application Controller:

- ``CAC_CFG_ENABLE_ERROR_LOGGING``: Enables error logging on dispatch failures.
- ``CAC_CFG_ENABLE_NRC_DETAIL``: Enables detailed NRC reporting (specific NRC per failure mode).

DID Allocation:
- 0x1001 = ADC Sample Rate
- 0x1002 = ADC Resolution
- 0x2001 = GPIO Configuration
- 0x3001 = PWM Configuration
- 0x4001 = I2C Configuration
- 0x5001 = SPI Configuration
- 0x6001 = Serial Configuration

RID Allocation:
- 0x01xx = ADC operations
- 0x02xx = GPIO operations
- 0x03xx = PWM operations
- 0x04xx = I2C operations
- 0x05xx = SPI operations

..  doxygenfile::  centralAppControllerCfg.h
    :project: CentralAppController