serialToI2CAppCfg.h
########################

Defines compile-time feature flags for the Serial-to-I2C Application:

- ``SERIAL_TO_I2C_CFG_ENABLE_MASTER``: Enables I2C master transaction support (write, read, write-read).
- ``SERIAL_TO_I2C_CFG_ENABLE_SLAVE``: Enables I2C slave mode support (disabled by default).

..  doxygenfile::  serialToI2CAppCfg.h
    :project: SerialToI2CApp
