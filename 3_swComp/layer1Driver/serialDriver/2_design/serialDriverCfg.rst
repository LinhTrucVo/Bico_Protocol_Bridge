serialDriverCfg.h
########################

Defines compile-time feature flags for the Serial Driver:

- ``SERIAL_CFG_ENABLE_DMA``: Enables DMA-based transmit and receive transfers.
- ``SERIAL_CFG_ENABLE_CALLBACKS``: Enables RX and TX complete callback registration.
- ``SERIAL_CFG_ENABLE_FLOW_CONTROL``: Enables hardware (RTS/CTS) and software (XON/XOFF) flow control.

..  doxygenfile::  serialDriverCfg.h
    :project: SerialDriver
