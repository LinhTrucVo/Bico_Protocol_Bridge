//----------------------------------------------------------------------------
// Unit Test file for SPIAPP - Typed SPI API
//----------------------------------------------------------------------------

#include "gtest/gtest.h"
#include "gmock/gmock.h"

extern "C"
{
#include "mockSPIAPP.h"
}

//------------------------------------------------------------------------------
// Test Fixture Class
//------------------------------------------------------------------------------
class SPIAPP : public ::testing::Test 
{
protected:
    void SetUp() override 
    {
        FFF_RESET_HISTORY();
        call_SPIAPP_Init();
    }

    void TearDown() override 
    {
        call_SPIAPP_DeInit();
    }
};

//------------------------------------------------------------------------------
// Init / DeInit
//------------------------------------------------------------------------------
TEST_F(SPIAPP, SPIAPP_Init_Valid_ReturnsOK)
{
    call_SPIAPP_DeInit();
    SPIAPP_Status_t status = call_SPIAPP_Init();
    EXPECT_EQ(SPI_APP_STATUS_OK, status);
}

//------------------------------------------------------------------------------
// SPI Write
//------------------------------------------------------------------------------
TEST_F(SPIAPP, SPIAPP_Write_Valid_ReturnsOK)
{
    uint8_t data[] = {0x9F};
    SPIAPP_Status_t status = call_SPIAPP_Write(0, data, 1);
    EXPECT_EQ(SPI_APP_STATUS_OK, status);
}

TEST_F(SPIAPP, SPIAPP_Write_NullData_ReturnsInvalidParam)
{
    SPIAPP_Status_t status = call_SPIAPP_Write(0, nullptr, 1);
    EXPECT_EQ(SPI_APP_STATUS_INVALID_PARAM, status);
}

TEST_F(SPIAPP, SPIAPP_Write_ZeroLength_ReturnsInvalidParam)
{
    uint8_t data[] = {0x9F};
    SPIAPP_Status_t status = call_SPIAPP_Write(0, data, 0);
    EXPECT_EQ(SPI_APP_STATUS_INVALID_PARAM, status);
}

TEST_F(SPIAPP, SPIAPP_Write_NotInitialized_ReturnsNotInitialized)
{
    call_SPIAPP_DeInit();
    uint8_t data[] = {0x9F};
    SPIAPP_Status_t status = call_SPIAPP_Write(0, data, 1);
    EXPECT_EQ(SPI_APP_STATUS_NOT_INITIALIZED, status);
}

//------------------------------------------------------------------------------
// SPI Transceive
//------------------------------------------------------------------------------
TEST_F(SPIAPP, SPIAPP_Transceive_Valid_ReturnsOK)
{
    uint8_t tx[] = {0x9F};
    uint8_t rx[3] = {0};
    SPIAPP_Status_t status = call_SPIAPP_Transceive(0, tx, 1, rx, 3);
    EXPECT_EQ(SPI_APP_STATUS_OK, status);
}

TEST_F(SPIAPP, SPIAPP_Transceive_NullTx_ReturnsInvalidParam)
{
    uint8_t rx[3] = {0};
    SPIAPP_Status_t status = call_SPIAPP_Transceive(0, nullptr, 1, rx, 3);
    EXPECT_EQ(SPI_APP_STATUS_INVALID_PARAM, status);
}

TEST_F(SPIAPP, SPIAPP_Transceive_NullRx_ReturnsInvalidParam)
{
    uint8_t tx[] = {0x9F};
    SPIAPP_Status_t status = call_SPIAPP_Transceive(0, tx, 1, nullptr, 3);
    EXPECT_EQ(SPI_APP_STATUS_INVALID_PARAM, status);
}

TEST_F(SPIAPP, SPIAPP_Transceive_ZeroTxLength_ReturnsInvalidParam)
{
    uint8_t tx[] = {0x9F};
    uint8_t rx[3] = {0};
    SPIAPP_Status_t status = call_SPIAPP_Transceive(0, tx, 0, rx, 3);
    EXPECT_EQ(SPI_APP_STATUS_INVALID_PARAM, status);
}

TEST_F(SPIAPP, SPIAPP_Transceive_NotInitialized_ReturnsNotInitialized)
{
    call_SPIAPP_DeInit();
    uint8_t tx[] = {0x9F};
    uint8_t rx[3] = {0};
    SPIAPP_Status_t status = call_SPIAPP_Transceive(0, tx, 1, rx, 3);
    EXPECT_EQ(SPI_APP_STATUS_NOT_INITIALIZED, status);
}