//----------------------------------------------------------------------------
// Unit Test file for DIGITALAPP - Typed GPIO/PWM API
//----------------------------------------------------------------------------

#include "gtest/gtest.h"
#include "gmock/gmock.h"

extern "C"
{
#include "mockDIGITALAPP.h"
}

//------------------------------------------------------------------------------
// Test Fixture Class
//------------------------------------------------------------------------------
class DIGITALAPP : public ::testing::Test 
{
protected:
    void SetUp() override 
    {
        FFF_RESET_HISTORY();
        call_DIGITALAPP_Init();
    }

    void TearDown() override 
    {
        call_DIGITALAPP_DeInit();
    }
};

//------------------------------------------------------------------------------
// Init / DeInit
//------------------------------------------------------------------------------
TEST_F(DIGITALAPP, DIGITALAPP_Init_Valid_ReturnsOK)
{
    call_DIGITALAPP_DeInit();
    DIGITALAPP_Status_t status = call_DIGITALAPP_Init();
    EXPECT_EQ(DIGITAL_APP_STATUS_OK, status);
}

//------------------------------------------------------------------------------
// GPIO Write
//------------------------------------------------------------------------------
TEST_F(DIGITALAPP, DIGITALAPP_WriteGpio_ValidPin_ReturnsOK)
{
    DIGITALAPP_Status_t status = call_DIGITALAPP_WriteGpio(5, 1);
    EXPECT_EQ(DIGITAL_APP_STATUS_OK, status);
}

TEST_F(DIGITALAPP, DIGITALAPP_WriteGpio_InvalidPin_ReturnsInvalidParam)
{
    DIGITALAPP_Status_t status = call_DIGITALAPP_WriteGpio(32, 1);
    EXPECT_EQ(DIGITAL_APP_STATUS_INVALID_PARAM, status);
}

TEST_F(DIGITALAPP, DIGITALAPP_WriteGpio_NotInitialized_ReturnsNotInitialized)
{
    call_DIGITALAPP_DeInit();
    DIGITALAPP_Status_t status = call_DIGITALAPP_WriteGpio(5, 1);
    EXPECT_EQ(DIGITAL_APP_STATUS_NOT_INITIALIZED, status);
}

//------------------------------------------------------------------------------
// GPIO Read
//------------------------------------------------------------------------------
TEST_F(DIGITALAPP, DIGITALAPP_ReadGpio_ValidPin_ReturnsOK)
{
    call_DIGITALAPP_WriteGpio(3, 1);
    uint8_t state = 0;
    DIGITALAPP_Status_t status = call_DIGITALAPP_ReadGpio(3, &state);
    EXPECT_EQ(DIGITAL_APP_STATUS_OK, status);
    EXPECT_EQ(1U, state);
}

TEST_F(DIGITALAPP, DIGITALAPP_ReadGpio_InvalidPin_ReturnsInvalidParam)
{
    uint8_t state = 0;
    DIGITALAPP_Status_t status = call_DIGITALAPP_ReadGpio(32, &state);
    EXPECT_EQ(DIGITAL_APP_STATUS_INVALID_PARAM, status);
}

TEST_F(DIGITALAPP, DIGITALAPP_ReadGpio_NullPointer_ReturnsInvalidParam)
{
    DIGITALAPP_Status_t status = call_DIGITALAPP_ReadGpio(3, nullptr);
    EXPECT_EQ(DIGITAL_APP_STATUS_INVALID_PARAM, status);
}

//------------------------------------------------------------------------------
// PWM Start / Stop
//------------------------------------------------------------------------------
TEST_F(DIGITALAPP, DIGITALAPP_StartPwm_ValidChannel_ReturnsOK)
{
    DIGITALAPP_Status_t status = call_DIGITALAPP_StartPwm(1);
    EXPECT_EQ(DIGITAL_APP_STATUS_OK, status);
}

TEST_F(DIGITALAPP, DIGITALAPP_StartPwm_InvalidChannel_ReturnsInvalidParam)
{
    DIGITALAPP_Status_t status = call_DIGITALAPP_StartPwm(8);
    EXPECT_EQ(DIGITAL_APP_STATUS_INVALID_PARAM, status);
}

TEST_F(DIGITALAPP, DIGITALAPP_StopPwm_ValidChannel_ReturnsOK)
{
    DIGITALAPP_Status_t status = call_DIGITALAPP_StopPwm(1);
    EXPECT_EQ(DIGITAL_APP_STATUS_OK, status);
}

TEST_F(DIGITALAPP, DIGITALAPP_StopPwm_InvalidChannel_ReturnsInvalidParam)
{
    DIGITALAPP_Status_t status = call_DIGITALAPP_StopPwm(8);
    EXPECT_EQ(DIGITAL_APP_STATUS_INVALID_PARAM, status);
}