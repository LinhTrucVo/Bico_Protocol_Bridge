serialDriverCfg.h
########################

Defines compile-time feature flags and tuning parameters for the Serial Driver.

Feature Flags
*************

- ``SERIAL_CFG_ENABLE_DMA``: Enables DMA-based transmit and receive transfers. When disabled, interrupt mode is used.
- ``SERIAL_CFG_ENABLE_CALLBACKS``: Enables RX and TX complete callback registration for asynchronous notification.
- ``SERIAL_CFG_ENABLE_FLOW_CONTROL``: Enables hardware (RTS/CTS) and software (XON/XOFF) flow control.
- ``SERIAL_CFG_ENABLE_ERROR_CALLBACK``: Enables error event callback for overrun, framing, and parity errors.

Timing Configuration
********************

- ``SERIAL_CFG_DEFAULT_TIMEOUT_MS``: Default timeout for Send/Receive operations when no explicit timeout is specified (default: 100 ms).

Supported Baud Rates
********************

The following baud rates are supported (configurable at runtime):

- 9600 bps
- 19200 bps
- 38400 bps
- 57600 bps
- 115200 bps
- 230400 bps
- 460800 bps
- 921600 bps

..  doxygenfile::  serialDriverCfg.h
    :project: SerialDriver
