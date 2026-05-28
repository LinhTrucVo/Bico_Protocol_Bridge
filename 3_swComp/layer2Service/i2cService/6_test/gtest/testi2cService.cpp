//----------------------------------------------------------------------------
// Unit Test file for I2CAPP - Typed I2C API
//----------------------------------------------------------------------------

#include "gtest/gtest.h"
#include "gmock/gmock.h"

extern "C"
{
#include "mockI2CAPP.h"
}

//------------------------------------------------------------------------------
// Test Fixture Class
//------------------------------------------------------------------------------
class I2CAPP : public ::testing::Test 
{
protected:
    void SetUp() override 
    {
        FFF_RESET_HISTORY();
        call_I2cServiceUnit_Init();
    }

    void TearDown() override 
    {
        call_I2cServiceUnit_DeInit();
    }
};

//------------------------------------------------------------------------------
// Init / DeInit
//------------------------------------------------------------------------------
TEST_F(I2CAPP, I2cServiceUnit_Init_Valid_ReturnsOK)
{
    call_I2cServiceUnit_DeInit();
    I2cService_Status_t status = call_I2cServiceUnit_Init();
    EXPECT_EQ(I2CSERVICE_STATUS_OK, status);
}

//------------------------------------------------------------------------------
// I2C Write
//------------------------------------------------------------------------------
TEST_F(I2CAPP, I2CAPP_Write_Valid_ReturnsOK)
{
    uint8_t data[] = {0x10, 0xAA};
    I2cService_Status_t status = call_I2cServiceUnit_Write(0x50, data, 2);
    EXPECT_EQ(I2CSERVICE_STATUS_OK, status);
}

TEST_F(I2CAPP, I2CAPP_Write_NullData_ReturnsInvalidParam)
{
    I2cService_Status_t status = call_I2cServiceUnit_Write(0x50, nullptr, 2);
    EXPECT_EQ(I2CSERVICE_STATUS_INVALID_PARAM, status);
}

TEST_F(I2CAPP, I2CAPP_Write_ZeroLength_ReturnsInvalidParam)
{
    uint8_t data[] = {0x10};
    I2cService_Status_t status = call_I2cServiceUnit_Write(0x50, data, 0);
    EXPECT_EQ(I2CSERVICE_STATUS_INVALID_PARAM, status);
}

TEST_F(I2CAPP, I2CAPP_Write_OverMaxTransfer_ReturnsInvalidParam)
{
    uint8_t data[257] = {0};
    I2cService_Status_t status = call_I2cServiceUnit_Write(0x50, data, 257);
    EXPECT_EQ(I2CSERVICE_STATUS_INVALID_PARAM, status);
}

TEST_F(I2CAPP, I2CAPP_Write_NotInitialized_ReturnsNotInitialized)
{
    call_I2cServiceUnit_DeInit();
    uint8_t data[] = {0x10};
    I2cService_Status_t status = call_I2cServiceUnit_Write(0x50, data, 1);
    EXPECT_EQ(I2CSERVICE_STATUS_NOT_INITIALIZED, status);
}

//------------------------------------------------------------------------------
// I2C Read
//------------------------------------------------------------------------------
TEST_F(I2CAPP, I2cServiceUnit_Read_Valid_ReturnsOK)
{
    uint8_t data[4] = {0};
    I2cService_Status_t status = call_I2cServiceUnit_Read(0x50, data, 4);
    EXPECT_EQ(I2CSERVICE_STATUS_OK, status);
}

TEST_F(I2CAPP, I2cServiceUnit_Read_NullData_ReturnsInvalidParam)
{
    I2cService_Status_t status = call_I2cServiceUnit_Read(0x50, nullptr, 4);
    EXPECT_EQ(I2CSERVICE_STATUS_INVALID_PARAM, status);
}

TEST_F(I2CAPP, I2cServiceUnit_Read_ZeroLength_ReturnsInvalidParam)
{
    uint8_t data[4] = {0};
    I2cService_Status_t status = call_I2cServiceUnit_Read(0x50, data, 0);
    EXPECT_EQ(I2CSERVICE_STATUS_INVALID_PARAM, status);
}

TEST_F(I2CAPP, I2cServiceUnit_Read_NotInitialized_ReturnsNotInitialized)
{
    call_I2cServiceUnit_DeInit();
    uint8_t data[4] = {0};
    I2cService_Status_t status = call_I2cServiceUnit_Read(0x50, data, 4);
    EXPECT_EQ(I2CSERVICE_STATUS_NOT_INITIALIZED, status);
}