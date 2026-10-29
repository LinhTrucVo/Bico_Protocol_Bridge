// This file is used to define the public interface of the component unit.
// It contains public macros, types, variables, and function prototypes that shall be included in component headers file (gpioDriver.h)

#ifndef BPB_GPIODRIVERUNIT_H
#define BPB_GPIODRIVERUNIT_H

//============================================================================
// Dependencies
//============================================================================
#include <stdint.h>
#include <stdbool.h>
#include "gpioDriverCfg.h"

//============================================================================
// Configuration Macros
//============================================================================
#define BPB_GPIO_CFG_MAX_PINS            32
#define BPB_GPIO_CFG_DEFAULT_MODE        BPB_GPIO_MODE_INPUT
#define BPB_GPIO_CFG_DEFAULT_PULL        BPB_GPIO_PULL_NONE
#define BPB_GPIO_CFG_DEFAULT_SPEED       BPB_GPIO_SPEED_LOW
#define BPB_GPIO_CFG_DEFAULT_IO_CAPABILITY BPB_GPIO_IO_DRIVE_CAP_LV0
#define BPB_GPIO_MAX_PINS                32

//============================================================================
// Status Enums
//============================================================================
#define BPB_GPIO_STATUS_OK               GPIOSTATUS_OK
#define BPB_GPIO_STATUS_ERROR            GPIOSTATUS_ERROR
#define BPB_GPIO_STATUS_INVALID_PIN      GPIOSTATUS_INVALID_PIN

//============================================================================
// Public Macros
//============================================================================

//============================================================================
// Public Types
//============================================================================
typedef enum
{
    BPB_GPIO_STATUS_OK = 0,
    BPB_GPIO_STATUS_ERROR,
    BPB_GPIO_STATUS_INVALID_PIN,
    BPB_GPIO_STATUS_INVALID_MODE,
    BPB_GPIO_STATUS_NOT_INITIALIZED
} GpioDriver_Status_t;

typedef enum
{
    BPB_GPIO_MODE_INPUT = 0,
    BPB_GPIO_MODE_OUTPUT,
    BPB_GPIO_MODE_ALTERNATE,
    BPB_GPIO_MODE_ANALOG
} GpioDriver_Mode_t;

typedef enum
{
    BPB_GPIO_STATE_LOW = 0,
    BPB_GPIO_STATE_HIGH = 1
} GpioDriver_State_t;

typedef enum
{
    BPB_GPIO_PULL_NONE = 0,
    BPB_GPIO_PULL_UP,
    BPB_GPIO_PULL_DOWN
} GpioDriver_Pull_t;

typedef enum
{
    BPB_GPIO_SPEED_LOW = 0,
    BPB_GPIO_SPEED_MEDIUM,
    BPB_GPIO_SPEED_HIGH,
    BPB_GPIO_SPEED_VERY_HIGH
} GpioDriver_Speed_t;

typedef enum
{
    BPB_GPIO_INTERRUPT_RISING = 0,
    BPB_GPIO_INTERRUPT_FALLING,
    BPB_GPIO_INTERRUPT_BOTH
} GpioDriver_InterruptEdge_t;

typedef enum
{
    BPB_GPIO_IO_DRIVE_CAP_LV0 = 0,  // Lowest drive capacity
    BPB_GPIO_IO_DRIVE_CAP_LV1,       // Low drive capacity
    BPB_GPIO_IO_DRIVE_CAP_LV2,       // Low-medium drive capacity
    BPB_GPIO_IO_DRIVE_CAP_LV3,       // Medium-low drive capacity
    BPB_GPIO_IO_DRIVE_CAP_LV4,       // Medium-high drive capacity
    BPB_GPIO_IO_DRIVE_CAP_LV5,       // High drive capacity
    BPB_GPIO_IO_DRIVE_CAP_LV6,       // Very high drive capacity
    BPB_GPIO_IO_DRIVE_CAP_LV7        // Highest drive capacity
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

typedef struct
{
    bool enableInterrupts;
    bool enableCallbacks;
} GpioDriver_Config_t;

typedef void (*GpioDriver_InterruptCallback_t)(GpioDriver_Pin_t pin);

//============================================================================
// Public Variables
//============================================================================

//============================================================================
// Public Functions
//============================================================================
GpioDriver_Status_t GpioDriverUnit_Init(const GpioDriver_Config_t *pConfig);
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

#endif /* BPB_GPIODRIVERUNIT_H */
