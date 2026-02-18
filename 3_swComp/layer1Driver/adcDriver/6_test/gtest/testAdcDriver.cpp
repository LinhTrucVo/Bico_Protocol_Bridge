//----------------------------------------------------------------------------
// Unit Test file for ADC Driver component
//----------------------------------------------------------------------------

#include "gtest/gtest.h"
#include "gmock/gmock.h"

// Unit under test
extern "C"
{
#include "mockAdcDriver.h"
}

//------------------------------------------------------------------------------
// Test Fixture Class
//------------------------------------------------------------------------------
class AdcDriver : public ::testing::Test 
{
protected:
    void SetUp() override 
    {
        // Reset all fake functions before each test
        FFF_RESET_HISTORY();
    }

    void TearDown() override 
    {
        // Clean up after each test if needed
    }
};

//------------------------------------------------------------------------------
// Test Cases for AdcDriverUnit_Init
//------------------------------------------------------------------------------
TEST_F(AdcDriver, AdcDriver_Init_ValidConfig_ReturnsOK)
{
    // Arrange
    AdcDriver_Config_t cfg = {
        ADC_RESOLUTION_12BIT,
        ADC_VREF_3V3,
        ADC_MODE_SINGLE,
        1000,
        false,
        false
    };
    
    // Act
    AdcDriver_Status_t status = call_AdcDriverUnit_Init(&cfg);
    
    // Assert
    EXPECT_EQ(ADC_STATUS_OK, status);
}

//------------------------------------------------------------------------------
// Test Cases for AdcDriverUnit_ConfigureChannel
//------------------------------------------------------------------------------
TEST_F(AdcDriver, AdcDriver_ConfigureChannel_ValidChannel_ReturnsOK)
{
    // Arrange
    AdcDriver_Config_t cfg = {
        ADC_RESOLUTION_12BIT,
        ADC_VREF_3V3,
        ADC_MODE_SINGLE,
        1000,
        false,
        false
    };
    call_AdcDriverUnit_Init(&cfg);
    
    // Act
    AdcDriver_Status_t status = call_AdcDriverUnit_ConfigureChannel(ADC_CHANNEL_0, true);
    
    // Assert
    EXPECT_EQ(ADC_STATUS_OK, status);
}

//------------------------------------------------------------------------------
// Test Cases for AdcDriverUnit_StartConversion
//------------------------------------------------------------------------------
TEST_F(AdcDriver, AdcDriver_StartConversion_ValidChannel_ReturnsOK)
{
    // Arrange
    AdcDriver_Config_t cfg = {
        ADC_RESOLUTION_12BIT,
        ADC_VREF_3V3,
        ADC_MODE_SINGLE,
        1000,
        false,
        false
    };
    call_AdcDriverUnit_Init(&cfg);
    call_AdcDriverUnit_ConfigureChannel(ADC_CHANNEL_0, true);
    
    // Act
    AdcDriver_Status_t status = call_AdcDriverUnit_StartConversion(ADC_CHANNEL_0);
    
    // Assert
    EXPECT_EQ(ADC_STATUS_OK, status);
}

//------------------------------------------------------------------------------
// Test Cases for AdcDriverUnit_ReadValue
//------------------------------------------------------------------------------
TEST_F(AdcDriver, AdcDriver_ReadValue_NullPointer_ReturnsFails)
{
    // Arrange
    AdcDriver_Config_t cfg = {
        ADC_RESOLUTION_12BIT,
        ADC_VREF_3V3,
        ADC_MODE_SINGLE,
        1000,
        false,
        false
    };
    call_AdcDriverUnit_Init(&cfg);
    
    // Act
    AdcDriver_Status_t status = call_AdcDriverUnit_ReadValue(ADC_CHANNEL_0, NULL);
    
    // Assert
    EXPECT_EQ(ADC_STATUS_INVALID_PARAM, status);
}
