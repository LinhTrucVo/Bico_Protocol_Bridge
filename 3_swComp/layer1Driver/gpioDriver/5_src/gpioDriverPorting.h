// Port interface of the GPIO driver. Implemented by the device workspace, called by gpioDriverUnit.c.

#ifndef GPIODRIVERPORT_H
#define GPIODRIVERPORT_H

//============================================================================
// Dependencies
//============================================================================
#include <stdint.h>
#include <stdbool.h>

//============================================================================
// Public Types
//============================================================================
typedef enum
{
    GPIOPORT_MODE_DISABLED = 0,
    GPIOPORT_MODE_INPUT,
    GPIOPORT_MODE_OUTPUT
} GpioPort_Mode_t;

typedef enum
{
    GPIOPORT_PULL_NONE = 0,
    GPIOPORT_PULL_UP,
    GPIOPORT_PULL_DOWN
} GpioPort_Pull_t;

typedef enum
{
    GPIOPORT_EDGE_RISING = 0,
    GPIOPORT_EDGE_FALLING,
    GPIOPORT_EDGE_BOTH
} GpioPort_Edge_t;

// Called by the port, possibly from interrupt context, when an enabled pin triggers.
typedef void (*GpioPort_InterruptHandler_t)(uint8_t pin);

//============================================================================
// Public Functions
//============================================================================
bool GpioPort_Init(void);
void GpioPort_DeInit(void);
bool GpioPort_ConfigurePin(uint8_t pin, GpioPort_Mode_t mode, GpioPort_Pull_t pull, uint8_t driveStrength, bool initialHigh);
bool GpioPort_SetDriveStrength(uint8_t pin, uint8_t driveStrength);
bool GpioPort_Write(uint8_t pin, bool high);
bool GpioPort_Read(uint8_t pin, bool *pHigh);
bool GpioPort_EnableInterrupt(uint8_t pin, GpioPort_Edge_t edge);
void GpioPort_DisableInterrupt(uint8_t pin);
void GpioPort_SetInterruptHandler(GpioPort_InterruptHandler_t handler);

#endif /* GPIODRIVERPORT_H */
