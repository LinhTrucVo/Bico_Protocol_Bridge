//----------------------------------------------------------------------------
// Unit Test file for Central App Controller - UDS Dispatcher
//----------------------------------------------------------------------------

#include "gtest/gtest.h"
#include "gmock/gmock.h"

extern "C"
{
#include "mockCentralAppController.h"
}

//------------------------------------------------------------------------------
// Test Fixture Class
//------------------------------------------------------------------------------
class CentralAppController : public ::testing::Test 
{
protected:
    uint8_t responseBuffer[256];
    uint16_t responseLength;

    void SetUp() override 
    {
        FFF_RESET_HISTORY();
        call_CentralAppControllerUnit_Init();
        memset(responseBuffer, 0, sizeof(responseBuffer));
        responseLength = 0;
    }

    void TearDown() override 
    {
        call_CentralAppControllerUnit_DeInit();
    }
};

//------------------------------------------------------------------------------
// Test Cases for Init / DeInit
//------------------------------------------------------------------------------
TEST_F(CentralAppController, CentralAppController_Init_Valid_ReturnsOK)
{
    call_CentralAppControllerUnit_DeInit();
    CentralAppController_Status_t status = call_CentralAppControllerUnit_Init();
    EXPECT_EQ(CENTRAL_APP_CONTROLLER_STATUS_OK, status);
}

TEST_F(CentralAppController, CentralAppController_GetState_AfterInit_ReturnsIdle)
{
    CentralAppController_State_t state;
    call_CentralAppControllerUnit_GetState(&state);
    EXPECT_EQ(CentralAppController_STATE_IDLE, state);
}

//------------------------------------------------------------------------------
// Test Cases for Dispatch - SID 0x22 ReadDataByIdentifier
//------------------------------------------------------------------------------
TEST_F(CentralAppController, CentralAppController_Dispatch_SID22_DID1001_ReturnsPositiveResponse)
{
    // Arrange - Read ADC sample rate
    uint8_t frame[] = {0x22, 0x10, 0x01};

    // Act
    CentralAppController_Status_t status = call_CentralAppControllerUnit_Dispatch(
        frame, sizeof(frame), responseBuffer, sizeof(responseBuffer), &responseLength);

    // Assert
    EXPECT_EQ(CENTRAL_APP_CONTROLLER_STATUS_OK, status);
    EXPECT_GT(responseLength, 0U);
    EXPECT_EQ(0x62U, responseBuffer[0]); // Positive response SID
    EXPECT_EQ(0x10U, responseBuffer[1]); // DID high
    EXPECT_EQ(0x01U, responseBuffer[2]); // DID low
}

TEST_F(CentralAppController, CentralAppController_Dispatch_SID22_UnknownDID_ReturnsNegativeResponse)
{
    // Arrange - Unknown DID
    uint8_t frame[] = {0x22, 0xFF, 0xFF};

    // Act
    CentralAppController_Status_t status = call_CentralAppControllerUnit_Dispatch(
        frame, sizeof(frame), responseBuffer, sizeof(responseBuffer), &responseLength);

    // Assert
    EXPECT_EQ(CENTRAL_APP_CONTROLLER_STATUS_OK, status);
    EXPECT_EQ(3U, responseLength);
    EXPECT_EQ(0x7FU, responseBuffer[0]); // Negative response
    EXPECT_EQ(0x22U, responseBuffer[1]); // Request SID
    EXPECT_EQ(0x31U, responseBuffer[2]); // NRC: requestOutOfRange
}

//------------------------------------------------------------------------------
// Test Cases for Dispatch - SID 0x2E WriteDataByIdentifier
//------------------------------------------------------------------------------
TEST_F(CentralAppController, CentralAppController_Dispatch_SID2E_DID1001_ReturnsPositiveResponse)
{
    // Arrange - Write ADC sample rate = 2000 (0x07D0)
    uint8_t frame[] = {0x2E, 0x10, 0x01, 0x07, 0xD0};

    // Act
    CentralAppController_Status_t status = call_CentralAppControllerUnit_Dispatch(
        frame, sizeof(frame), responseBuffer, sizeof(responseBuffer), &responseLength);

    // Assert
    EXPECT_EQ(CENTRAL_APP_CONTROLLER_STATUS_OK, status);
    EXPECT_EQ(3U, responseLength);
    EXPECT_EQ(0x6EU, responseBuffer[0]); // Positive response SID
    EXPECT_EQ(0x10U, responseBuffer[1]);
    EXPECT_EQ(0x01U, responseBuffer[2]);
}

TEST_F(CentralAppController, CentralAppController_Dispatch_SID2E_InsufficientPayload_ReturnsNegative)
{
    // Arrange - DID 0x1001 needs 2 bytes payload, provide only DID
    uint8_t frame[] = {0x2E, 0x10, 0x01};

    // Act
    CentralAppController_Status_t status = call_CentralAppControllerUnit_Dispatch(
        frame, sizeof(frame), responseBuffer, sizeof(responseBuffer), &responseLength);

    // Assert - Should get incorrectMessageLength since SID 0x2E needs >=4 bytes
    EXPECT_EQ(CENTRAL_APP_CONTROLLER_STATUS_OK, status);
    EXPECT_EQ(0x7FU, responseBuffer[0]);
}

//------------------------------------------------------------------------------
// Test Cases for Dispatch - SID 0x31 RoutineControl
//------------------------------------------------------------------------------
TEST_F(CentralAppController, CentralAppController_Dispatch_SID31_ADCRead_ReturnsRoutineResponse)
{
    // Arrange - RID 0x0100 (ADC Read), params=[channel=0]
    uint8_t frame[] = {0x31, 0x01, 0x01, 0x00, 0x00};

    // Act
    CentralAppController_Status_t status = call_CentralAppControllerUnit_Dispatch(
        frame, sizeof(frame), responseBuffer, sizeof(responseBuffer), &responseLength);

    // Assert
    EXPECT_EQ(CENTRAL_APP_CONTROLLER_STATUS_OK, status);
    EXPECT_EQ(0x71U, responseBuffer[0]); // Positive routine response
    EXPECT_EQ(0x01U, responseBuffer[1]); // routineControlType
    EXPECT_EQ(0x01U, responseBuffer[2]); // RID high
    EXPECT_EQ(0x00U, responseBuffer[3]); // RID low
}

TEST_F(CentralAppController, CentralAppController_Dispatch_SID31_GPIOWrite_ReturnsOK)
{
    // Arrange - RID 0x0200 (GPIO Write), params=[pin=5, state=1]
    uint8_t frame[] = {0x31, 0x01, 0x02, 0x00, 0x05, 0x01};

    // Act
    CentralAppController_Status_t status = call_CentralAppControllerUnit_Dispatch(
        frame, sizeof(frame), responseBuffer, sizeof(responseBuffer), &responseLength);

    // Assert
    EXPECT_EQ(CENTRAL_APP_CONTROLLER_STATUS_OK, status);
    EXPECT_EQ(0x71U, responseBuffer[0]);
}

TEST_F(CentralAppController, CentralAppController_Dispatch_SID31_GPIORead_ReturnsOK)
{
    // Arrange - RID 0x0201 (GPIO Read), params=[pin=3]
    uint8_t frame[] = {0x31, 0x01, 0x02, 0x01, 0x03};

    // Act
    CentralAppController_Status_t status = call_CentralAppControllerUnit_Dispatch(
        frame, sizeof(frame), responseBuffer, sizeof(responseBuffer), &responseLength);

    // Assert
    EXPECT_EQ(CENTRAL_APP_CONTROLLER_STATUS_OK, status);
    EXPECT_EQ(0x71U, responseBuffer[0]);
}

TEST_F(CentralAppController, CentralAppController_Dispatch_SID31_UnknownRID_ReturnsNegative)
{
    // Arrange - Unknown RID
    uint8_t frame[] = {0x31, 0x01, 0xFF, 0xFF, 0x00};

    // Act
    CentralAppController_Status_t status = call_CentralAppControllerUnit_Dispatch(
        frame, sizeof(frame), responseBuffer, sizeof(responseBuffer), &responseLength);

    // Assert
    EXPECT_EQ(CENTRAL_APP_CONTROLLER_STATUS_OK, status);
    EXPECT_EQ(0x7FU, responseBuffer[0]);
    EXPECT_EQ(0x31U, responseBuffer[1]); // Request SID
    EXPECT_EQ(0x31U, responseBuffer[2]); // NRC: requestOutOfRange
}

//------------------------------------------------------------------------------
// Test Cases for error conditions
//------------------------------------------------------------------------------
TEST_F(CentralAppController, CentralAppController_Dispatch_UnsupportedSID_ReturnsNegative)
{
    // Arrange
    uint8_t frame[] = {0x99, 0x10, 0x01};

    // Act
    CentralAppController_Status_t status = call_CentralAppControllerUnit_Dispatch(
        frame, sizeof(frame), responseBuffer, sizeof(responseBuffer), &responseLength);

    // Assert
    EXPECT_EQ(CENTRAL_APP_CONTROLLER_STATUS_OK, status);
    EXPECT_EQ(0x7FU, responseBuffer[0]);
    EXPECT_EQ(0x99U, responseBuffer[1]);
    EXPECT_EQ(0x11U, responseBuffer[2]); // NRC: serviceNotSupported
}

TEST_F(CentralAppController, CentralAppController_Dispatch_NullInput_ReturnsInvalidParam)
{
    CentralAppController_Status_t status = call_CentralAppControllerUnit_Dispatch(
        nullptr, 3, responseBuffer, sizeof(responseBuffer), &responseLength);
    EXPECT_EQ(CENTRAL_APP_CONTROLLER_STATUS_INVALID_PARAM, status);
}

TEST_F(CentralAppController, CentralAppController_Dispatch_NotInitialized_ReturnsNotInitialized)
{
    call_CentralAppControllerUnit_DeInit();
    uint8_t frame[] = {0x22, 0x10, 0x01};
    CentralAppController_Status_t status = call_CentralAppControllerUnit_Dispatch(
        frame, sizeof(frame), responseBuffer, sizeof(responseBuffer), &responseLength);
    EXPECT_EQ(CENTRAL_APP_CONTROLLER_STATUS_NOT_INITIALIZED, status);
}

TEST_F(CentralAppController, CentralAppController_Dispatch_FrameTooShort_ReturnsNegative)
{
    // Arrange - only 2 bytes, below minimum frame size
    uint8_t frame[] = {0x22, 0x10};

    // Act
    CentralAppController_Status_t status = call_CentralAppControllerUnit_Dispatch(
        frame, sizeof(frame), responseBuffer, sizeof(responseBuffer), &responseLength);

    // Assert
    EXPECT_EQ(CENTRAL_APP_CONTROLLER_STATUS_OK, status);
    EXPECT_EQ(0x7FU, responseBuffer[0]);
    EXPECT_EQ(0x13U, responseBuffer[2]); // NRC: incorrectMessageLength
}