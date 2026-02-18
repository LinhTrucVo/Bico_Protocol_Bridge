//----------------------------------------------------------------------------
// Unit Test file for I2C Master Driver component
//----------------------------------------------------------------------------

#include "gtest/gtest.h"
#include "gmock/gmock.h"

// Unit under test
extern "C"
{
#include "mockI2cMasterDriver.h"
}

//------------------------------------------------------------------------------
// Test Fixture Class
//------------------------------------------------------------------------------
class I2cMasterDriver : public ::testing::Test 
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
// Test Cases for I2cMasterDriverUnit_Init
//------------------------------------------------------------------------------
TEST_F(I2cMasterDriver, I2cMasterDriver_Init_ValidConfig_ReturnsOK)
{
    // Arrange
    I2cMasterDriver_Config_t cfg = {
        I2C_SPEED_STANDARD,
        I2C_ADDRESS_7BIT,
        false,
        false,
        100
    };
    
    // Act
    I2cMasterDriver_Status_t status = call_I2cMasterDriverUnit_Init(&cfg);
    
    // Assert
    EXPECT_EQ(I2C_MASTER_STATUS_OK, status);
}

//------------------------------------------------------------------------------
// Test Cases for I2cMasterDriverUnit_Write
//------------------------------------------------------------------------------
TEST_F(I2cMasterDriver, I2cMasterDriver_Write_ValidData_ReturnsOK)
{
    // Arrange
    I2cMasterDriver_Config_t cfg = {
        I2C_SPEED_STANDARD,
        I2C_ADDRESS_7BIT,
        false,
        false,
        100
    };
    call_I2cMasterDriverUnit_Init(&cfg);
    uint8_t data[2] = {0x01, 0x02};
    
    // Act
    I2cMasterDriver_Status_t status = call_I2cMasterDriverUnit_Write(0x50, data, 2);
    
    // Assert
    EXPECT_EQ(I2C_MASTER_STATUS_OK, status);
}

//------------------------------------------------------------------------------
// Test Cases for I2cMasterDriverUnit_Read
//------------------------------------------------------------------------------
TEST_F(I2cMasterDriver, I2cMasterDriver_Read_ValidAddress_ReturnsOK)
{
    // Arrange
    I2cMasterDriver_Config_t cfg = {
        I2C_SPEED_STANDARD,
        I2C_ADDRESS_7BIT,
        false,
        false,
        100
    };
    call_I2cMasterDriverUnit_Init(&cfg);
    uint8_t data[2] = {0x00, 0x00};
    
    // Act
    I2cMasterDriver_Status_t status = call_I2cMasterDriverUnit_Read(0x50, data, 2);
    
    // Assert
    EXPECT_EQ(I2C_MASTER_STATUS_OK, status);
}

//------------------------------------------------------------------------------
// Test Cases for I2cMasterDriverUnit_DeInit
//------------------------------------------------------------------------------
TEST_F(I2cMasterDriver, I2cMasterDriver_DeInit_ValidState_ReturnsOK)
{
    // Arrange
    // ... setup code ...
    
    // Act
    I2cMasterDriver_Status_t status = call_I2cMasterDriverUnit_DeInit();
    
    // Assert
    EXPECT_EQ(I2C_MASTER_STATUS_OK, status);
}
