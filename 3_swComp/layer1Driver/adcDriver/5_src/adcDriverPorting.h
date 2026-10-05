// Port interface of the ADC driver. Implemented by the device workspace, called by adcDriverUnit.c.

#ifndef ADCDRIVERPORT_H
#define ADCDRIVERPORT_H

//============================================================================
// Dependencies
//============================================================================
#include <stdint.h>
#include <stdbool.h>

//============================================================================
// Public Types
//============================================================================
// Called by the port for every sample of a periodic sampling.
typedef void (*AdcPort_SampleHandler_t)(uint8_t channel, uint16_t value);

//============================================================================
// Public Functions
//============================================================================
bool AdcPort_Init(void);
void AdcPort_DeInit(void);
bool AdcPort_ConfigureChannel(uint8_t channel);
bool AdcPort_ReadRaw(uint8_t channel, uint16_t *pRawValue);
bool AdcPort_StartPeriodicSampling(uint8_t channel, uint32_t frequencyHz);
void AdcPort_StopPeriodicSampling(void);
void AdcPort_SetSampleHandler(AdcPort_SampleHandler_t handler);

#endif /* ADCDRIVERPORT_H */
