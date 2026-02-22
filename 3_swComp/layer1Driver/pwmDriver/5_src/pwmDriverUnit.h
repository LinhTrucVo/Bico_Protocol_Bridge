#ifndef PWMDRIVERUNIT_H
#define PWMDRIVERUNIT_H

//============================================================================
// Dependencies
//============================================================================
#include <stdint.h>
#include <stdbool.h>
#include "pwmDriverCfg.h"

//============================================================================
// Configuration Macros
//============================================================================
#define PWM_CFG_MAX_CHANNELS        8
#define PWM_CFG_DEFAULT_FREQ_HZ     1000
#define PWM_CFG_DEFAULT_DUTY        5000
#define PWM_MAX_CHANNELS            PWM_CFG_MAX_CHANNELS
#define PWM_MIN_FREQUENCY           100
#define PWM_MAX_FREQUENCY           100000
#define PWM_MAX_DUTY_CYCLE          10000

//============================================================================
// Status Enums
//============================================================================
#define PWM_STATUS_OK               PWMDRIVER_OK
#define PWM_STATUS_ERROR            PWMDRIVER_ERROR
#define PWM_STATUS_INVALID_CHANNEL  PWMDRIVER_INVALID_CHANNEL
#define PWM_STATUS_INVALID_FREQUENCY PWMDRIVER_INVALID_FREQUENCY
#define PWM_STATUS_INVALID_PARAM    PWMDRIVER_ERROR
#define PWM_STATUS_NOT_INITIALIZED  PWMDRIVER_NOT_INITIALIZED

//============================================================================
// Public Types
//============================================================================
typedef enum
{
    PWMDRIVER_OK = 0,
    PWMDRIVER_ERROR,
    PWMDRIVER_INVALID_CHANNEL,
    PWMDRIVER_INVALID_FREQUENCY,
    PWMDRIVER_NOT_INITIALIZED
} PwmDriver_Status_t;

typedef enum
{
    PWM_CHANNEL_0 = 0,
    PWM_CHANNEL_1,
    PWM_CHANNEL_2,
    PWM_CHANNEL_3,
    PWM_CHANNEL_4,
    PWM_CHANNEL_5,
    PWM_CHANNEL_6,
    PWM_CHANNEL_7
} PwmDriver_Channel_t;

typedef enum
{
    PWM_POLARITY_NORMAL = 0,
    PWM_POLARITY_INVERTED
} PwmDriver_Polarity_t;

typedef enum
{
    PWM_ALIGNMENT_EDGE = 0,
    PWM_ALIGNMENT_CENTER
} PwmDriver_Alignment_t;

typedef struct
{
    uint32_t frequency;
    uint16_t dutyCycle;
    PwmDriver_Polarity_t polarity;
    PwmDriver_Alignment_t alignment;
    bool dmaEnabled;
    uint8_t interruptPriority;
    bool enableDeadTime;
    uint32_t deadTimeNs;
} PwmDriver_ChannelConfig_t;

typedef struct
{
    bool enableDma;
    bool enableDeadTime;
} PwmDriver_Config_t;

//============================================================================
// Public Functions
//============================================================================
PwmDriver_Status_t PwmDriverUnit_Init(const PwmDriver_Config_t *pConfig);
PwmDriver_Status_t PwmDriverUnit_ConfigureChannel(PwmDriver_Channel_t channel, const PwmDriver_ChannelConfig_t *pConfig);
PwmDriver_Status_t PwmDriverUnit_SetFrequency(PwmDriver_Channel_t channel, uint32_t frequency);
PwmDriver_Status_t PwmDriverUnit_SetDutyCycle(PwmDriver_Channel_t channel, uint16_t dutyCycle);
PwmDriver_Status_t PwmDriverUnit_SetPolarity(PwmDriver_Channel_t channel, PwmDriver_Polarity_t polarity);
PwmDriver_Status_t PwmDriverUnit_StartChannel(PwmDriver_Channel_t channel);
PwmDriver_Status_t PwmDriverUnit_StopChannel(PwmDriver_Channel_t channel);
PwmDriver_Status_t PwmDriverUnit_GetConfiguration(PwmDriver_Channel_t channel, PwmDriver_ChannelConfig_t *pConfig);
PwmDriver_Status_t PwmDriverUnit_IsChannelRunning(PwmDriver_Channel_t channel, bool *pIsRunning);
PwmDriver_Status_t PwmDriverUnit_DeInit(void);

#endif /* PWMDRIVERUNIT_H */
