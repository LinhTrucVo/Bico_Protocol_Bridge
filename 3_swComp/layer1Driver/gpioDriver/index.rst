gpioDriver Software Component
##############################

Introduction
************

The GPIO Driver provides hardware abstraction for General Purpose Input/Output pin management.
It handles GPIO initialization, pin direction configuration, and pin read/write operations.


References
**********

Other relevant documents, e.g. ISO standards, whitepapers, etc.


Static architecture
*******************

Component
=========

..  swc:: gpioDriver
    :provides: gpioDriver.h – GPIO initialization, pin direction configuration, and pin read/write operations.
    :requires: Vendor HAL or register-level GPIO peripheral access.

Public interfaces
=================

..  sw-if:: gpioDriverUnit.h

    Public interface of gpioDriverUnit.

    ..  sw-ifelement:: GpioDriverUnit_Init()
        :arguments:     return: GpioDriver_Status_t;    pConfig: const GpioDriver_Config_t*;

        Initializes the GPIO peripheral with the provided configuration structure.

        **Arguments:**

        - **pConfig**: Pointer to GPIO driver configuration structure (enableInterrupts, enableCallbacks).

        **Return values:** GPIO_STATUS_OK on success, GPIO_STATUS_INVALID_PIN for NULL config.

        **Restrictions:** Must be called before any other GPIO driver function.

    ..  sw-ifelement:: GpioDriverUnit_ConfigurePin()
        :arguments:     return: GpioDriver_Status_t;    pin: GpioDriver_Pin_t;    pConfig: const GpioDriver_PinConfig_t*;

        Configures a GPIO pin with the specified mode, pull, speed, and drive capability.

        **Arguments:**

        - **pin**: The GPIO pin identifier to configure.
        - **pConfig**: Pointer to a pin configuration structure (mode, pull, speed, drive capability).

        **Return values:** GPIO_STATUS_OK on success, GPIO_STATUS_INVALID_PIN for an invalid pin or NULL pointer.

        **Restrictions:** None.

    ..  sw-ifelement:: GpioDriverUnit_SetMode()
        :arguments:     return: GpioDriver_Status_t;    pin: GpioDriver_Pin_t;    mode: GpioDriver_Mode_t;

        Sets the direction mode of a GPIO pin (input, output, alternate, analog).

        **Arguments:**

        - **pin**: The GPIO pin to configure.
        - **mode**: Pin mode (GPIO_MODE_INPUT, GPIO_MODE_OUTPUT, GPIO_MODE_ALTERNATE, GPIO_MODE_ANALOG).

        **Return values:** GPIO_STATUS_OK on success, GPIO_STATUS_INVALID_PIN for an invalid pin.

        **Restrictions:** None.

    ..  sw-ifelement:: GpioDriverUnit_SetPull()
        :arguments:     return: GpioDriver_Status_t;    pin: GpioDriver_Pin_t;    pull: GpioDriver_Pull_t;

        Configures the internal pull-up or pull-down resistor of a GPIO pin.

        **Arguments:**

        - **pin**: The GPIO pin to configure.
        - **pull**: Pull resistor selection (GPIO_PULL_NONE, GPIO_PULL_UP, GPIO_PULL_DOWN).

        **Return values:** GPIO_STATUS_OK on success, GPIO_STATUS_INVALID_PIN for an invalid pin.

        **Restrictions:** None.

    ..  sw-ifelement:: GpioDriverUnit_SetSpeed()
        :arguments:     return: GpioDriver_Status_t;    pin: GpioDriver_Pin_t;    speed: GpioDriver_Speed_t;

        Sets the output slew-rate speed of a GPIO pin.

        **Arguments:**

        - **pin**: The GPIO pin to configure.
        - **speed**: Slew-rate speed selection (GPIO_SPEED_LOW, GPIO_SPEED_MEDIUM, GPIO_SPEED_HIGH, GPIO_SPEED_VERY_HIGH).

        **Return values:** GPIO_STATUS_OK on success, GPIO_STATUS_INVALID_PIN for an invalid pin.

        **Restrictions:** None.

    ..  sw-ifelement:: GpioDriverUnit_SetIOCapability()
        :arguments:     return: GpioDriver_Status_t;    pin: GpioDriver_Pin_t;    capability: GpioDriver_IOCapability_t;

        Sets the drive strength capability of a GPIO pin.

        **Arguments:**

        - **pin**: The GPIO pin to configure.
        - **capability**: Drive strength selection.

        **Return values:** GPIO_STATUS_OK on success, GPIO_STATUS_INVALID_PIN for an invalid pin.

        **Restrictions:** None.

    ..  sw-ifelement:: GpioDriverUnit_WritePin()
        :arguments:     return: GpioDriver_Status_t;    pin: GpioDriver_Pin_t;    state: GpioDriver_State_t;

        Writes a logical state (HIGH or LOW) to a GPIO output pin.

        **Arguments:**

        - **pin**: The GPIO output pin to write.
        - **state**: Logical state to write (GPIO_STATE_LOW or GPIO_STATE_HIGH).

        **Return values:** GPIO_STATUS_OK on success, GPIO_STATUS_INVALID_PIN for an invalid pin.

        **Restrictions:** The pin must be configured as output before calling this function.

    ..  sw-ifelement:: GpioDriverUnit_ReadPin()
        :arguments:     return: GpioDriver_Status_t;    pin: GpioDriver_Pin_t;    pState: GpioDriver_State_t*;

        Reads the current logical state of a GPIO pin.

        **Arguments:**

        - **pin**: The GPIO pin to read.
        - **pState**: Pointer to store the read state (GPIO_STATE_LOW or GPIO_STATE_HIGH).

        **Return values:** GPIO_STATUS_OK on success, GPIO_STATUS_INVALID_PIN for an invalid pin or NULL pointer.

        **Restrictions:** None.

    ..  sw-ifelement:: GpioDriverUnit_TogglePin()
        :arguments:     return: GpioDriver_Status_t;    pin: GpioDriver_Pin_t;

        Toggles the state of a GPIO output pin.

        **Arguments:**

        - **pin**: The GPIO output pin to toggle.

        **Return values:** GPIO_STATUS_OK on success, GPIO_STATUS_INVALID_PIN for an invalid pin.

        **Restrictions:** The pin must be configured as output before calling this function.

    ..  sw-ifelement:: GpioDriverUnit_EnableInterrupt()
        :arguments:     return: GpioDriver_Status_t;    pin: GpioDriver_Pin_t;    edge: GpioDriver_InterruptEdge_t;    callback: GpioDriver_InterruptCallback_t;

        Enables an edge-triggered interrupt on a GPIO pin and registers a callback.

        **Arguments:**

        - **pin**: The GPIO pin on which to enable the interrupt.
        - **edge**: Edge trigger selection (GPIO_EDGE_RISING, GPIO_EDGE_FALLING, GPIO_EDGE_BOTH).
        - **callback**: Function pointer invoked when the interrupt fires. Pass NULL to clear the callback.

        **Return values:** GPIO_STATUS_OK on success, GPIO_STATUS_INVALID_PIN for an invalid pin.

        **Restrictions:** GpioDriverUnit_Init() must have been called with enableInterrupts = true. Callback is invoked from interrupt context and must be short and non-blocking.

    ..  sw-ifelement:: GpioDriverUnit_DisableInterrupt()
        :arguments:     return: GpioDriver_Status_t;    pin: GpioDriver_Pin_t;

        Disables the interrupt on a GPIO pin.

        **Arguments:**

        - **pin**: The GPIO pin whose interrupt shall be disabled.

        **Return values:** GPIO_STATUS_OK on success, GPIO_STATUS_INVALID_PIN for an invalid pin.

        **Restrictions:** None.

    ..  sw-ifelement:: GpioDriverUnit_DeInit()
        :arguments:     return: GpioDriver_Status_t;

        De-initializes the GPIO peripheral and releases resources.

        **Arguments:** None.

        **Return values:** GPIO_STATUS_OK on success.

        **Restrictions:** None.


Requirements
************

.. toctree::
    :maxdepth: 1

    ./1_swcReq/gpioDriverReq.rst


Design documentation
********************

.. toctree::
    :maxdepth: 1

    ./2_design/gpioDriverComp.rst


Code documentation
******************

.. toctree::
    :maxdepth: 1

    ./2_design/gpioDriverCfg.rst
    ./2_design/gpioDriverUnit.rst
