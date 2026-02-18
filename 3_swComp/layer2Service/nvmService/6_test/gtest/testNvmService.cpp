//----------------------------------------------------------------------------
// Unit Test file for NvmService component
//----------------------------------------------------------------------------

#include "gtest/gtest.h"
#include "gmock/gmock.h"

// Unit under test
extern "C"
{
#include "mockNvmService.h"
}

//------------------------------------------------------------------------------
// Test Fixture Class
//------------------------------------------------------------------------------
class NvmService : public ::testing::Test 
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
// Test Cases for NvmServiceUnit_Init
//------------------------------------------------------------------------------
TEST_F(NvmService, NvmService_Init_Valid_ReturnsOK)
{
    // Arrange
    // No setup needed
    
    // Act
    NvmService_Status_t status = call_NvmServiceUnit_Init();
    
    // Assert
    EXPECT_EQ(NVM_SERVICE_STATUS_OK, status);
}

//------------------------------------------------------------------------------
// Test Cases for NvmServiceUnit_Save
//------------------------------------------------------------------------------
TEST_F(NvmService, NvmService_Save_ValidBlob_ReturnsOK)
{
    // Arrange
    uint8_t data[2] = {0x11, 0x22};
    NvmService_Blob_t blob = { NVM_SERVICE_KEY_SYSTEM_CONFIG, 2, data };
    call_NvmServiceUnit_Init();
    
    // Act
    NvmService_Status_t status = call_NvmServiceUnit_Save(&blob);
    
    // Assert
    EXPECT_EQ(NVM_SERVICE_STATUS_OK, status);
}

//------------------------------------------------------------------------------
// Test Cases for NvmServiceUnit_Load
//------------------------------------------------------------------------------
TEST_F(NvmService, NvmService_Load_ValidKey_ReturnsOK)
{
    // Arrange
    uint8_t data[2] = {0x11, 0x22};
    uint8_t out[4] = {0};
    uint16_t outLen = 0;
    NvmService_Blob_t blob = { NVM_SERVICE_KEY_SYSTEM_CONFIG, 2, data };
    call_NvmServiceUnit_Init();
    call_NvmServiceUnit_Save(&blob);
    
    // Act
    NvmService_Status_t status = call_NvmServiceUnit_Load(NVM_SERVICE_KEY_SYSTEM_CONFIG, out, sizeof(out), &outLen);
    
    // Assert
    EXPECT_EQ(NVM_SERVICE_STATUS_OK, status);
    EXPECT_EQ(outLen, 2);
}

//------------------------------------------------------------------------------
// Test Cases for NvmServiceUnit_Erase
//------------------------------------------------------------------------------
TEST_F(NvmService, NvmService_Erase_ValidKey_ReturnsOK)
{
    // Arrange
    call_NvmServiceUnit_Init();
    
    // Act
    NvmService_Status_t status = call_NvmServiceUnit_Erase(NVM_SERVICE_KEY_SYSTEM_CONFIG);
    
    // Assert
    EXPECT_EQ(NVM_SERVICE_STATUS_OK, status);
}

//------------------------------------------------------------------------------
// Test Cases for NvmServiceUnit_Exists
//------------------------------------------------------------------------------
TEST_F(NvmService, NvmService_Exists_ValidKey_ReturnsOK)
{
    // Arrange
    bool exists = false;
    call_NvmServiceUnit_Init();
    
    // Act
    NvmService_Status_t status = call_NvmServiceUnit_Exists(NVM_SERVICE_KEY_SYSTEM_CONFIG, &exists);
    
    // Assert
    EXPECT_EQ(NVM_SERVICE_STATUS_OK, status);
}

//------------------------------------------------------------------------------
// Test Cases for NvmServiceUnit_ComputeCrc
//------------------------------------------------------------------------------
TEST_F(NvmService, NvmService_ComputeCrc_ValidData_ReturnsOK)
{
    // Arrange
    uint8_t data[2] = {0x11, 0x22};
    uint32_t crc = 0;
    call_NvmServiceUnit_Init();
    
    // Act
    NvmService_Status_t status = call_NvmServiceUnit_ComputeCrc(data, 2, &crc);
    
    // Assert
    EXPECT_EQ(NVM_SERVICE_STATUS_OK, status);
}

//------------------------------------------------------------------------------
// Test Cases for NvmServiceUnit_DeInit
//------------------------------------------------------------------------------
TEST_F(NvmService, NvmService_DeInit_Valid_ReturnsOK)
{
    // Arrange
    call_NvmServiceUnit_Init();
    
    // Act
    NvmService_Status_t status = call_NvmServiceUnit_DeInit();
    
    // Assert
    EXPECT_EQ(NVM_SERVICE_STATUS_OK, status);
}
