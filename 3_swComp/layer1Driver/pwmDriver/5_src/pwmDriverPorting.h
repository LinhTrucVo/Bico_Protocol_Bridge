// Port interface of the PWM driver. Implemented by the device workspace, called by pwmDriverUnit.c.

#ifndef PWMDRIVERPORT_H
#define PWMDRIVERPORT_H

//============================================================================
// Dependencies
//============================================================================
#include <stdint.h>
#include <stdbool.h>

//============================================================================
// Public Macros
//============================================================================
// Duty cycle unit of the port: 0..10000 equals 0..100 percent.
#define PWMPORT_DUTY_MAX    10000U

//============================================================================
// Public Functions
//============================================================================
bool PwmPort_Init(void);
void PwmPort_DeInit(void);
bool PwmPort_ConfigureChannel(uint8_t channel, uint32_t frequencyHz, uint16_t duty, bool inverted);
bool PwmPort_SetFrequency(uint8_t channel, uint32_t frequencyHz);
bool PwmPort_SetDuty(uint8_t channel, uint16_t duty);
bool PwmPort_Start(uint8_t channel);
bool PwmPort_Stop(uint8_t channel);

#endif /* PWMDRIVERPORT_H */
