//----------------------------------------------------------------------------
// Unit Test file for Serial To SPI App component
//----------------------------------------------------------------------------

#include "gtest/gtest.h"
#include "gmock/gmock.h"

// Unit under test
extern "C"
{
#include "mockSerialToSPIApp.h"
}

//------------------------------------------------------------------------------
// Test Fixture Class
//------------------------------------------------------------------------------
class SerialToSPIApp : public ::testing::Test 
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
// Test Cases for SerialToSPIAppUnit_Init
//------------------------------------------------------------------------------
TEST_F(SerialToSPIApp, SerialToSPIApp_Init_Valid_ReturnsOK)
{
    // Arrange
    
    // Act
    SerialToSPIApp_Status_t status = call_SerialToSPIAppUnit_Init();
    
    // Assert
    EXPECT_EQ(SERIAL_TO_SPI_APP_STATUS_OK, status);
}

//------------------------------------------------------------------------------
// Test Cases for SerialToSPIAppUnit_ProcessFrame
//------------------------------------------------------------------------------
TEST_F(SerialToSPIApp, SerialToSPIApp_ProcessFrame_ValidFrame_ReturnsOK)
{
    // Arrange
    uint8_t frameBuffer[32] = {0};
    uint8_t responseBuffer[64] = {0};
    uint16_t responseLength = 0;
    call_SerialToSPIAppUnit_Init();
    
    // Act
    SerialToSPIApp_Status_t status = call_SerialToSPIAppUnit_ProcessFrame(frameBuffer, sizeof(frameBuffer), responseBuffer, &responseLength);
    
    // Assert
    EXPECT_EQ(SERIAL_TO_SPI_APP_STATUS_OK, status);
}
