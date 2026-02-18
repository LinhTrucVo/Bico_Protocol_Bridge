//----------------------------------------------------------------------------
// Unit Test file for I2C Slave Driver component
//----------------------------------------------------------------------------

#include "gtest/gtest.h"
#include "gmock/gmock.h"

// Unit under test
extern "C"
{
#include "mockI2cSlaveDriver.h"
}

//------------------------------------------------------------------------------
// Test Fixture Class
//------------------------------------------------------------------------------
class I2cSlaveDriver : public ::testing::Test 
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
// Test Cases for I2cSlaveDriverUnit_Init
//------------------------------------------------------------------------------
TEST_F(I2cSlaveDriver, I2cSlaveDriver_Init_ValidConfig_ReturnsOK)
{
    // Arrange
    I2cSlaveDriver_Config_t cfg = {
        0x10,
        I2C_SLAVE_ADDRESS_7BIT,
        false,
        false,
        false
    };
    
    // Act
    I2cSlaveDriver_Status_t status = call_I2cSlaveDriverUnit_Init(&cfg);
    
    // Assert
    EXPECT_EQ(I2C_SLAVE_STATUS_OK, status);
}

//------------------------------------------------------------------------------
// Test Cases for I2cSlaveDriverUnit_SetRxBuffer
//------------------------------------------------------------------------------
TEST_F(I2cSlaveDriver, I2cSlaveDriver_SetRxBuffer_ValidBuffer_ReturnsOK)
{
    // Arrange
    I2cSlaveDriver_Config_t cfg = {
        0x10,
        I2C_SLAVE_ADDRESS_7BIT,
        false,
        false,
        false
    };
    uint8_t rx[4] = {0};
    call_I2cSlaveDriverUnit_Init(&cfg);
    
    // Act
    I2cSlaveDriver_Status_t status = call_I2cSlaveDriverUnit_SetRxBuffer(rx, sizeof(rx));
    
    // Assert
    EXPECT_EQ(I2C_SLAVE_STATUS_OK, status);
}

//------------------------------------------------------------------------------
// Test Cases for I2cSlaveDriverUnit_SetTxBuffer
//------------------------------------------------------------------------------
TEST_F(I2cSlaveDriver, I2cSlaveDriver_SetTxBuffer_ValidBuffer_ReturnsOK)
{
    // Arrange
    I2cSlaveDriver_Config_t cfg = {
        0x10,
        I2C_SLAVE_ADDRESS_7BIT,
        false,
        false,
        false
    };
    uint8_t tx[2] = {0xAA, 0x55};
    call_I2cSlaveDriverUnit_Init(&cfg);
    
    // Act
    I2cSlaveDriver_Status_t status = call_I2cSlaveDriverUnit_SetTxBuffer(tx, sizeof(tx));
    
    // Assert
    EXPECT_EQ(I2C_SLAVE_STATUS_OK, status);
}
