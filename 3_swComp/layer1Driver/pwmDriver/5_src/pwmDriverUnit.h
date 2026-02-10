#ifndef PWMDRIVERUNIT_H
#define PWMDRIVERUNIT_H

//============================================================================
// Dependencies
//============================================================================
#include <stdint.h>
#include <stdbool.h>
#include "pwmDriverCfg.h"

//============================================================================
// Forward declarations (types defined in pwmDriver.h)
//============================================================================
typedef enum PwmDriver_Status_t PwmDriver_Status_t;
typedef enum PwmDriver_Channel_t PwmDriver_Channel_t;
typedef enum PwmDriver_Polarity_t PwmDriver_Polarity_t;
typedef struct PwmDriver_ChannelConfig_t PwmDriver_ChannelConfig_t;

//============================================================================
// Public Functions
//============================================================================
PwmDriver_Status_t PwmDriverUnit_Init(void);
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
