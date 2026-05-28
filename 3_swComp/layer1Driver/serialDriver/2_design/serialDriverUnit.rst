..  c:namespace:: SerialDriver

serialDriverUnit.c
###########################

Hardware abstraction layer for serial communication (UART), providing low-level interface for asynchronous serial data transmission and reception.

Key implementation details:

- Wraps vendor UART HAL for portability across MCU platforms.
- Does not manage internal buffers — data is transferred directly between caller-provided buffers and HAL.
- Supports both interrupt-driven and DMA-based transfer modes (compile-time selectable).
- Provides timeout-based blocking API with HAL abort on timeout expiry.
- Validates all input parameters at API boundary (NULL pointers, zero lengths, unsupported values).
- Callbacks are invoked from ISR context; implementations must be short and non-blocking.

Internal functions:

- ``serialDriverUnit_TxCpltHandler()`` – ISR callback updating state and invoking user TX callback.
- ``serialDriverUnit_RxCpltHandler()`` – ISR callback updating state and invoking user RX callback.
- ``serialDriverUnit_ErrorHandler()`` – ISR callback transitioning to ERROR state on UART error.

..  doxygenfile:: serialDriverUnit.c
    :project: SerialDriver
