//----------------------------------------------------------------------------
// Unit Test file for SerialToDigitalApp - Typed GPIO/PWM API
//----------------------------------------------------------------------------

#include "gtest/gtest.h"
#include "gmock/gmock.h"

extern "C"
{
#include "mockSerialToDigitalApp.h"
}

//------------------------------------------------------------------------------
// Test Fixture Class
//------------------------------------------------------------------------------
class SerialToDigitalApp : public ::testing::Test 
{
protected:
    void SetUp() override 
    {
        FFF_RESET_HISTORY();
        call_SerialToDigitalApp_Init();
    }

    void TearDown() override 
    {
        call_SerialToDigitalApp_DeInit();
    }
};

//------------------------------------------------------------------------------
// Init / DeInit
//------------------------------------------------------------------------------
TEST_F(SerialToDigitalApp, SerialToDigitalApp_Init_Valid_ReturnsOK)
{
    call_SerialToDigitalApp_DeInit();
    SerialToDigitalApp_Status_t status = call_SerialToDigitalApp_Init();
    EXPECT_EQ(SERIAL_TO_DIGITAL_APP_STATUS_OK, status);
}

//------------------------------------------------------------------------------
// GPIO Write
//------------------------------------------------------------------------------
TEST_F(SerialToDigitalApp, SerialToDigitalApp_WriteGpio_ValidPin_ReturnsOK)
{
    SerialToDigitalApp_Status_t status = call_SerialToDigitalApp_WriteGpio(5, 1);
    EXPECT_EQ(SERIAL_TO_DIGITAL_APP_STATUS_OK, status);
}

TEST_F(SerialToDigitalApp, SerialToDigitalApp_WriteGpio_InvalidPin_ReturnsInvalidParam)
{
    SerialToDigitalApp_Status_t status = call_SerialToDigitalApp_WriteGpio(32, 1);
    EXPECT_EQ(SERIAL_TO_DIGITAL_APP_STATUS_INVALID_PARAM, status);
}

TEST_F(SerialToDigitalApp, SerialToDigitalApp_WriteGpio_NotInitialized_ReturnsNotInitialized)
{
    call_SerialToDigitalApp_DeInit();
    SerialToDigitalApp_Status_t status = call_SerialToDigitalApp_WriteGpio(5, 1);
    EXPECT_EQ(SERIAL_TO_DIGITAL_APP_STATUS_NOT_INITIALIZED, status);
}

//------------------------------------------------------------------------------
// GPIO Read
//------------------------------------------------------------------------------
TEST_F(SerialToDigitalApp, SerialToDigitalApp_ReadGpio_ValidPin_ReturnsOK)
{
    call_SerialToDigitalApp_WriteGpio(3, 1);
    uint8_t state = 0;
    SerialToDigitalApp_Status_t status = call_SerialToDigitalApp_ReadGpio(3, &state);
    EXPECT_EQ(SERIAL_TO_DIGITAL_APP_STATUS_OK, status);
    EXPECT_EQ(1U, state);
}

TEST_F(SerialToDigitalApp, SerialToDigitalApp_ReadGpio_InvalidPin_ReturnsInvalidParam)
{
    uint8_t state = 0;
    SerialToDigitalApp_Status_t status = call_SerialToDigitalApp_ReadGpio(32, &state);
    EXPECT_EQ(SERIAL_TO_DIGITAL_APP_STATUS_INVALID_PARAM, status);
}

TEST_F(SerialToDigitalApp, SerialToDigitalApp_ReadGpio_NullPointer_ReturnsInvalidParam)
{
    SerialToDigitalApp_Status_t status = call_SerialToDigitalApp_ReadGpio(3, nullptr);
    EXPECT_EQ(SERIAL_TO_DIGITAL_APP_STATUS_INVALID_PARAM, status);
}

//------------------------------------------------------------------------------
// PWM Start / Stop
//------------------------------------------------------------------------------
TEST_F(SerialToDigitalApp, SerialToDigitalApp_StartPwm_ValidChannel_ReturnsOK)
{
    SerialToDigitalApp_Status_t status = call_SerialToDigitalApp_StartPwm(1);
    EXPECT_EQ(SERIAL_TO_DIGITAL_APP_STATUS_OK, status);
}

TEST_F(SerialToDigitalApp, SerialToDigitalApp_StartPwm_InvalidChannel_ReturnsInvalidParam)
{
    SerialToDigitalApp_Status_t status = call_SerialToDigitalApp_StartPwm(8);
    EXPECT_EQ(SERIAL_TO_DIGITAL_APP_STATUS_INVALID_PARAM, status);
}

TEST_F(SerialToDigitalApp, SerialToDigitalApp_StopPwm_ValidChannel_ReturnsOK)
{
    SerialToDigitalApp_Status_t status = call_SerialToDigitalApp_StopPwm(1);
    EXPECT_EQ(SERIAL_TO_DIGITAL_APP_STATUS_OK, status);
}

TEST_F(SerialToDigitalApp, SerialToDigitalApp_StopPwm_InvalidChannel_ReturnsInvalidParam)
{
    SerialToDigitalApp_Status_t status = call_SerialToDigitalApp_StopPwm(8);
    EXPECT_EQ(SERIAL_TO_DIGITAL_APP_STATUS_INVALID_PARAM, status);
}