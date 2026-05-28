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
        call_DigitalServiceUnit_Init();
    }

    void TearDown() override 
    {
        call_DigitalServiceUnit_DeInit();
    }
};

//------------------------------------------------------------------------------
// Init / DeInit
//------------------------------------------------------------------------------
TEST_F(DIGITALAPP, DigitalServiceUnit_Init_Valid_ReturnsOK)
{
    call_DigitalServiceUnit_DeInit();
    DigitalService_Status_t status = call_DigitalServiceUnit_Init();
    EXPECT_EQ(DIGITALSERVICE_STATUS_OK, status);
}

//------------------------------------------------------------------------------
// GPIO Write
//------------------------------------------------------------------------------
TEST_F(DIGITALAPP, DigitalServiceUnit_WriteGpio_ValidPin_ReturnsOK)
{
    DigitalService_Status_t status = call_DigitalServiceUnit_WriteGpio(5, 1);
    EXPECT_EQ(DIGITALSERVICE_STATUS_OK, status);
}

TEST_F(DIGITALAPP, DigitalServiceUnit_WriteGpio_InvalidPin_ReturnsInvalidParam)
{
    DigitalService_Status_t status = call_DigitalServiceUnit_WriteGpio(32, 1);
    EXPECT_EQ(DIGITALSERVICE_STATUS_INVALID_PARAM, status);
}

TEST_F(DIGITALAPP, DigitalServiceUnit_WriteGpio_NotInitialized_ReturnsNotInitialized)
{
    call_DigitalServiceUnit_DeInit();
    DigitalService_Status_t status = call_DigitalServiceUnit_WriteGpio(5, 1);
    EXPECT_EQ(DIGITALSERVICE_STATUS_NOT_INITIALIZED, status);
}

//------------------------------------------------------------------------------
// GPIO Read
//------------------------------------------------------------------------------
TEST_F(DIGITALAPP, DigitalServiceUnit_ReadGpio_ValidPin_ReturnsOK)
{
    call_DigitalServiceUnit_WriteGpio(3, 1);
    uint8_t state = 0;
    DigitalService_Status_t status = call_DigitalServiceUnit_ReadGpio(3, &state);
    EXPECT_EQ(DIGITALSERVICE_STATUS_OK, status);
    EXPECT_EQ(1U, state);
}

TEST_F(DIGITALAPP, DigitalServiceUnit_ReadGpio_InvalidPin_ReturnsInvalidParam)
{
    uint8_t state = 0;
    DigitalService_Status_t status = call_DigitalServiceUnit_ReadGpio(32, &state);
    EXPECT_EQ(DIGITALSERVICE_STATUS_INVALID_PARAM, status);
}

TEST_F(DIGITALAPP, DigitalServiceUnit_ReadGpio_NullPointer_ReturnsInvalidParam)
{
    DigitalService_Status_t status = call_DigitalServiceUnit_ReadGpio(3, nullptr);
    EXPECT_EQ(DIGITALSERVICE_STATUS_INVALID_PARAM, status);
}

//------------------------------------------------------------------------------
// PWM Start / Stop
//------------------------------------------------------------------------------
TEST_F(DIGITALAPP, DigitalServiceUnit_StartPwm_ValidChannel_ReturnsOK)
{
    DigitalService_Status_t status = call_DigitalServiceUnit_StartPwm(1);
    EXPECT_EQ(DIGITALSERVICE_STATUS_OK, status);
}

TEST_F(DIGITALAPP, DigitalServiceUnit_StartPwm_InvalidChannel_ReturnsInvalidParam)
{
    DigitalService_Status_t status = call_DigitalServiceUnit_StartPwm(8);
    EXPECT_EQ(DIGITALSERVICE_STATUS_INVALID_PARAM, status);
}

TEST_F(DIGITALAPP, DigitalServiceUnit_StopPwm_ValidChannel_ReturnsOK)
{
    DigitalService_Status_t status = call_DigitalServiceUnit_StopPwm(1);
    EXPECT_EQ(DIGITALSERVICE_STATUS_OK, status);
}

TEST_F(DIGITALAPP, DigitalServiceUnit_StopPwm_InvalidChannel_ReturnsInvalidParam)
{
    DigitalService_Status_t status = call_DigitalServiceUnit_StopPwm(8);
    EXPECT_EQ(DIGITALSERVICE_STATUS_INVALID_PARAM, status);
}