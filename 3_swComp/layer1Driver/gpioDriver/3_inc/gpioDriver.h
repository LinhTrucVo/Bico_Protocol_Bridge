// GPIO Driver Component - Public Interface

#ifndef GPIODRIVER_H
#define GPIODRIVER_H

//============================================================================
// Dependencies
//============================================================================
#include <stdint.h>
#include <stdbool.h>
#include "gpioDriverCfg.h"
#include "gpioDriverUnit.h"

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
    GPIO_STATUS_INVALID_PIN
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

typedef uint8_t GpioDriver_Pin_t;

//============================================================================
// Public Functions
//============================================================================
GpioDriver_Status_t GpioDriver_Init(void);
GpioDriver_Status_t GpioDriver_ConfigurePin(GpioDriver_Pin_t pin, GpioDriver_Mode_t mode);
GpioDriver_Status_t GpioDriver_WritePin(GpioDriver_Pin_t pin, GpioDriver_State_t state);
GpioDriver_Status_t GpioDriver_ReadPin(GpioDriver_Pin_t pin, GpioDriver_State_t *pState);
GpioDriver_Status_t GpioDriver_TogglePin(GpioDriver_Pin_t pin);
GpioDriver_Status_t GpioDriver_DeInit(void);

#endif /* GPIODRIVER_H */
