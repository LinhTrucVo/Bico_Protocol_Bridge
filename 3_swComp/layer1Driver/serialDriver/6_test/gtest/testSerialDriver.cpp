//----------------------------------------------------------------------------
// Unit Test file for Serial Driver component
//----------------------------------------------------------------------------

#include "gtest/gtest.h"
#include "gmock/gmock.h"

// Unit under test
extern "C"
{
#include "mockSerialDriver.h"
}

//------------------------------------------------------------------------------
// Test Fixture Class
//------------------------------------------------------------------------------
class SerialDriver : public ::testing::Test 
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
// Test Cases for SerialDriverUnit_Init
//------------------------------------------------------------------------------
TEST_F(SerialDriver, SerialDriver_Init_ValidConfig_ReturnsOK)
{
    // Arrange
    SerialDriver_Config_t cfg = {
        SERIAL_BAUDRATE_115200,
        SERIAL_PARITY_NONE,
        SERIAL_STOPBITS_1,
        SERIAL_DATABITS_8,
        SERIAL_FLOWCONTROL_NONE,
        false,
        false
    };
    
    // Act
    SerialDriver_Status_t status = call_SerialDriverUnit_Init(&cfg);
    
    // Assert
    EXPECT_EQ(SERIAL_STATUS_OK, status);
}

//------------------------------------------------------------------------------
// Test Cases for SerialDriverUnit_Send
//------------------------------------------------------------------------------
TEST_F(SerialDriver, SerialDriver_Send_ValidData_ReturnsOK)
{
    // Arrange
    SerialDriver_Config_t cfg = {
        SERIAL_BAUDRATE_115200,
        SERIAL_PARITY_NONE,
        SERIAL_STOPBITS_1,
        SERIAL_DATABITS_8,
        SERIAL_FLOWCONTROL_NONE,
        false,
        false
    };
    uint8_t data[2] = {0xAA, 0x55};
    call_SerialDriverUnit_Init(&cfg);
    
    // Act
    SerialDriver_Status_t status = call_SerialDriverUnit_Send(data, 2);
    
    // Assert
    EXPECT_EQ(SERIAL_STATUS_OK, status);
}

//------------------------------------------------------------------------------
// Test Cases for SerialDriverUnit_Configure
//------------------------------------------------------------------------------
TEST_F(SerialDriver, SerialDriver_Configure_ValidParams_ReturnsOK)
{
    // Arrange
    SerialDriver_Config_t cfg = {
        SERIAL_BAUDRATE_115200,
        SERIAL_PARITY_NONE,
        SERIAL_STOPBITS_1,
        SERIAL_DATABITS_8,
        SERIAL_FLOWCONTROL_NONE,
        false,
        false
    };
    call_SerialDriverUnit_Init(&cfg);
    
    // Act
    SerialDriver_Status_t status = call_SerialDriverUnit_Configure(SERIAL_BAUDRATE_115200, SERIAL_PARITY_NONE, SERIAL_STOPBITS_1, SERIAL_DATABITS_8);
    
    // Assert
    EXPECT_EQ(SERIAL_STATUS_OK, status);
}
