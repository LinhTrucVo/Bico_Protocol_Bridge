//----------------------------------------------------------------------------
// Unit Test file for NVM Driver component
//----------------------------------------------------------------------------

#include "gtest/gtest.h"
#include "gmock/gmock.h"

// Unit under test
extern "C"
{
#include "mockNvmDriver.h"
}

//------------------------------------------------------------------------------
// Test Fixture Class
//------------------------------------------------------------------------------
class NvmDriver : public ::testing::Test 
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
// Test Cases for NvmDriverUnit_Init
//------------------------------------------------------------------------------
TEST_F(NvmDriver, NvmDriver_Init_ValidConfig_ReturnsOK)
{
    // Arrange
    NvmDriver_Config_t cfg = {
        NVM_TYPE_FLASH,
        0x00000000U,
        0x00010000U,
        256,
        4096,
        false
    };
    
    // Act
    NvmDriver_Status_t status = call_NvmDriverUnit_Init(&cfg);
    
    // Assert
    EXPECT_EQ(NVM_STATUS_OK, status);
}

//------------------------------------------------------------------------------
// Test Cases for NvmDriverUnit_Write
//------------------------------------------------------------------------------
TEST_F(NvmDriver, NvmDriver_Write_ValidData_ReturnsOK)
{
    // Arrange
    NvmDriver_Config_t cfg = {
        NVM_TYPE_FLASH,
        0x00000000U,
        0x00010000U,
        256,
        4096,
        false
    };
    uint8_t data[2] = {0x11, 0x22};
    call_NvmDriverUnit_Init(&cfg);
    
    // Act
    NvmDriver_Status_t status = call_NvmDriverUnit_Write(0, data, 2);
    
    // Assert
    EXPECT_EQ(NVM_STATUS_OK, status);
}

//------------------------------------------------------------------------------
// Test Cases for NvmDriverUnit_Read
//------------------------------------------------------------------------------
TEST_F(NvmDriver, NvmDriver_Read_ValidData_ReturnsOK)
{
    // Arrange
    NvmDriver_Config_t cfg = {
        NVM_TYPE_FLASH,
        0x00000000U,
        0x00010000U,
        256,
        4096,
        false
    };
    uint8_t data[2] = {0x11, 0x22};
    uint8_t out[2] = {0};
    call_NvmDriverUnit_Init(&cfg);
    call_NvmDriverUnit_Write(0, data, 2);
    
    // Act
    NvmDriver_Status_t status = call_NvmDriverUnit_Read(0, out, 2);
    
    // Assert
    EXPECT_EQ(NVM_STATUS_OK, status);
}
