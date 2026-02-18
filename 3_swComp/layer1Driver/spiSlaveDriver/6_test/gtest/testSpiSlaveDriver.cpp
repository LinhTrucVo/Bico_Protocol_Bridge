//----------------------------------------------------------------------------
// Unit Test file for SPI Slave Driver component
//----------------------------------------------------------------------------

#include "gtest/gtest.h"
#include "gmock/gmock.h"

// Unit under test
extern "C"
{
#include "mockSpiSlaveDriver.h"
}

//------------------------------------------------------------------------------
// Test Fixture Class
//------------------------------------------------------------------------------
class SpiSlaveDriver : public ::testing::Test 
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
// Test Cases for SpiSlaveDriverUnit_Init
//------------------------------------------------------------------------------
TEST_F(SpiSlaveDriver, SpiSlaveDriver_Init_ValidConfig_ReturnsOK)
{
    // Arrange
    SpiSlaveDriver_Config_t cfg = {
        SPI_SLAVE_MODE_0,
        SPI_SLAVE_BITORDER_MSB_FIRST,
        false,
        false
    };
    
    // Act
    SpiSlaveDriver_Status_t status = call_SpiSlaveDriverUnit_Init(&cfg);
    
    // Assert
    EXPECT_EQ(SPI_SLAVE_STATUS_OK, status);
}

//------------------------------------------------------------------------------
// Test Cases for SpiSlaveDriverUnit_SetRxBuffer
//------------------------------------------------------------------------------
TEST_F(SpiSlaveDriver, SpiSlaveDriver_SetRxBuffer_ValidBuffer_ReturnsOK)
{
    // Arrange
    uint8_t rx[4] = {0};
    SpiSlaveDriver_Config_t cfg = {
        SPI_SLAVE_MODE_0,
        SPI_SLAVE_BITORDER_MSB_FIRST,
        false,
        false
    };
    call_SpiSlaveDriverUnit_Init(&cfg);
    
    // Act
    SpiSlaveDriver_Status_t status = call_SpiSlaveDriverUnit_SetRxBuffer(rx, sizeof(rx));
    
    // Assert
    EXPECT_EQ(SPI_SLAVE_STATUS_OK, status);
}

//------------------------------------------------------------------------------
// Test Cases for SpiSlaveDriverUnit_SetTxBuffer
//------------------------------------------------------------------------------
TEST_F(SpiSlaveDriver, SpiSlaveDriver_SetTxBuffer_ValidBuffer_ReturnsOK)
{
    // Arrange
    uint8_t tx[2] = {0xAA, 0x55};
    SpiSlaveDriver_Config_t cfg = {
        SPI_SLAVE_MODE_0,
        SPI_SLAVE_BITORDER_MSB_FIRST,
        false,
        false
    };
    call_SpiSlaveDriverUnit_Init(&cfg);
    
    // Act
    SpiSlaveDriver_Status_t status = call_SpiSlaveDriverUnit_SetTxBuffer(tx, sizeof(tx));
    
    // Assert
    EXPECT_EQ(SPI_SLAVE_STATUS_OK, status);
}
