//----------------------------------------------------------------------------
// Unit Test file for Central App Controller component
//----------------------------------------------------------------------------

#include "gtest/gtest.h"
#include "gmock/gmock.h"

// Unit under test
extern "C"
{
#include "mockCentralAppController.h"
#include "deserialize.h"
}

//------------------------------------------------------------------------------
// Test Fixture Class
//------------------------------------------------------------------------------
class CentralAppController : public ::testing::Test 
{
protected:
    void SetUp() override 
    {
        // Reset all fake functions before each test
        FFF_RESET_HISTORY();
    }

    void TearDown() override 
    {
        // Clean up after each test if needed
    }
};

//------------------------------------------------------------------------------
// Test Cases for CentralAppControllerUnit_Init
//------------------------------------------------------------------------------
TEST_F(CentralAppController, CentralAppController_Init_Valid_ReturnsOK)
{
    // Arrange
    
    // Act
    CentralAppController_Status_t status = call_CentralAppControllerUnit_Init();
    
    // Assert
    EXPECT_EQ(CENTRAL_APP_CONTROLLER_STATUS_OK, status);
}

//------------------------------------------------------------------------------
// Test Cases for CentralAppControllerUnit_ProcessFrame
//------------------------------------------------------------------------------
TEST_F(CentralAppController, CentralAppController_ProcessFrame_ValidFrame_ReturnsOK)
{
    // Arrange
    uint8_t inFrame[8] = {0};
    uint8_t outFrame[64] = {0};
    uint16_t outLen = 0;
    CentralAppController_Frame_t in = { inFrame, 7 };
    CentralAppController_OutFrame_t out = { outFrame, sizeof(outFrame) };
    uint16_t crc = 0;

    inFrame[0] = 0x02; // ADC_READ
    inFrame[1] = 0x01; // seq
    inFrame[2] = 0x00;
    inFrame[3] = 0x00;
    inFrame[4] = 0x00;
    Deserialize_Init();
    Deserialize_ComputeCrc(inFrame, 5, &crc);
    inFrame[5] = (uint8_t)(crc & 0xFFU);
    inFrame[6] = (uint8_t)((crc >> 8U) & 0xFFU);

    call_CentralAppControllerUnit_Init();
    
    // Act
    CentralAppController_Status_t status = call_CentralAppControllerUnit_ProcessFrame(&in, &out, &outLen);
    
    // Assert
    EXPECT_EQ(CENTRAL_APP_CONTROLLER_STATUS_OK, status);
    EXPECT_GT(outLen, 0U);
}

//------------------------------------------------------------------------------
// Test Cases for CentralAppControllerUnit_GetState
//------------------------------------------------------------------------------
TEST_F(CentralAppController, CentralAppController_GetState_AfterInit_ReturnsIdleState)
{
    // Arrange
    CentralAppController_State_t state;
    call_CentralAppControllerUnit_Init();
    
    // Act
    CentralAppController_Status_t status = call_CentralAppControllerUnit_GetState(&state);
    
    // Assert
    EXPECT_EQ(CENTRAL_APP_CONTROLLER_STATUS_OK, status);
    EXPECT_EQ(CentralAppController_STATE_IDLE, state);
}
