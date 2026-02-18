//----------------------------------------------------------------------------
// Unit Test file for SPI Master Driver component
//----------------------------------------------------------------------------

#include "gtest/gtest.h"
#include "gmock/gmock.h"

// Unit under test
extern "C"
{
#include "mockSpiMasterDriver.h"
}

//------------------------------------------------------------------------------
// Test Fixture Class
//------------------------------------------------------------------------------
class SpiMasterDriver : public ::testing::Test 
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
// Test Cases for SpiMasterDriverUnit_Init
//------------------------------------------------------------------------------
TEST_F(SpiMasterDriver, SpiMasterDriver_Init_ValidConfig_ReturnsOK)
{
    // Arrange
    SpiMasterDriver_Config_t cfg = {
        1000000,
        SPI_MODE_0,
        SPI_BITORDER_MSB_FIRST,
        SPI_DATASIZE_8BIT,
        SPI_CS_MODE_MANUAL,
        false,
        false
    };
    
    // Act
    SpiMasterDriver_Status_t status = call_SpiMasterDriverUnit_Init(&cfg);
    
    // Assert
    EXPECT_EQ(SPI_MASTER_STATUS_OK, status);
}

//------------------------------------------------------------------------------
// Test Cases for SpiMasterDriverUnit_Transmit
//------------------------------------------------------------------------------
TEST_F(SpiMasterDriver, SpiMasterDriver_Transmit_ValidData_ReturnsOK)
{
    // Arrange
    uint8_t data[2] = {0x01, 0x02};
    SpiMasterDriver_Config_t cfg = {
        1000000,
        SPI_MODE_0,
        SPI_BITORDER_MSB_FIRST,
        SPI_DATASIZE_8BIT,
        SPI_CS_MODE_MANUAL,
        false,
        false
    };
    call_SpiMasterDriverUnit_Init(&cfg);
    
    // Act
    SpiMasterDriver_Status_t status = call_SpiMasterDriverUnit_Transmit(data, 2);
    
    // Assert
    EXPECT_EQ(SPI_MASTER_STATUS_OK, status);
}

//------------------------------------------------------------------------------
// Test Cases for SpiMasterDriverUnit_Receive
//------------------------------------------------------------------------------
TEST_F(SpiMasterDriver, SpiMasterDriver_Receive_ValidBuffer_ReturnsOK)
{
    // Arrange
    uint8_t data[2] = {0};
    SpiMasterDriver_Config_t cfg = {
        1000000,
        SPI_MODE_0,
        SPI_BITORDER_MSB_FIRST,
        SPI_DATASIZE_8BIT,
        SPI_CS_MODE_MANUAL,
        false,
        false
    };
    call_SpiMasterDriverUnit_Init(&cfg);
    
    // Act
    SpiMasterDriver_Status_t status = call_SpiMasterDriverUnit_Receive(data, 2);
    
    // Assert
    EXPECT_EQ(SPI_MASTER_STATUS_OK, status);
}
