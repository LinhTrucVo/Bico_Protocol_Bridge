// This file is used to define the public interface of the component unit.
// It contains public macros, types, variables, and function prototypes that shall be included in component headers file (gpioDriver.h)

#ifndef GPIODRIVERUNIT_H
#define GPIODRIVERUNIT_H

//============================================================================
// Dependencies
//============================================================================
#include <stdint.h>
#include <stdbool.h>
#include "gpioDriverCfg.h"

//============================================================================
// Public Macros
//============================================================================
#define GPIO_MAX_PINS            32

//============================================================================
// Public Types
//============================================================================
typedef enum
{
    GPIO_STATUS_OK = 0,
    GPIO_STATUS_ERROR,
    GPIO_STATUS_INVALID_PIN,
    GPIO_STATUS_INVALID_MODE,
    GPIO_STATUS_NOT_INITIALIZED
} GpioDriver_Status_t;

typedef enum
{
    GPIO_MODE_INPUT = 0,
    GPIO_MODE_OUTPUT,
    GPIO_MODE_ALTERNATE,
    GPIO_MODE_ANALOG
} GpioDriver_Mode_t;

typedef enum
{
    GPIO_STATE_LOW = 0,
    GPIO_STATE_HIGH = 1
} GpioDriver_State_t;

typedef enum
{
    GPIO_PULL_NONE = 0,
    GPIO_PULL_UP,
    GPIO_PULL_DOWN
} GpioDriver_Pull_t;

typedef enum
{
    GPIO_SPEED_LOW = 0,
    GPIO_SPEED_MEDIUM,
    GPIO_SPEED_HIGH,
    GPIO_SPEED_VERY_HIGH
} GpioDriver_Speed_t;

typedef enum
{
    GPIO_INTERRUPT_RISING = 0,
    GPIO_INTERRUPT_FALLING,
    GPIO_INTERRUPT_BOTH
} GpioDriver_InterruptEdge_t;

typedef enum
{
    GPIO_IO_DRIVE_CAP_LV0 = 0,  // Lowest drive capacity
    GPIO_IO_DRIVE_CAP_LV1,       // Low drive capacity
    GPIO_IO_DRIVE_CAP_LV2,       // Low-medium drive capacity
    GPIO_IO_DRIVE_CAP_LV3,       // Medium-low drive capacity
    GPIO_IO_DRIVE_CAP_LV4,       // Medium-high drive capacity
    GPIO_IO_DRIVE_CAP_LV5,       // High drive capacity
    GPIO_IO_DRIVE_CAP_LV6,       // Very high drive capacity
    GPIO_IO_DRIVE_CAP_LV7        // Highest drive capacity
} GpioDriver_IOCapability_t;

typedef uint8_t GpioDriver_Pin_t;

typedef struct
{
    GpioDriver_Mode_t mode;
    GpioDriver_Pull_t pull;
    GpioDriver_Speed_t speed;
    GpioDriver_State_t initialState;
    GpioDriver_IOCapability_t ioCapability;
} GpioDriver_PinConfig_t;

typedef void (*GpioDriver_InterruptCallback_t)(GpioDriver_Pin_t pin);

//============================================================================
// Public Variables
//============================================================================

//============================================================================
// Public Functions
//============================================================================
GpioDriver_Status_t GpioDriverUnit_Init(void);
GpioDriver_Status_t GpioDriverUnit_ConfigurePin(GpioDriver_Pin_t pin, const GpioDriver_PinConfig_t *pConfig);
GpioDriver_Status_t GpioDriverUnit_SetMode(GpioDriver_Pin_t pin, GpioDriver_Mode_t mode);
GpioDriver_Status_t GpioDriverUnit_SetPull(GpioDriver_Pin_t pin, GpioDriver_Pull_t pull);
GpioDriver_Status_t GpioDriverUnit_SetSpeed(GpioDriver_Pin_t pin, GpioDriver_Speed_t speed);
GpioDriver_Status_t GpioDriverUnit_SetIOCapability(GpioDriver_Pin_t pin, GpioDriver_IOCapability_t capability);
GpioDriver_Status_t GpioDriverUnit_WritePin(GpioDriver_Pin_t pin, GpioDriver_State_t state);
GpioDriver_Status_t GpioDriverUnit_ReadPin(GpioDriver_Pin_t pin, GpioDriver_State_t *pState);
GpioDriver_Status_t GpioDriverUnit_TogglePin(GpioDriver_Pin_t pin);
GpioDriver_Status_t GpioDriverUnit_EnableInterrupt(GpioDriver_Pin_t pin, GpioDriver_InterruptEdge_t edge, GpioDriver_InterruptCallback_t callback);
GpioDriver_Status_t GpioDriverUnit_DisableInterrupt(GpioDriver_Pin_t pin);
GpioDriver_Status_t GpioDriverUnit_DeInit(void);

#endif /* GPIODRIVERUNIT_H */
