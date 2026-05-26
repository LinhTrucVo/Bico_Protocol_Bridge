//----------------------------------------------------------------------------
// Unit Test file for SerialToAnalogApp - Typed ADC API
//----------------------------------------------------------------------------

#include "gtest/gtest.h"
#include "gmock/gmock.h"

extern "C"
{
#include "mockSerialToAnalogApp.h"
}

//------------------------------------------------------------------------------
// Test Fixture Class
//------------------------------------------------------------------------------
class SerialToAnalogApp : public ::testing::Test 
{
protected:
    void SetUp() override 
    {
        FFF_RESET_HISTORY();
        call_SerialToAnalogApp_Init();
    }

    void TearDown() override 
    {
        call_SerialToAnalogApp_DeInit();
    }
};

//------------------------------------------------------------------------------
// Test Cases for Init / DeInit
//------------------------------------------------------------------------------
TEST_F(SerialToAnalogApp, SerialToAnalogApp_Init_Valid_ReturnsOK)
{
    call_SerialToAnalogApp_DeInit();
    SerialToAnalogApp_Status_t status = call_SerialToAnalogApp_Init();
    EXPECT_EQ(SERIAL_TO_ANALOG_APP_STATUS_OK, status);
}

TEST_F(SerialToAnalogApp, SerialToAnalogApp_DeInit_Valid_ReturnsOK)
{
    SerialToAnalogApp_Status_t status = call_SerialToAnalogApp_DeInit();
    EXPECT_EQ(SERIAL_TO_ANALOG_APP_STATUS_OK, status);
}

//------------------------------------------------------------------------------
// Test Cases for ReadAdc
//------------------------------------------------------------------------------
TEST_F(SerialToAnalogApp, SerialToAnalogApp_ReadAdc_ValidChannel_ReturnsOK)
{
    uint16_t rawValue = 0;
    SerialToAnalogApp_Status_t status = call_SerialToAnalogApp_ReadAdc(0, &rawValue);
    EXPECT_EQ(SERIAL_TO_ANALOG_APP_STATUS_OK, status);
}

TEST_F(SerialToAnalogApp, SerialToAnalogApp_ReadAdc_InvalidChannel_ReturnsInvalidParam)
{
    uint16_t rawValue = 0;
    SerialToAnalogApp_Status_t status = call_SerialToAnalogApp_ReadAdc(8, &rawValue);
    EXPECT_EQ(SERIAL_TO_ANALOG_APP_STATUS_INVALID_PARAM, status);
}

TEST_F(SerialToAnalogApp, SerialToAnalogApp_ReadAdc_NullPointer_ReturnsInvalidParam)
{
    SerialToAnalogApp_Status_t status = call_SerialToAnalogApp_ReadAdc(0, nullptr);
    EXPECT_EQ(SERIAL_TO_ANALOG_APP_STATUS_INVALID_PARAM, status);
}

TEST_F(SerialToAnalogApp, SerialToAnalogApp_ReadAdc_NotInitialized_ReturnsNotInitialized)
{
    call_SerialToAnalogApp_DeInit();
    uint16_t rawValue = 0;
    SerialToAnalogApp_Status_t status = call_SerialToAnalogApp_ReadAdc(0, &rawValue);
    EXPECT_EQ(SERIAL_TO_ANALOG_APP_STATUS_NOT_INITIALIZED, status);
}

TEST_F(SerialToAnalogApp, SerialToAnalogApp_ReadAdc_AllChannels_ReturnsOK)
{
    for (uint8_t ch = 0; ch < 8; ch++)
    {
        uint16_t rawValue = 0;
        SerialToAnalogApp_Status_t status = call_SerialToAnalogApp_ReadAdc(ch, &rawValue);
        EXPECT_EQ(SERIAL_TO_ANALOG_APP_STATUS_OK, status);
    }
}