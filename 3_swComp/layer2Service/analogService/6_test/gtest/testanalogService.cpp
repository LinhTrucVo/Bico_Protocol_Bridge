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
        call_AnalogServiceUnit_Init();
    }

    void TearDown() override 
    {
        call_AnalogServiceUnit_DeInit();
    }
};

//------------------------------------------------------------------------------
// Test Cases for Init / DeInit
//------------------------------------------------------------------------------
TEST_F(ANALOGAPP, AnalogServiceUnit_Init_Valid_ReturnsOK)
{
    call_AnalogServiceUnit_DeInit();
    AnalogService_Status_t status = call_AnalogServiceUnit_Init();
    EXPECT_EQ(ANALOGSERVICE_STATUS_OK, status);
}

TEST_F(ANALOGAPP, AnalogServiceUnit_DeInit_Valid_ReturnsOK)
{
    AnalogService_Status_t status = call_AnalogServiceUnit_DeInit();
    EXPECT_EQ(ANALOGSERVICE_STATUS_OK, status);
}

//------------------------------------------------------------------------------
// Test Cases for ReadAdc
//------------------------------------------------------------------------------
TEST_F(ANALOGAPP, AnalogServiceUnit_ReadAdc_ValidChannel_ReturnsOK)
{
    uint16_t rawValue = 0;
    AnalogService_Status_t status = call_AnalogServiceUnit_ReadAdc(0, &rawValue);
    EXPECT_EQ(ANALOGSERVICE_STATUS_OK, status);
}

TEST_F(ANALOGAPP, AnalogServiceUnit_ReadAdc_InvalidChannel_ReturnsInvalidParam)
{
    uint16_t rawValue = 0;
    AnalogService_Status_t status = call_AnalogServiceUnit_ReadAdc(8, &rawValue);
    EXPECT_EQ(ANALOGSERVICE_STATUS_INVALID_PARAM, status);
}

TEST_F(ANALOGAPP, AnalogServiceUnit_ReadAdc_NullPointer_ReturnsInvalidParam)
{
    AnalogService_Status_t status = call_AnalogServiceUnit_ReadAdc(0, nullptr);
    EXPECT_EQ(ANALOGSERVICE_STATUS_INVALID_PARAM, status);
}

TEST_F(ANALOGAPP, AnalogServiceUnit_ReadAdc_NotInitialized_ReturnsNotInitialized)
{
    call_AnalogServiceUnit_DeInit();
    uint16_t rawValue = 0;
    AnalogService_Status_t status = call_AnalogServiceUnit_ReadAdc(0, &rawValue);
    EXPECT_EQ(ANALOGSERVICE_STATUS_NOT_INITIALIZED, status);
}

TEST_F(ANALOGAPP, AnalogServiceUnit_ReadAdc_AllChannels_ReturnsOK)
{
    for (uint8_t ch = 0; ch < 8; ch++)
    {
        uint16_t rawValue = 0;
        AnalogService_Status_t status = call_AnalogServiceUnit_ReadAdc(ch, &rawValue);
        EXPECT_EQ(ANALOGSERVICE_STATUS_OK, status);
    }
}