// PwmDriver - Public Interface
#ifndef PWMDRIVER_H
#define PWMDRIVER_H
#include <stdint.h>
#include <stdbool.h>
#include "pwmDriverCfg.h"
#include "pwmDriverUnit.h"
typedef enum
{
    PWM_STATUS_OK = 0,
    PWM_STATUS_ERROR,
    PWM_STATUS_BUSY
} PwmDriver_Status_t;
PwmDriver_Status_t PwmDriver_Init(void);
PwmDriver_Status_t PwmDriver_DeInit(void);
#endif /* PWMDRIVER_H */
