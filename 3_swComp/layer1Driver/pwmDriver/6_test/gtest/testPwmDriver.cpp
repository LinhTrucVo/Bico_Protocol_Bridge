//----------------------------------------------------------------------------
// Unit Test file for PWM Driver component
//----------------------------------------------------------------------------

#include "gtest/gtest.h"
#include "gmock/gmock.h"

// Unit under test
extern "C"
{
#include "mockPwmDriver.h"
}

//------------------------------------------------------------------------------
// Test Fixture Class
//------------------------------------------------------------------------------
class PwmDriver : public ::testing::Test 
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
// Test Cases for PwmDriverUnit_Init
//------------------------------------------------------------------------------
TEST_F(PwmDriver, PwmDriver_Init_ValidConfig_ReturnsOK)
{
    // Arrange
    // Act
    PwmDriver_Status_t status = call_PwmDriverUnit_Init();
    
    // Assert
    EXPECT_EQ(PWM_STATUS_OK, status);
}

//------------------------------------------------------------------------------
// Test Cases for PwmDriverUnit_ConfigureChannel
//------------------------------------------------------------------------------
TEST_F(PwmDriver, PwmDriver_ConfigureChannel_ValidChannel_ReturnsOK)
{
    // Arrange
    PwmDriver_ChannelConfig_t cfg = {
        1000,
        5000,
        PWM_POLARITY_NORMAL,
        PWM_ALIGNMENT_EDGE,
        false,
        0
    };
    call_PwmDriverUnit_Init();
    
    // Act
    PwmDriver_Status_t status = call_PwmDriverUnit_ConfigureChannel(PWM_CHANNEL_0, &cfg);
    
    // Assert
    EXPECT_EQ(PWM_STATUS_OK, status);
}

//------------------------------------------------------------------------------
// Test Cases for PwmDriverUnit_StartChannel
//------------------------------------------------------------------------------
TEST_F(PwmDriver, PwmDriver_StartChannel_ValidChannel_ReturnsOK)
{
    // Arrange
    PwmDriver_ChannelConfig_t cfg = {
        1000,
        5000,
        PWM_POLARITY_NORMAL,
        PWM_ALIGNMENT_EDGE,
        false,
        0
    };
    call_PwmDriverUnit_Init();
    call_PwmDriverUnit_ConfigureChannel(PWM_CHANNEL_0, &cfg);
    
    // Act
    PwmDriver_Status_t status = call_PwmDriverUnit_StartChannel(PWM_CHANNEL_0);
    
    // Assert
    EXPECT_EQ(PWM_STATUS_OK, status);
}
