// ADC Driver Test Cases
// This file contains unit tests for the ADC driver component

#include <gtest/gtest.h>

extern "C" {
#include "adcDriver.h"
}

class AdcDriverTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Setup code before each test
    }

    void TearDown() override {
        // Cleanup code after each test
    }
};

TEST_F(AdcDriverTest, InitSuccess) {
    AdcDriver_Status_t status = AdcDriver_Init();
    EXPECT_EQ(ADC_STATUS_OK, status);
}

TEST_F(AdcDriverTest, StartConversionValidChannel) {
    AdcDriver_Init();
    AdcDriver_Status_t status = AdcDriver_StartConversion(ADC_CHANNEL_0);
    EXPECT_EQ(ADC_STATUS_OK, status);
}

TEST_F(AdcDriverTest, ReadValueValidChannel) {
    uint16_t value = 0;
    AdcDriver_Init();
    AdcDriver_Status_t status = AdcDriver_ReadValue(ADC_CHANNEL_0, &value);
    EXPECT_EQ(ADC_STATUS_OK, status);
}

TEST_F(AdcDriverTest, ReadValueNullPointer) {
    AdcDriver_Init();
    AdcDriver_Status_t status = AdcDriver_ReadValue(ADC_CHANNEL_0, NULL);
    EXPECT_EQ(ADC_STATUS_ERROR, status);
}

TEST_F(AdcDriverTest, DeInitSuccess) {
    AdcDriver_Init();
    AdcDriver_Status_t status = AdcDriver_DeInit();
    EXPECT_EQ(ADC_STATUS_OK, status);
}
