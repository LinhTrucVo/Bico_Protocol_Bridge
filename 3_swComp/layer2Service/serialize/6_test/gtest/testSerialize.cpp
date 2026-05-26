//----------------------------------------------------------------------------
// Unit Test file for Serialize component - UDS Response Builder
//----------------------------------------------------------------------------

#include "gtest/gtest.h"
#include "gmock/gmock.h"

extern "C"
{
#include "mockSerialize.h"
}

//------------------------------------------------------------------------------
// Test Fixture Class
//------------------------------------------------------------------------------
class Serialize : public ::testing::Test 
{
protected:
    void SetUp() override 
    {
        FFF_RESET_HISTORY();
        call_SerializeUnit_Init();
    }

    void TearDown() override 
    {
        call_SerializeUnit_DeInit();
    }
};

//------------------------------------------------------------------------------
// Test Cases for SerializeUnit_Init / DeInit
//------------------------------------------------------------------------------
TEST_F(Serialize, Serialize_Init_Valid_ReturnsOK)
{
    call_SerializeUnit_DeInit();
    Serialize_Status_t status = call_SerializeUnit_Init();
    EXPECT_EQ(SERIALIZE_STATUS_OK, status);
}

TEST_F(Serialize, Serialize_DeInit_Valid_ReturnsOK)
{
    Serialize_Status_t status = call_SerializeUnit_DeInit();
    EXPECT_EQ(SERIALIZE_STATUS_OK, status);
}

//------------------------------------------------------------------------------
// Test Cases for BuildReadResponse (SID 0x22 -> 0x62)
//------------------------------------------------------------------------------
TEST_F(Serialize, Serialize_BuildReadResponse_Valid_ReturnsOK)
{
    // Arrange
    uint8_t data[] = {0x03, 0xE8};
    Serialize_UdsResponse_t resp = {0};

    // Act
    Serialize_Status_t status = call_SerializeUnit_BuildReadResponse(0x1001, data, 2, &resp);

    // Assert
    EXPECT_EQ(SERIALIZE_STATUS_OK, status);
    EXPECT_EQ(5U, resp.length); // 0x62 + DID(2) + data(2)
    EXPECT_EQ(0x62U, resp.buffer[0]);
    EXPECT_EQ(0x10U, resp.buffer[1]);
    EXPECT_EQ(0x01U, resp.buffer[2]);
    EXPECT_EQ(0x03U, resp.buffer[3]);
    EXPECT_EQ(0xE8U, resp.buffer[4]);
}

TEST_F(Serialize, Serialize_BuildReadResponse_NullResponse_ReturnsInvalidParam)
{
    uint8_t data[] = {0x01};
    Serialize_Status_t status = call_SerializeUnit_BuildReadResponse(0x1001, data, 1, nullptr);
    EXPECT_EQ(SERIALIZE_STATUS_INVALID_PARAM, status);
}

TEST_F(Serialize, Serialize_BuildReadResponse_NotInitialized_ReturnsError)
{
    call_SerializeUnit_DeInit();
    uint8_t data[] = {0x01};
    Serialize_UdsResponse_t resp = {0};
    Serialize_Status_t status = call_SerializeUnit_BuildReadResponse(0x1001, data, 1, &resp);
    EXPECT_EQ(SERIALIZE_STATUS_ERROR, status);
}

//------------------------------------------------------------------------------
// Test Cases for BuildWriteResponse (SID 0x2E -> 0x6E)
//------------------------------------------------------------------------------
TEST_F(Serialize, Serialize_BuildWriteResponse_Valid_ReturnsOK)
{
    // Arrange
    Serialize_UdsResponse_t resp = {0};

    // Act
    Serialize_Status_t status = call_SerializeUnit_BuildWriteResponse(0x1001, &resp);

    // Assert
    EXPECT_EQ(SERIALIZE_STATUS_OK, status);
    EXPECT_EQ(3U, resp.length); // 0x6E + DID(2)
    EXPECT_EQ(0x6EU, resp.buffer[0]);
    EXPECT_EQ(0x10U, resp.buffer[1]);
    EXPECT_EQ(0x01U, resp.buffer[2]);
}

TEST_F(Serialize, Serialize_BuildWriteResponse_NullResponse_ReturnsInvalidParam)
{
    Serialize_Status_t status = call_SerializeUnit_BuildWriteResponse(0x1001, nullptr);
    EXPECT_EQ(SERIALIZE_STATUS_INVALID_PARAM, status);
}

//------------------------------------------------------------------------------
// Test Cases for BuildRoutineResponse (SID 0x31 -> 0x71)
//------------------------------------------------------------------------------
TEST_F(Serialize, Serialize_BuildRoutineResponse_Valid_ReturnsOK)
{
    // Arrange
    uint8_t statusRec[] = {0x08, 0x00};
    Serialize_UdsResponse_t resp = {0};

    // Act
    Serialize_Status_t status = call_SerializeUnit_BuildRoutineResponse(0x01, 0x0100, statusRec, 2, &resp);

    // Assert
    EXPECT_EQ(SERIALIZE_STATUS_OK, status);
    EXPECT_EQ(6U, resp.length); // 0x71 + type(1) + RID(2) + status(2)
    EXPECT_EQ(0x71U, resp.buffer[0]);
    EXPECT_EQ(0x01U, resp.buffer[1]); // routineControlType
    EXPECT_EQ(0x01U, resp.buffer[2]); // RID high
    EXPECT_EQ(0x00U, resp.buffer[3]); // RID low
    EXPECT_EQ(0x08U, resp.buffer[4]);
    EXPECT_EQ(0x00U, resp.buffer[5]);
}

TEST_F(Serialize, Serialize_BuildRoutineResponse_NoStatus_ReturnsOK)
{
    Serialize_UdsResponse_t resp = {0};
    Serialize_Status_t status = call_SerializeUnit_BuildRoutineResponse(0x01, 0x0200, nullptr, 0, &resp);
    EXPECT_EQ(SERIALIZE_STATUS_OK, status);
    EXPECT_EQ(4U, resp.length);
}

//------------------------------------------------------------------------------
// Test Cases for BuildNegativeResponse (0x7F)
//------------------------------------------------------------------------------
TEST_F(Serialize, Serialize_BuildNegativeResponse_Valid_ReturnsOK)
{
    // Arrange
    Serialize_UdsResponse_t resp = {0};

    // Act
    Serialize_Status_t status = call_SerializeUnit_BuildNegativeResponse(0x22, 0x31, &resp);

    // Assert
    EXPECT_EQ(SERIALIZE_STATUS_OK, status);
    EXPECT_EQ(3U, resp.length);
    EXPECT_EQ(0x7FU, resp.buffer[0]);
    EXPECT_EQ(0x22U, resp.buffer[1]); // requestSID
    EXPECT_EQ(0x31U, resp.buffer[2]); // NRC
}

TEST_F(Serialize, Serialize_BuildNegativeResponse_NullResponse_ReturnsInvalidParam)
{
    Serialize_Status_t status = call_SerializeUnit_BuildNegativeResponse(0x22, 0x31, nullptr);
    EXPECT_EQ(SERIALIZE_STATUS_INVALID_PARAM, status);
}