//----------------------------------------------------------------------------
// Unit Test file for Deserialize component - UDS Request Parser
//----------------------------------------------------------------------------

#include "gtest/gtest.h"
#include "gmock/gmock.h"

// Unit under test
extern "C"
{
#include "mockDeserialize.h"
}

//------------------------------------------------------------------------------
// Test Fixture Class
//------------------------------------------------------------------------------
class Deserialize : public ::testing::Test 
{
protected:
    void SetUp() override 
    {
        FFF_RESET_HISTORY();
        call_DeserializeUnit_Init();
    }

    void TearDown() override 
    {
        call_DeserializeUnit_DeInit();
    }
};

//------------------------------------------------------------------------------
// Test Cases for DeserializeUnit_Init / DeInit
//------------------------------------------------------------------------------
TEST_F(Deserialize, Deserialize_Init_Valid_ReturnsOK)
{
    // Arrange
    call_DeserializeUnit_DeInit();

    // Act
    Deserialize_Status_t status = call_DeserializeUnit_Init();

    // Assert
    EXPECT_EQ(DESERIALIZE_STATUS_OK, status);
}

TEST_F(Deserialize, Deserialize_DeInit_Valid_ReturnsOK)
{
    // Act
    Deserialize_Status_t status = call_DeserializeUnit_DeInit();

    // Assert
    EXPECT_EQ(DESERIALIZE_STATUS_OK, status);
}

//------------------------------------------------------------------------------
// Test Cases for DeserializeUnit_Parse - SID 0x22 ReadDataByIdentifier
//------------------------------------------------------------------------------
TEST_F(Deserialize, Deserialize_Parse_SID22_ValidFrame_ReturnsOK)
{
    // Arrange
    uint8_t frame[] = {0x22, 0x10, 0x01}; // SID=0x22, DID=0x1001
    Deserialize_Frame_t f = { frame, sizeof(frame) };
    Deserialize_UdsRequest_t req = {0};

    // Act
    Deserialize_Status_t status = call_DeserializeUnit_Parse(&f, &req);

    // Assert
    EXPECT_EQ(DESERIALIZE_STATUS_OK, status);
    EXPECT_EQ(0x22U, req.sid);
    EXPECT_EQ(0x1001U, req.id);
    EXPECT_EQ(nullptr, req.pPayload);
    EXPECT_EQ(0U, req.payloadLength);
}

TEST_F(Deserialize, Deserialize_Parse_SID22_DIDDecodesBigEndian)
{
    // Arrange
    uint8_t frame[] = {0x22, 0xAB, 0xCD};
    Deserialize_Frame_t f = { frame, sizeof(frame) };
    Deserialize_UdsRequest_t req = {0};

    // Act
    call_DeserializeUnit_Parse(&f, &req);

    // Assert
    EXPECT_EQ(0xABCDU, req.id);
}

TEST_F(Deserialize, Deserialize_Parse_SID22_TooShort_ReturnsInvalidFrame)
{
    // Arrange - only 2 bytes (need minimum 3)
    uint8_t frame[] = {0x22, 0x10};
    Deserialize_Frame_t f = { frame, sizeof(frame) };
    Deserialize_UdsRequest_t req = {0};

    // Act
    Deserialize_Status_t status = call_DeserializeUnit_Parse(&f, &req);

    // Assert
    EXPECT_EQ(DESERIALIZE_STATUS_INVALID_FRAME, status);
}

//------------------------------------------------------------------------------
// Test Cases for DeserializeUnit_Parse - SID 0x2E WriteDataByIdentifier
//------------------------------------------------------------------------------
TEST_F(Deserialize, Deserialize_Parse_SID2E_ValidFrame_ReturnsOK)
{
    // Arrange
    uint8_t frame[] = {0x2E, 0x10, 0x01, 0x07, 0xD0}; // SID=0x2E, DID=0x1001, data=[0x07,0xD0]
    Deserialize_Frame_t f = { frame, sizeof(frame) };
    Deserialize_UdsRequest_t req = {0};

    // Act
    Deserialize_Status_t status = call_DeserializeUnit_Parse(&f, &req);

    // Assert
    EXPECT_EQ(DESERIALIZE_STATUS_OK, status);
    EXPECT_EQ(0x2EU, req.sid);
    EXPECT_EQ(0x1001U, req.id);
    EXPECT_EQ(&frame[3], req.pPayload);
    EXPECT_EQ(2U, req.payloadLength);
}

TEST_F(Deserialize, Deserialize_Parse_SID2E_NoPayload_ReturnsInvalidFrame)
{
    // Arrange - SID + DID but no data (need minimum 4 bytes)
    uint8_t frame[] = {0x2E, 0x10, 0x01};
    Deserialize_Frame_t f = { frame, sizeof(frame) };
    Deserialize_UdsRequest_t req = {0};

    // Act
    Deserialize_Status_t status = call_DeserializeUnit_Parse(&f, &req);

    // Assert
    EXPECT_EQ(DESERIALIZE_STATUS_INVALID_FRAME, status);
}

//------------------------------------------------------------------------------
// Test Cases for DeserializeUnit_Parse - SID 0x31 RoutineControl
//------------------------------------------------------------------------------
TEST_F(Deserialize, Deserialize_Parse_SID31_ValidFrame_ReturnsOK)
{
    // Arrange
    uint8_t frame[] = {0x31, 0x01, 0x01, 0x00, 0x05}; // SID=0x31, type=start, RID=0x0100, params=[0x05]
    Deserialize_Frame_t f = { frame, sizeof(frame) };
    Deserialize_UdsRequest_t req = {0};

    // Act
    Deserialize_Status_t status = call_DeserializeUnit_Parse(&f, &req);

    // Assert
    EXPECT_EQ(DESERIALIZE_STATUS_OK, status);
    EXPECT_EQ(0x31U, req.sid);
    EXPECT_EQ(0x01U, req.routineControlType);
    EXPECT_EQ(0x0100U, req.id);
    EXPECT_EQ(&frame[4], req.pPayload);
    EXPECT_EQ(1U, req.payloadLength);
}

TEST_F(Deserialize, Deserialize_Parse_SID31_NoParams_ReturnsOK)
{
    // Arrange - minimum valid: SID + type + RID (4 bytes, no params)
    uint8_t frame[] = {0x31, 0x01, 0x02, 0x00};
    Deserialize_Frame_t f = { frame, sizeof(frame) };
    Deserialize_UdsRequest_t req = {0};

    // Act
    Deserialize_Status_t status = call_DeserializeUnit_Parse(&f, &req);

    // Assert
    EXPECT_EQ(DESERIALIZE_STATUS_OK, status);
    EXPECT_EQ(0x0200U, req.id);
    EXPECT_EQ(nullptr, req.pPayload);
    EXPECT_EQ(0U, req.payloadLength);
}

TEST_F(Deserialize, Deserialize_Parse_SID31_TooShort_ReturnsInvalidFrame)
{
    // Arrange - only 3 bytes (need minimum 4 for SID 0x31)
    uint8_t frame[] = {0x31, 0x01, 0x01};
    Deserialize_Frame_t f = { frame, sizeof(frame) };
    Deserialize_UdsRequest_t req = {0};

    // Act
    Deserialize_Status_t status = call_DeserializeUnit_Parse(&f, &req);

    // Assert
    EXPECT_EQ(DESERIALIZE_STATUS_INVALID_FRAME, status);
}

//------------------------------------------------------------------------------
// Test Cases for error conditions
//------------------------------------------------------------------------------
TEST_F(Deserialize, Deserialize_Parse_UnsupportedSID_ReturnsUnsupportedSID)
{
    // Arrange
    uint8_t frame[] = {0x99, 0x10, 0x01};
    Deserialize_Frame_t f = { frame, sizeof(frame) };
    Deserialize_UdsRequest_t req = {0};

    // Act
    Deserialize_Status_t status = call_DeserializeUnit_Parse(&f, &req);

    // Assert
    EXPECT_EQ(DESERIALIZE_STATUS_UNSUPPORTED_SID, status);
}

TEST_F(Deserialize, Deserialize_Parse_NullFrame_ReturnsInvalidParam)
{
    // Arrange
    Deserialize_UdsRequest_t req = {0};

    // Act
    Deserialize_Status_t status = call_DeserializeUnit_Parse(nullptr, &req);

    // Assert
    EXPECT_EQ(DESERIALIZE_STATUS_INVALID_PARAM, status);
}

TEST_F(Deserialize, Deserialize_Parse_NullRequest_ReturnsInvalidParam)
{
    // Arrange
    uint8_t frame[] = {0x22, 0x10, 0x01};
    Deserialize_Frame_t f = { frame, sizeof(frame) };

    // Act
    Deserialize_Status_t status = call_DeserializeUnit_Parse(&f, nullptr);

    // Assert
    EXPECT_EQ(DESERIALIZE_STATUS_INVALID_PARAM, status);
}

TEST_F(Deserialize, Deserialize_Parse_NotInitialized_ReturnsError)
{
    // Arrange
    call_DeserializeUnit_DeInit();
    uint8_t frame[] = {0x22, 0x10, 0x01};
    Deserialize_Frame_t f = { frame, sizeof(frame) };
    Deserialize_UdsRequest_t req = {0};

    // Act
    Deserialize_Status_t status = call_DeserializeUnit_Parse(&f, &req);

    // Assert
    EXPECT_EQ(DESERIALIZE_STATUS_ERROR, status);
}