//----------------------------------------------------------------------------
// Unit Test file for SerialToSPIApp - Typed SPI API
//----------------------------------------------------------------------------

#include "gtest/gtest.h"
#include "gmock/gmock.h"

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
        FFF_RESET_HISTORY();
        call_SerialToSPIApp_Init();
    }

    void TearDown() override 
    {
        call_SerialToSPIApp_DeInit();
    }
};

//------------------------------------------------------------------------------
// Init / DeInit
//------------------------------------------------------------------------------
TEST_F(SerialToSPIApp, SerialToSPIApp_Init_Valid_ReturnsOK)
{
    call_SerialToSPIApp_DeInit();
    SerialToSPIApp_Status_t status = call_SerialToSPIApp_Init();
    EXPECT_EQ(SERIAL_TO_SPI_APP_STATUS_OK, status);
}

//------------------------------------------------------------------------------
// SPI Write
//------------------------------------------------------------------------------
TEST_F(SerialToSPIApp, SerialToSPIApp_Write_Valid_ReturnsOK)
{
    uint8_t data[] = {0x9F};
    SerialToSPIApp_Status_t status = call_SerialToSPIApp_Write(0, data, 1);
    EXPECT_EQ(SERIAL_TO_SPI_APP_STATUS_OK, status);
}

TEST_F(SerialToSPIApp, SerialToSPIApp_Write_NullData_ReturnsInvalidParam)
{
    SerialToSPIApp_Status_t status = call_SerialToSPIApp_Write(0, nullptr, 1);
    EXPECT_EQ(SERIAL_TO_SPI_APP_STATUS_INVALID_PARAM, status);
}

TEST_F(SerialToSPIApp, SerialToSPIApp_Write_ZeroLength_ReturnsInvalidParam)
{
    uint8_t data[] = {0x9F};
    SerialToSPIApp_Status_t status = call_SerialToSPIApp_Write(0, data, 0);
    EXPECT_EQ(SERIAL_TO_SPI_APP_STATUS_INVALID_PARAM, status);
}

TEST_F(SerialToSPIApp, SerialToSPIApp_Write_NotInitialized_ReturnsNotInitialized)
{
    call_SerialToSPIApp_DeInit();
    uint8_t data[] = {0x9F};
    SerialToSPIApp_Status_t status = call_SerialToSPIApp_Write(0, data, 1);
    EXPECT_EQ(SERIAL_TO_SPI_APP_STATUS_NOT_INITIALIZED, status);
}

//------------------------------------------------------------------------------
// SPI Transceive
//------------------------------------------------------------------------------
TEST_F(SerialToSPIApp, SerialToSPIApp_Transceive_Valid_ReturnsOK)
{
    uint8_t tx[] = {0x9F};
    uint8_t rx[3] = {0};
    SerialToSPIApp_Status_t status = call_SerialToSPIApp_Transceive(0, tx, 1, rx, 3);
    EXPECT_EQ(SERIAL_TO_SPI_APP_STATUS_OK, status);
}

TEST_F(SerialToSPIApp, SerialToSPIApp_Transceive_NullTx_ReturnsInvalidParam)
{
    uint8_t rx[3] = {0};
    SerialToSPIApp_Status_t status = call_SerialToSPIApp_Transceive(0, nullptr, 1, rx, 3);
    EXPECT_EQ(SERIAL_TO_SPI_APP_STATUS_INVALID_PARAM, status);
}

TEST_F(SerialToSPIApp, SerialToSPIApp_Transceive_NullRx_ReturnsInvalidParam)
{
    uint8_t tx[] = {0x9F};
    SerialToSPIApp_Status_t status = call_SerialToSPIApp_Transceive(0, tx, 1, nullptr, 3);
    EXPECT_EQ(SERIAL_TO_SPI_APP_STATUS_INVALID_PARAM, status);
}

TEST_F(SerialToSPIApp, SerialToSPIApp_Transceive_ZeroTxLength_ReturnsInvalidParam)
{
    uint8_t tx[] = {0x9F};
    uint8_t rx[3] = {0};
    SerialToSPIApp_Status_t status = call_SerialToSPIApp_Transceive(0, tx, 0, rx, 3);
    EXPECT_EQ(SERIAL_TO_SPI_APP_STATUS_INVALID_PARAM, status);
}

TEST_F(SerialToSPIApp, SerialToSPIApp_Transceive_NotInitialized_ReturnsNotInitialized)
{
    call_SerialToSPIApp_DeInit();
    uint8_t tx[] = {0x9F};
    uint8_t rx[3] = {0};
    SerialToSPIApp_Status_t status = call_SerialToSPIApp_Transceive(0, tx, 1, rx, 3);
    EXPECT_EQ(SERIAL_TO_SPI_APP_STATUS_NOT_INITIALIZED, status);
}