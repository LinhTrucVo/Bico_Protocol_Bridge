//----------------------------------------------------------------------------
// Unit Test file for Serial To I2C App component
//----------------------------------------------------------------------------

#include "gtest/gtest.h"
#include "gmock/gmock.h"

// Unit under test
extern "C"
{
#include "mockSerialToI2CApp.h"
}

//------------------------------------------------------------------------------
// Test Fixture Class
//------------------------------------------------------------------------------
class SerialToI2CApp : public ::testing::Test 
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
// Test Cases for SerialToI2CAppUnit_Init
//------------------------------------------------------------------------------
TEST_F(SerialToI2CApp, SerialToI2CApp_Init_Valid_ReturnsOK)
{
    // Arrange
    
    // Act
    SerialToI2CApp_Status_t status = call_SerialToI2CAppUnit_Init();
    
    // Assert
    EXPECT_EQ(SERIAL_TO_I2C_APP_STATUS_OK, status);
}

//------------------------------------------------------------------------------
// Test Cases for SerialToI2CAppUnit_ProcessFrame
//------------------------------------------------------------------------------
TEST_F(SerialToI2CApp, SerialToI2CApp_ProcessFrame_ValidFrame_ReturnsOK)
{
    // Arrange
    uint8_t frameBuffer[32] = {0};
    uint8_t responseBuffer[64] = {0};
    uint16_t responseLength = 0;
    call_SerialToI2CAppUnit_Init();
    
    // Act
    SerialToI2CApp_Status_t status = call_SerialToI2CAppUnit_ProcessFrame(frameBuffer, sizeof(frameBuffer), responseBuffer, &responseLength);
    
    // Assert
    EXPECT_EQ(SERIAL_TO_I2C_APP_STATUS_OK, status);
}
