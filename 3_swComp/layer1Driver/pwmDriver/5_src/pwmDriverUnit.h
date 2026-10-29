#ifndef BPB_PWMDRIVERUNIT_H
#define BPB_PWMDRIVERUNIT_H

//============================================================================
// Dependencies
//============================================================================
#include <stdint.h>
#include <stdbool.h>
#include "pwmDriverCfg.h"

//============================================================================
// Configuration Macros
//============================================================================
#define BPB_PWM_CFG_MAX_CHANNELS        8
#define BPB_PWM_CFG_DEFAULT_FREQ_HZ     1000
#define BPB_PWM_CFG_DEFAULT_DUTY        5000
#define BPB_PWM_MAX_CHANNELS            BPB_PWM_CFG_MAX_CHANNELS
#define BPB_PWM_MIN_FREQUENCY           100
#define BPB_PWM_MAX_FREQUENCY           100000
#define BPB_PWM_MAX_DUTY_CYCLE          10000

//============================================================================
// Status Enums
//============================================================================
#define BPB_PWM_STATUS_OK               BPB_PWMDRIVER_OK
#define BPB_PWM_STATUS_ERROR            BPB_PWMDRIVER_ERROR
#define BPB_PWM_STATUS_INVALID_CHANNEL  BPB_PWMDRIVER_INVALID_CHANNEL
#define BPB_PWM_STATUS_INVALID_FREQUENCY BPB_PWMDRIVER_INVALID_FREQUENCY
#define BPB_PWM_STATUS_INVALID_PARAM    BPB_PWMDRIVER_ERROR
#define BPB_PWM_STATUS_NOT_INITIALIZED  BPB_PWMDRIVER_NOT_INITIALIZED

//============================================================================
// Public Types
//============================================================================
typedef enum
{
    BPB_PWMDRIVER_OK = 0,
    BPB_PWMDRIVER_ERROR,
    BPB_PWMDRIVER_INVALID_CHANNEL,
    BPB_PWMDRIVER_INVALID_FREQUENCY,
    BPB_PWMDRIVER_NOT_INITIALIZED
} PwmDriver_Status_t;

typedef enum
{
    BPB_PWM_CHANNEL_0 = 0,
    BPB_PWM_CHANNEL_1,
    BPB_PWM_CHANNEL_2,
    BPB_PWM_CHANNEL_3,
    BPB_PWM_CHANNEL_4,
    BPB_PWM_CHANNEL_5,
    BPB_PWM_CHANNEL_6,
    BPB_PWM_CHANNEL_7
} PwmDriver_Channel_t;

typedef enum
{
    BPB_PWM_POLARITY_NORMAL = 0,
    BPB_PWM_POLARITY_INVERTED
} PwmDriver_Polarity_t;

typedef enum
{
    BPB_PWM_ALIGNMENT_EDGE = 0,
    BPB_PWM_ALIGNMENT_CENTER
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

#endif /* BPB_PWMDRIVERUNIT_H */
