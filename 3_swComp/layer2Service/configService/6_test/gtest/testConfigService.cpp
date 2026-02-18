//----------------------------------------------------------------------------
// Unit Test file for ConfigService component
//----------------------------------------------------------------------------

#include "gtest/gtest.h"
#include "gmock/gmock.h"

// Unit under test
extern "C"
{
#include "mockConfigService.h"
}

//------------------------------------------------------------------------------
// Test Fixture Class
//------------------------------------------------------------------------------
class ConfigService : public ::testing::Test 
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
// Test Cases for ConfigServiceUnit_Init
//------------------------------------------------------------------------------
TEST_F(ConfigService, ConfigService_Init_Valid_ReturnsOK)
{
    // Arrange
    // No setup needed
    
    // Act
    ConfigService_Status_t status = call_ConfigServiceUnit_Init();
    
    // Assert
    EXPECT_EQ(CONFIG_SERVICE_STATUS_OK, status);
}

//------------------------------------------------------------------------------
// Test Cases for ConfigServiceUnit_SetAnalogChannelConfig
//------------------------------------------------------------------------------
TEST_F(ConfigService, ConfigService_SetAnalogChannelConfig_ValidChannel_ReturnsOK)
{
    // Arrange
    ConfigService_AnalogChannelConfig_t cfg = {0, 12, 3.3f, 1000, 1, 1.0f, 0.0f, false};
    call_ConfigServiceUnit_Init();
    
    // Act
    ConfigService_Status_t status = call_ConfigServiceUnit_SetAnalogChannelConfig(0, &cfg);
    
    // Assert
    EXPECT_EQ(CONFIG_SERVICE_STATUS_OK, status);
}

//------------------------------------------------------------------------------
// Test Cases for ConfigServiceUnit_GetAnalogChannelConfig
//------------------------------------------------------------------------------
TEST_F(ConfigService, ConfigService_GetAnalogChannelConfig_ValidChannel_ReturnsOK)
{
    // Arrange
    ConfigService_AnalogChannelConfig_t cfg = {0, 12, 3.3f, 1000, 1, 1.0f, 0.0f, false};
    ConfigService_AnalogChannelConfig_t out = {0};
    call_ConfigServiceUnit_Init();
    call_ConfigServiceUnit_SetAnalogChannelConfig(0, &cfg);
    
    // Act
    ConfigService_Status_t status = call_ConfigServiceUnit_GetAnalogChannelConfig(0, &out);
    
    // Assert
    EXPECT_EQ(CONFIG_SERVICE_STATUS_OK, status);
}

//------------------------------------------------------------------------------
// Test Cases for ConfigServiceUnit_DeInit
//------------------------------------------------------------------------------
TEST_F(ConfigService, ConfigService_DeInit_Valid_ReturnsOK)
{
    // Arrange
    call_ConfigServiceUnit_Init();
    
    // Act
    ConfigService_Status_t status = call_ConfigServiceUnit_DeInit();
    
    // Assert
    EXPECT_EQ(CONFIG_SERVICE_STATUS_OK, status);
}
