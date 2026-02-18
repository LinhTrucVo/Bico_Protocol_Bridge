//----------------------------------------------------------------------------
// Unit Test file for Deserialize component
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
        // Reset all fake functions before each test
        FFF_RESET_HISTORY();
    }

    void TearDown() override 
    {
        // Clean up after each test if needed
    }
};

//------------------------------------------------------------------------------
// Test Cases for DeserializeUnit_Init
//------------------------------------------------------------------------------
TEST_F(Deserialize, Deserialize_Init_Valid_ReturnsOK)
{
    // Arrange
    // No setup needed
    
    // Act
    Deserialize_Status_t status = call_DeserializeUnit_Init();
    
    // Assert
    EXPECT_EQ(DESERIALIZE_STATUS_OK, status);
}

//------------------------------------------------------------------------------
// Test Cases for DeserializeUnit_ComputeCrc
//------------------------------------------------------------------------------
TEST_F(Deserialize, Deserialize_ComputeCrc_ValidFrame_ReturnsOK)
{
    // Arrange
    uint8_t frame[5] = {0x02, 0x01, 0x00, 0x00, 0x00};
    uint16_t crc = 0;
    call_DeserializeUnit_Init();
    
    // Act
    Deserialize_Status_t status = call_DeserializeUnit_ComputeCrc(frame, 5, &crc);
    
    // Assert
    EXPECT_EQ(DESERIALIZE_STATUS_OK, status);
}

//------------------------------------------------------------------------------
// Test Cases for DeserializeUnit_ParseFrame
//------------------------------------------------------------------------------
TEST_F(Deserialize, Deserialize_ParseFrame_ValidFrame_ReturnsOK)
{
    // Arrange
    uint8_t frame[16] = {0};
    frame[0] = 0x02; // ADC_READ
    frame[1] = 0x01; // seq
    frame[2] = 0x00; // type
    frame[3] = 0x00; // payload length LSB
    frame[4] = 0x00; // payload length MSB
    uint16_t crc = 0;
    Deserialize_Frame_t f = { frame, 7 };
    Deserialize_Request_t req = {0};
    call_DeserializeUnit_Init();
    call_DeserializeUnit_ComputeCrc(frame, 5, &crc);
    frame[5] = (uint8_t)(crc & 0xFFU);
    frame[6] = (uint8_t)((crc >> 8U) & 0xFFU);
    
    // Act
    Deserialize_Status_t status = call_DeserializeUnit_ParseFrame(&f, &req);
    
    // Assert
    EXPECT_EQ(DESERIALIZE_STATUS_OK, status);
}

//------------------------------------------------------------------------------
// Test Cases for DeserializeUnit_ValidateFrame
//------------------------------------------------------------------------------
TEST_F(Deserialize, Deserialize_ValidateFrame_ValidFrame_ReturnsOK)
{
    // Arrange
    uint8_t frame[16] = {0};
    frame[0] = 0x02;
    frame[1] = 0x01;
    Deserialize_Frame_t f = { frame, 7 };
    call_DeserializeUnit_Init();
    
    // Act
    Deserialize_Status_t status = call_DeserializeUnit_ValidateFrame(&f);
    
    // Assert
    EXPECT_EQ(DESERIALIZE_STATUS_OK, status);
}

//------------------------------------------------------------------------------
// Test Cases for DeserializeUnit_DeInit
//------------------------------------------------------------------------------
TEST_F(Deserialize, Deserialize_DeInit_Valid_ReturnsOK)
{
    // Arrange
    call_DeserializeUnit_Init();
    
    // Act
    Deserialize_Status_t status = call_DeserializeUnit_DeInit();
    
    // Assert
    EXPECT_EQ(DESERIALIZE_STATUS_OK, status);
}
