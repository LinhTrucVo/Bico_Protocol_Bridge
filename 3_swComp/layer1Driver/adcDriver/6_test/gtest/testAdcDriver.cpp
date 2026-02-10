// ADC Driver Test Cases

#include <gtest/gtest.h>

extern "C" {
#include "adcDriver.h"
}

TEST(AdcDriverTest, InitAndConfigureChannel) {
    AdcDriver_Config_t cfg = {
        ADC_RESOLUTION_12BIT,
        ADC_VREF_3V3,
        ADC_MODE_SINGLE,
        1000,
        false,
        false
    };
    EXPECT_EQ(ADC_STATUS_OK, AdcDriver_Init(&cfg));
    EXPECT_EQ(ADC_STATUS_OK, AdcDriver_ConfigureChannel(ADC_CHANNEL_0, true));
}

TEST(AdcDriverTest, StartReadStop) {
    AdcDriver_Config_t cfg = {
        ADC_RESOLUTION_12BIT,
        ADC_VREF_3V3,
        ADC_MODE_SINGLE,
        1000,
        false,
        false
    };
    uint16_t value = 0;
    EXPECT_EQ(ADC_STATUS_OK, AdcDriver_Init(&cfg));
    EXPECT_EQ(ADC_STATUS_OK, AdcDriver_ConfigureChannel(ADC_CHANNEL_0, true));
    EXPECT_EQ(ADC_STATUS_OK, AdcDriver_StartConversion(ADC_CHANNEL_0));
    EXPECT_EQ(ADC_STATUS_OK, AdcDriver_ReadValue(ADC_CHANNEL_0, &value));
    EXPECT_EQ(ADC_STATUS_OK, AdcDriver_StopConversion());
}

TEST(AdcDriverTest, NullPointerReadFails) {
    AdcDriver_Config_t cfg = {
        ADC_RESOLUTION_12BIT,
        ADC_VREF_3V3,
        ADC_MODE_SINGLE,
        1000,
        false,
        false
    };
    EXPECT_EQ(ADC_STATUS_OK, AdcDriver_Init(&cfg));
    EXPECT_EQ(ADC_STATUS_INVALID_PARAM, AdcDriver_ReadValue(ADC_CHANNEL_0, NULL));
}
