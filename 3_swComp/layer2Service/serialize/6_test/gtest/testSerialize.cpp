//----------------------------------------------------------------------------
// Unit Test file for Serialize component
//----------------------------------------------------------------------------

#include "gtest/gtest.h"
#include "gmock/gmock.h"

// Unit under test
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
        // Reset all fake functions before each test
        FFF_RESET_HISTORY();
    }

    void TearDown() override 
    {
        // Clean up after each test if needed
    }
};

//------------------------------------------------------------------------------
// Test Cases for SerializeUnit_Init
//------------------------------------------------------------------------------
TEST_F(Serialize, Serialize_Init_Valid_ReturnsOK)
{
    // Arrange
    // No setup needed
    
    // Act
    Serialize_Status_t status = call_SerializeUnit_Init();
    
    // Assert
    EXPECT_EQ(SERIALIZE_STATUS_OK, status);
}

//------------------------------------------------------------------------------
// Test Cases for SerializeUnit_BuildFrame
//------------------------------------------------------------------------------
TEST_F(Serialize, Serialize_BuildFrame_ValidMessage_ReturnsOK)
{
    // Arrange
    uint8_t payload[2] = {0x01, 0x02};
    uint8_t buffer[64] = {0};
    Serialize_Message_t msg = { {0x10, 0x01, SERIALIZE_MSG_TYPE_RESPONSE}, payload, 2 };
    Serialize_Buffer_t out = { buffer, sizeof(buffer) };
    uint16_t frameLen = 0;
    call_SerializeUnit_Init();
    
    // Act
    Serialize_Status_t status = call_SerializeUnit_BuildFrame(&msg, &out, &frameLen);
    
    // Assert
    EXPECT_EQ(SERIALIZE_STATUS_OK, status);
    EXPECT_GT(frameLen, 0U);
}

//------------------------------------------------------------------------------
// Test Cases for SerializeUnit_ComputeCrc
//------------------------------------------------------------------------------
TEST_F(Serialize, Serialize_ComputeCrc_ValidData_ReturnsOK)
{
    // Arrange
    uint8_t data[4] = {0x10, 0x01, 0x00, 0x00};
    uint16_t crc = 0;
    call_SerializeUnit_Init();
    
    // Act
    Serialize_Status_t status = call_SerializeUnit_ComputeCrc(data, 4, &crc);
    
    // Assert
    EXPECT_EQ(SERIALIZE_STATUS_OK, status);
}

//------------------------------------------------------------------------------
// Test Cases for SerializeUnit_BuildError
//------------------------------------------------------------------------------
TEST_F(Serialize, Serialize_BuildError_ValidError_ReturnsOK)
{
    // Arrange
    uint8_t buffer[64] = {0};
    Serialize_Buffer_t out = { buffer, sizeof(buffer) };
    uint16_t frameLen = 0;
    call_SerializeUnit_Init();
    
    // Act
    Serialize_Status_t status = call_SerializeUnit_BuildError(0x10, 0x01, SERIALIZE_ERROR_INVALID_COMMAND, &out, &frameLen);
    
    // Assert
    EXPECT_EQ(SERIALIZE_STATUS_OK, status);
    EXPECT_GT(frameLen, 0U);
}

//------------------------------------------------------------------------------
// Test Cases for SerializeUnit_BuildAnalogSamples
//------------------------------------------------------------------------------
TEST_F(Serialize, Serialize_BuildAnalogSamples_ValidSamples_ReturnsOK)
{
    // Arrange
    uint16_t samples[4] = {100, 200, 300, 400};
    uint8_t buffer[64] = {0};
    Serialize_Buffer_t out = { buffer, sizeof(buffer) };
    uint16_t frameLen = 0;
    call_SerializeUnit_Init();
    
    // Act
    Serialize_Status_t status = call_SerializeUnit_BuildAnalogSamples(0, samples, 4, &out, &frameLen);
    
    // Assert
    EXPECT_EQ(SERIALIZE_STATUS_OK, status);
    EXPECT_GT(frameLen, 0U);
}

//------------------------------------------------------------------------------
// Test Cases for SerializeUnit_BuildDigitalRead
//------------------------------------------------------------------------------
TEST_F(Serialize, Serialize_BuildDigitalRead_ValidPin_ReturnsOK)
{
    // Arrange
    uint8_t buffer[64] = {0};
    Serialize_Buffer_t out = { buffer, sizeof(buffer) };
    uint16_t frameLen = 0;
    call_SerializeUnit_Init();
    
    // Act
    Serialize_Status_t status = call_SerializeUnit_BuildDigitalRead(0, 1, &out, &frameLen);
    
    // Assert
    EXPECT_EQ(SERIALIZE_STATUS_OK, status);
    EXPECT_GT(frameLen, 0U);
}

//------------------------------------------------------------------------------
// Test Cases for SerializeUnit_BuildI2CRead
//------------------------------------------------------------------------------
TEST_F(Serialize, Serialize_BuildI2CRead_ValidData_ReturnsOK)
{
    // Arrange
    uint8_t data[4] = {0x01, 0x02, 0x03, 0x04};
    uint8_t buffer[64] = {0};
    Serialize_Buffer_t out = { buffer, sizeof(buffer) };
    uint16_t frameLen = 0;
    call_SerializeUnit_Init();
    
    // Act
    Serialize_Status_t status = call_SerializeUnit_BuildI2CRead(0x50, data, 4, &out, &frameLen);
    
    // Assert
    EXPECT_EQ(SERIALIZE_STATUS_OK, status);
    EXPECT_GT(frameLen, 0U);
}

//------------------------------------------------------------------------------
// Test Cases for SerializeUnit_BuildSPITransfer
//------------------------------------------------------------------------------
TEST_F(Serialize, Serialize_BuildSPITransfer_ValidData_ReturnsOK)
{
    // Arrange
    uint8_t txData[2] = {0xAA, 0xBB};
    uint8_t rxData[2] = {0x11, 0x22};
    uint8_t buffer[64] = {0};
    Serialize_Buffer_t out = { buffer, sizeof(buffer) };
    uint16_t frameLen = 0;
    call_SerializeUnit_Init();
    
    // Act
    Serialize_Status_t status = call_SerializeUnit_BuildSPITransfer(txData, rxData, 2, &out, &frameLen);
    
    // Assert
    EXPECT_EQ(SERIALIZE_STATUS_OK, status);
    EXPECT_GT(frameLen, 0U);
}

//------------------------------------------------------------------------------
// Test Cases for SerializeUnit_DeInit
//------------------------------------------------------------------------------
TEST_F(Serialize, Serialize_DeInit_Valid_ReturnsOK)
{
    // Arrange
    call_SerializeUnit_Init();
    
    // Act
    Serialize_Status_t status = call_SerializeUnit_DeInit();
    
    // Assert
    EXPECT_EQ(SERIALIZE_STATUS_OK, status);
}
