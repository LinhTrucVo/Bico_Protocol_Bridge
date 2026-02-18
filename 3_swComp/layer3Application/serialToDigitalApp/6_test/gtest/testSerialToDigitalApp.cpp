//----------------------------------------------------------------------------
// Unit Test file for Serial To Digital App component
//----------------------------------------------------------------------------

#include "gtest/gtest.h"
#include "gmock/gmock.h"

// Unit under test
extern "C"
{
#include "mockSerialToDigitalApp.h"
}

//------------------------------------------------------------------------------
// Test Fixture Class
//------------------------------------------------------------------------------
class SerialToDigitalApp : public ::testing::Test 
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
// Test Cases for SerialToDigitalAppUnit_Init
//------------------------------------------------------------------------------
TEST_F(SerialToDigitalApp, SerialToDigitalApp_Init_Valid_ReturnsOK)
{
    // Arrange
    
    // Act
    SerialToDigitalApp_Status_t status = call_SerialToDigitalAppUnit_Init();
    
    // Assert
    EXPECT_EQ(SERIAL_TO_DIGITAL_APP_STATUS_OK, status);
}

//------------------------------------------------------------------------------
// Test Cases for SerialToDigitalAppUnit_ProcessFrame
//------------------------------------------------------------------------------
TEST_F(SerialToDigitalApp, SerialToDigitalApp_ProcessFrame_ValidFrame_ReturnsOK)
{
    // Arrange
    uint8_t frameBuffer[32] = {0};
    uint8_t responseBuffer[64] = {0};
    uint16_t responseLength = 0;
    call_SerialToDigitalAppUnit_Init();
    
    // Act
    SerialToDigitalApp_Status_t status = call_SerialToDigitalAppUnit_ProcessFrame(frameBuffer, sizeof(frameBuffer), responseBuffer, &responseLength);
    
    // Assert
    EXPECT_EQ(SERIAL_TO_DIGITAL_APP_STATUS_OK, status);
}
