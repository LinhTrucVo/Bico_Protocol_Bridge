//----------------------------------------------------------------------------
// Unit Test file for SerialToI2CApp - Typed I2C API
//----------------------------------------------------------------------------

#include "gtest/gtest.h"
#include "gmock/gmock.h"

extern "C"
{
#include "mockSerialToI2CApp.h"
}

//------------------------------------------------------------------------------
// Test Fixture Class
//------------------------------------------------------------------------------
class SerialToI2CApp : public ::testing::Test 
{
protected:
    void SetUp() override 
    {
        FFF_RESET_HISTORY();
        call_SerialToI2CApp_Init();
    }

    void TearDown() override 
    {
        call_SerialToI2CApp_DeInit();
    }
};

//------------------------------------------------------------------------------
// Init / DeInit
//------------------------------------------------------------------------------
TEST_F(SerialToI2CApp, SerialToI2CApp_Init_Valid_ReturnsOK)
{
    call_SerialToI2CApp_DeInit();
    SerialToI2CApp_Status_t status = call_SerialToI2CApp_Init();
    EXPECT_EQ(SERIAL_TO_I2C_APP_STATUS_OK, status);
}

//------------------------------------------------------------------------------
// I2C Write
//------------------------------------------------------------------------------
TEST_F(SerialToI2CApp, SerialToI2CApp_Write_Valid_ReturnsOK)
{
    uint8_t data[] = {0x10, 0xAA};
    SerialToI2CApp_Status_t status = call_SerialToI2CApp_Write(0x50, data, 2);
    EXPECT_EQ(SERIAL_TO_I2C_APP_STATUS_OK, status);
}

TEST_F(SerialToI2CApp, SerialToI2CApp_Write_NullData_ReturnsInvalidParam)
{
    SerialToI2CApp_Status_t status = call_SerialToI2CApp_Write(0x50, nullptr, 2);
    EXPECT_EQ(SERIAL_TO_I2C_APP_STATUS_INVALID_PARAM, status);
}

TEST_F(SerialToI2CApp, SerialToI2CApp_Write_ZeroLength_ReturnsInvalidParam)
{
    uint8_t data[] = {0x10};
    SerialToI2CApp_Status_t status = call_SerialToI2CApp_Write(0x50, data, 0);
    EXPECT_EQ(SERIAL_TO_I2C_APP_STATUS_INVALID_PARAM, status);
}

TEST_F(SerialToI2CApp, SerialToI2CApp_Write_OverMaxTransfer_ReturnsInvalidParam)
{
    uint8_t data[257] = {0};
    SerialToI2CApp_Status_t status = call_SerialToI2CApp_Write(0x50, data, 257);
    EXPECT_EQ(SERIAL_TO_I2C_APP_STATUS_INVALID_PARAM, status);
}

TEST_F(SerialToI2CApp, SerialToI2CApp_Write_NotInitialized_ReturnsNotInitialized)
{
    call_SerialToI2CApp_DeInit();
    uint8_t data[] = {0x10};
    SerialToI2CApp_Status_t status = call_SerialToI2CApp_Write(0x50, data, 1);
    EXPECT_EQ(SERIAL_TO_I2C_APP_STATUS_NOT_INITIALIZED, status);
}

//------------------------------------------------------------------------------
// I2C Read
//------------------------------------------------------------------------------
TEST_F(SerialToI2CApp, SerialToI2CApp_Read_Valid_ReturnsOK)
{
    uint8_t data[4] = {0};
    SerialToI2CApp_Status_t status = call_SerialToI2CApp_Read(0x50, data, 4);
    EXPECT_EQ(SERIAL_TO_I2C_APP_STATUS_OK, status);
}

TEST_F(SerialToI2CApp, SerialToI2CApp_Read_NullData_ReturnsInvalidParam)
{
    SerialToI2CApp_Status_t status = call_SerialToI2CApp_Read(0x50, nullptr, 4);
    EXPECT_EQ(SERIAL_TO_I2C_APP_STATUS_INVALID_PARAM, status);
}

TEST_F(SerialToI2CApp, SerialToI2CApp_Read_ZeroLength_ReturnsInvalidParam)
{
    uint8_t data[4] = {0};
    SerialToI2CApp_Status_t status = call_SerialToI2CApp_Read(0x50, data, 0);
    EXPECT_EQ(SERIAL_TO_I2C_APP_STATUS_INVALID_PARAM, status);
}

TEST_F(SerialToI2CApp, SerialToI2CApp_Read_NotInitialized_ReturnsNotInitialized)
{
    call_SerialToI2CApp_DeInit();
    uint8_t data[4] = {0};
    SerialToI2CApp_Status_t status = call_SerialToI2CApp_Read(0x50, data, 4);
    EXPECT_EQ(SERIAL_TO_I2C_APP_STATUS_NOT_INITIALIZED, status);
}