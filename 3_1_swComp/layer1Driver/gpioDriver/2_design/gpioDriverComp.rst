#################################
What is this component about?
#################################

The GPIO Driver abstracts platform GPIO configuration and I/O operations.


#################################
Static structure
#################################

..  uml:: gpioDriverStaticStructure.puml

Public interfaces
#################################

..  sw-if:: gpioDriverUnit.h
    :id: SWIF_GPIODRIVER

    Public interface of gpioDriverUnit.

    ..  sw-ifelement:: GpioDriverUnit_Init()
        :id: SWIFE_GPIODRIVER_INIT
        :arguments:     return: GpioDriver_Status_t;    pConfig: const GpioDriver_Config_t*;

        Initializes the GPIO peripheral with the provided configuration structure.

        **Arguments:**

        - **pConfig**: Pointer to GPIO driver configuration structure (enableInterrupts, enableCallbacks).

        **Return values:** BPB_GPIO_STATUS_OK on success, BPB_GPIO_STATUS_INVALID_PIN for NULL config.

        **Restrictions:** Must be called before any other GPIO driver function.

    ..  sw-ifelement:: GpioDriverUnit_ConfigurePin()
        :id: SWIFE_GPIODRIVER_CONFIGUREPIN
        :arguments:     return: GpioDriver_Status_t;    pin: GpioDriver_Pin_t;    pConfig: const GpioDriver_PinConfig_t*;

        Configures a GPIO pin with the specified mode, pull, speed, and drive capability.

        **Arguments:**

        - **pin**: The GPIO pin identifier to configure.
        - **pConfig**: Pointer to a pin configuration structure (mode, pull, speed, drive capability).

        **Return values:** BPB_GPIO_STATUS_OK on success, BPB_GPIO_STATUS_INVALID_PIN for an invalid pin or NULL pointer.

        **Restrictions:** None.

    ..  sw-ifelement:: GpioDriverUnit_SetMode()
        :id: SWIFE_GPIODRIVER_SETMODE
        :arguments:     return: GpioDriver_Status_t;    pin: GpioDriver_Pin_t;    mode: GpioDriver_Mode_t;

        Sets the direction mode of a GPIO pin (input, output, alternate, analog).

        **Arguments:**

        - **pin**: The GPIO pin to configure.
        - **mode**: Pin mode (BPB_GPIO_MODE_INPUT, BPB_GPIO_MODE_OUTPUT, BPB_GPIO_MODE_ALTERNATE, BPB_GPIO_MODE_ANALOG).

        **Return values:** BPB_GPIO_STATUS_OK on success, BPB_GPIO_STATUS_INVALID_PIN for an invalid pin.

        **Restrictions:** None.

    ..  sw-ifelement:: GpioDriverUnit_SetPull()
        :id: SWIFE_GPIODRIVER_SETPULL
        :arguments:     return: GpioDriver_Status_t;    pin: GpioDriver_Pin_t;    pull: GpioDriver_Pull_t;

        Configures the internal pull-up or pull-down resistor of a GPIO pin.

        **Arguments:**

        - **pin**: The GPIO pin to configure.
        - **pull**: Pull resistor selection (BPB_GPIO_PULL_NONE, BPB_GPIO_PULL_UP, BPB_GPIO_PULL_DOWN).

        **Return values:** BPB_GPIO_STATUS_OK on success, BPB_GPIO_STATUS_INVALID_PIN for an invalid pin.

        **Restrictions:** None.

    ..  sw-ifelement:: GpioDriverUnit_SetSpeed()
        :id: SWIFE_GPIODRIVER_SETSPEED
        :arguments:     return: GpioDriver_Status_t;    pin: GpioDriver_Pin_t;    speed: GpioDriver_Speed_t;

        Sets the output slew-rate speed of a GPIO pin.

        **Arguments:**

        - **pin**: The GPIO pin to configure.
        - **speed**: Slew-rate speed selection (BPB_GPIO_SPEED_LOW, BPB_GPIO_SPEED_MEDIUM, BPB_GPIO_SPEED_HIGH, BPB_GPIO_SPEED_VERY_HIGH).

        **Return values:** BPB_GPIO_STATUS_OK on success, BPB_GPIO_STATUS_INVALID_PIN for an invalid pin.

        **Restrictions:** None.

    ..  sw-ifelement:: GpioDriverUnit_SetIOCapability()
        :id: SWIFE_GPIODRIVER_SETIOCAPABILITY
        :arguments:     return: GpioDriver_Status_t;    pin: GpioDriver_Pin_t;    capability: GpioDriver_IOCapability_t;

        Sets the drive strength capability of a GPIO pin.

        **Arguments:**

        - **pin**: The GPIO pin to configure.
        - **capability**: Drive strength selection.

        **Return values:** BPB_GPIO_STATUS_OK on success, BPB_GPIO_STATUS_INVALID_PIN for an invalid pin.

        **Restrictions:** None.

    ..  sw-ifelement:: GpioDriverUnit_WritePin()
        :id: SWIFE_GPIODRIVER_WRITEPIN
        :arguments:     return: GpioDriver_Status_t;    pin: GpioDriver_Pin_t;    state: GpioDriver_State_t;

        Writes a logical state (HIGH or LOW) to a GPIO output pin.

        **Arguments:**

        - **pin**: The GPIO output pin to write.
        - **state**: Logical state to write (BPB_GPIO_STATE_LOW or BPB_GPIO_STATE_HIGH).

        **Return values:** BPB_GPIO_STATUS_OK on success, BPB_GPIO_STATUS_INVALID_PIN for an invalid pin.

        **Restrictions:** The pin must be configured as output before calling this function.

    ..  sw-ifelement:: GpioDriverUnit_ReadPin()
        :id: SWIFE_GPIODRIVER_READPIN
        :arguments:     return: GpioDriver_Status_t;    pin: GpioDriver_Pin_t;    pState: GpioDriver_State_t*;

        Reads the current logical state of a GPIO pin.

        **Arguments:**

        - **pin**: The GPIO pin to read.
        - **pState**: Pointer to store the read state (BPB_GPIO_STATE_LOW or BPB_GPIO_STATE_HIGH).

        **Return values:** BPB_GPIO_STATUS_OK on success, BPB_GPIO_STATUS_INVALID_PIN for an invalid pin or NULL pointer.

        **Restrictions:** None.

    ..  sw-ifelement:: GpioDriverUnit_TogglePin()
        :id: SWIFE_GPIODRIVER_TOGGLEPIN
        :arguments:     return: GpioDriver_Status_t;    pin: GpioDriver_Pin_t;

        Toggles the state of a GPIO output pin.

        **Arguments:**

        - **pin**: The GPIO output pin to toggle.

        **Return values:** BPB_GPIO_STATUS_OK on success, BPB_GPIO_STATUS_INVALID_PIN for an invalid pin.

        **Restrictions:** The pin must be configured as output before calling this function.

    ..  sw-ifelement:: GpioDriverUnit_EnableInterrupt()
        :id: SWIFE_GPIODRIVER_ENABLEINTERRUPT
        :arguments:     return: GpioDriver_Status_t;    pin: GpioDriver_Pin_t;    edge: GpioDriver_InterruptEdge_t;    callback: GpioDriver_InterruptCallback_t;

        Enables an edge-triggered interrupt on a GPIO pin and registers a callback.

        **Arguments:**

        - **pin**: The GPIO pin on which to enable the interrupt.
        - **edge**: Edge trigger selection (GPIO_EDGE_RISING, GPIO_EDGE_FALLING, GPIO_EDGE_BOTH).
        - **callback**: Function pointer invoked when the interrupt fires. Pass NULL to clear the callback.

        **Return values:** BPB_GPIO_STATUS_OK on success, BPB_GPIO_STATUS_INVALID_PIN for an invalid pin.

        **Restrictions:** GpioDriverUnit_Init() must have been called with enableInterrupts = true. Callback is invoked from interrupt context and must be short and non-blocking.

    ..  sw-ifelement:: GpioDriverUnit_DisableInterrupt()
        :id: SWIFE_GPIODRIVER_DISABLEINTERRUPT
        :arguments:     return: GpioDriver_Status_t;    pin: GpioDriver_Pin_t;

        Disables the interrupt on a GPIO pin.

        **Arguments:**

        - **pin**: The GPIO pin whose interrupt shall be disabled.

        **Return values:** BPB_GPIO_STATUS_OK on success, BPB_GPIO_STATUS_INVALID_PIN for an invalid pin.

        **Restrictions:** None.

    ..  sw-ifelement:: GpioDriverUnit_DeInit()
        :id: SWIFE_GPIODRIVER_DEINIT
        :arguments:     return: GpioDriver_Status_t;

        De-initializes the GPIO peripheral and releases resources.

        **Arguments:** None.

        **Return values:** BPB_GPIO_STATUS_OK on success.

        **Restrictions:** None.

#################################


Dynamic behaviour
#################################

* State machine diagram
..  uml:: gpioDriverStateMachine.puml

* Sequence diagram
..  uml:: gpioDriverSequenceDiagram.puml


#################################
Design chooices
#################################
Description:
************
Provide a thin hardware abstraction for GPIO configuration and I/O.

Assumptions and influencing factors:
************************************
* Vendor HAL is available for actual pin operations.

Solutions list:
***************
Solution 1 - HAL wrapper
Expose minimal wrapper APIs for GPIO access.

Solution 2 - Direct register access
Implement direct register manipulation per platform.

Solution evaluation:
********************
HAL wrapper improves portability across targets.

Final solution:
****************
Solution 1 selected for portability and maintainability.
