//----------------------------------------------------------------------------
// Unit Test file for ANALOGAPP - Typed ADC API
//----------------------------------------------------------------------------

#include "gtest/gtest.h"
#include "gmock/gmock.h"

extern "C"
{
#include "mockANALOGAPP.h"
}

//------------------------------------------------------------------------------
// Test Fixture Class
//------------------------------------------------------------------------------
class ANALOGAPP : public ::testing::Test 
{
protected:
    void SetUp() override 
    {
        FFF_RESET_HISTORY();
        call_ANALOGAPP_Init();
    }

    void TearDown() override 
    {
        call_ANALOGAPP_DeInit();
    }
};

//------------------------------------------------------------------------------
// Test Cases for Init / DeInit
//------------------------------------------------------------------------------
TEST_F(ANALOGAPP, ANALOGAPP_Init_Valid_ReturnsOK)
{
    call_ANALOGAPP_DeInit();
    ANALOGAPP_Status_t status = call_ANALOGAPP_Init();
    EXPECT_EQ(ANALOG_APP_STATUS_OK, status);
}

TEST_F(ANALOGAPP, ANALOGAPP_DeInit_Valid_ReturnsOK)
{
    ANALOGAPP_Status_t status = call_ANALOGAPP_DeInit();
    EXPECT_EQ(ANALOG_APP_STATUS_OK, status);
}

//------------------------------------------------------------------------------
// Test Cases for ReadAdc
//------------------------------------------------------------------------------
TEST_F(ANALOGAPP, ANALOGAPP_ReadAdc_ValidChannel_ReturnsOK)
{
    uint16_t rawValue = 0;
    ANALOGAPP_Status_t status = call_ANALOGAPP_ReadAdc(0, &rawValue);
    EXPECT_EQ(ANALOG_APP_STATUS_OK, status);
}

TEST_F(ANALOGAPP, ANALOGAPP_ReadAdc_InvalidChannel_ReturnsInvalidParam)
{
    uint16_t rawValue = 0;
    ANALOGAPP_Status_t status = call_ANALOGAPP_ReadAdc(8, &rawValue);
    EXPECT_EQ(ANALOG_APP_STATUS_INVALID_PARAM, status);
}

TEST_F(ANALOGAPP, ANALOGAPP_ReadAdc_NullPointer_ReturnsInvalidParam)
{
    ANALOGAPP_Status_t status = call_ANALOGAPP_ReadAdc(0, nullptr);
    EXPECT_EQ(ANALOG_APP_STATUS_INVALID_PARAM, status);
}

TEST_F(ANALOGAPP, ANALOGAPP_ReadAdc_NotInitialized_ReturnsNotInitialized)
{
    call_ANALOGAPP_DeInit();
    uint16_t rawValue = 0;
    ANALOGAPP_Status_t status = call_ANALOGAPP_ReadAdc(0, &rawValue);
    EXPECT_EQ(ANALOG_APP_STATUS_NOT_INITIALIZED, status);
}

TEST_F(ANALOGAPP, ANALOGAPP_ReadAdc_AllChannels_ReturnsOK)
{
    for (uint8_t ch = 0; ch < 8; ch++)
    {
        uint16_t rawValue = 0;
        ANALOGAPP_Status_t status = call_ANALOGAPP_ReadAdc(ch, &rawValue);
        EXPECT_EQ(ANALOG_APP_STATUS_OK, status);
    }
}