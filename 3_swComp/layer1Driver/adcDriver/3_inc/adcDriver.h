// ADC Driver Component - Public Interface
// This file defines the public interface for the ADC driver component

#ifndef ADCDRIVER_H
#define ADCDRIVER_H

//============================================================================
// Dependencies
//============================================================================
#include <stdint.h>
#include <stdbool.h>
#include "adcDriverCfg.h"
#include "adcDriverUnit.h"

//============================================================================
// Public Macros
//============================================================================
#define ADC_MAX_CHANNELS         8
#define ADC_RESOLUTION_BITS      12
#define ADC_MAX_VALUE            ((1U << ADC_RESOLUTION_BITS) - 1)

//============================================================================
// Public Types
//============================================================================
typedef enum
{
    ADC_STATUS_OK = 0,
    ADC_STATUS_ERROR,
    ADC_STATUS_BUSY,
    ADC_STATUS_TIMEOUT
} AdcDriver_Status_t;

typedef enum
{
    ADC_CHANNEL_0 = 0,
    ADC_CHANNEL_1,
    ADC_CHANNEL_2,
    ADC_CHANNEL_3,
    ADC_CHANNEL_4,
    ADC_CHANNEL_5,
    ADC_CHANNEL_6,
    ADC_CHANNEL_7
} AdcDriver_Channel_t;

//============================================================================
// Public Variables
//============================================================================
// None

//============================================================================
// Public Functions
//============================================================================
/**
 * @brief Initialize the ADC driver
 * @return AdcDriver_Status_t Status of initialization
 */
AdcDriver_Status_t AdcDriver_Init(void);

/**
 * @brief Start ADC conversion on specified channel
 * @param channel ADC channel to convert
 * @return AdcDriver_Status_t Status of operation
 */
AdcDriver_Status_t AdcDriver_StartConversion(AdcDriver_Channel_t channel);

/**
 * @brief Read ADC conversion result
 * @param channel ADC channel to read from
 * @param pValue Pointer to store the conversion result
 * @return AdcDriver_Status_t Status of operation
 */
AdcDriver_Status_t AdcDriver_ReadValue(AdcDriver_Channel_t channel, uint16_t *pValue);

/**
 * @brief Deinitialize the ADC driver
 * @return AdcDriver_Status_t Status of operation
 */
AdcDriver_Status_t AdcDriver_DeInit(void);

#endif /* ADCDRIVER_H */
