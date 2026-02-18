//----------------------------------------------------------------------------
// Unit Test file for Serial To Analog App component
//----------------------------------------------------------------------------

#include "gtest/gtest.h"
#include "gmock/gmock.h"

// Unit under test
extern "C"
{
#include "mockSerialToAnalogApp.h"
}

//------------------------------------------------------------------------------
// Test Fixture Class
//------------------------------------------------------------------------------
class SerialToAnalogApp : public ::testing::Test 
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
// Test Cases for SerialToAnalogAppUnit_Init
//------------------------------------------------------------------------------
TEST_F(SerialToAnalogApp, SerialToAnalogApp_Init_Valid_ReturnsOK)
{
    // Arrange
    
    // Act
    SerialToAnalogApp_Status_t status = call_SerialToAnalogAppUnit_Init();
    
    // Assert
    EXPECT_EQ(SERIAL_TO_ANALOG_APP_STATUS_OK, status);
}

//------------------------------------------------------------------------------
// Test Cases for SerialToAnalogAppUnit_ConfigureChannel
//------------------------------------------------------------------------------
TEST_F(SerialToAnalogApp, SerialToAnalogApp_ConfigureChannel_ValidConfig_ReturnsOK)
{
    // Arrange
    SerialToAnalogApp_ChannelConfig_t cfg = {0, true, SERIAL_TO_ANALOG_RESOLUTION_12BIT, SERIAL_TO_ANALOG_RANGE_3V3, 1000, 1, false, 0.0f, 0.0f};
    call_SerialToAnalogAppUnit_Init();
    
    // Act
    SerialToAnalogApp_Status_t status = call_SerialToAnalogAppUnit_ProcessFrame(nullptr, 0, nullptr, nullptr);
    
    // Assert
    EXPECT_EQ(SERIAL_TO_ANALOG_APP_STATUS_OK, status) << "ProcessFrame should succeed";
}
