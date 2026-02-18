.. Descrive about the GPIO Driver component requirements
Overall requirements
********************

The GPIO Driver shall provide a hardware abstraction for GPIO configuration and I/O operations.
The component shall support input, output, and interrupt modes.

Input validation
****************

The component shall validate pin IDs and configuration parameters.
The component shall reject operations when the driver is not initialized.

Requirements for component
**************************

Req-gpioDriver-001: The component shall configure a GPIO pin with mode, pull, and drive strength.
   Verification: ConfigurePin applies the requested configuration for valid pins.

Req-gpioDriver-002: The component shall write a digital state to a GPIO pin.
   Verification: WritePin sets the pin to HIGH or LOW as requested.

Req-gpioDriver-003: The component shall read a digital state from a GPIO pin.
   Verification: ReadPin returns the current state for a valid pin.

Req-gpioDriver-004: The component shall toggle a GPIO pin state.
   Verification: TogglePin changes pin state from high to low or low to high.

Req-gpioDriver-005: The component shall enable and disable GPIO interrupts.
   Verification: EnableInterrupt registers a callback and DisableInterrupt stops it.

Req-gpioDriver-006: The component shall return INVALID_PIN for invalid pin IDs.
   Verification: APIs return INVALID_PIN for out-of-range pins.

Req-gpioDriver-007: The component shall set IO drive capacity (LV0, LV1, LV2, LV3) for a GPIO pin.
   Verification: SetIOCapability applies the requested drive capacity level (higher LV = higher driving capacity) for valid pins.
