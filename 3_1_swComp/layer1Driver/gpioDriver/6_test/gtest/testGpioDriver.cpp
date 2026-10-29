//----------------------------------------------------------------------------
// Unit Test file for GPIO Driver component
//----------------------------------------------------------------------------

#include "gtest/gtest.h"
#include "gmock/gmock.h"

// Unit under test
extern "C"
{
#include "mockGpioDriver.h"
}

//------------------------------------------------------------------------------
// Test Fixture Class
//------------------------------------------------------------------------------
class GpioDriver : public ::testing::Test 
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
// Test Cases for GpioDriverUnit_Init
//------------------------------------------------------------------------------
TEST_F(GpioDriver, GpioDriver_Init_ValidConfig_ReturnsOK)
{
    // Arrange
    GpioDriver_Config_t config = {false, false};
    
    // Act
    GpioDriver_Status_t status = call_GpioDriverUnit_Init(&config);
    
    // Assert
    EXPECT_EQ(BPB_GPIO_STATUS_OK, status);
}

//------------------------------------------------------------------------------
// Test Cases for GpioDriverUnit_ConfigurePin
//------------------------------------------------------------------------------
TEST_F(GpioDriver, GpioDriver_ConfigurePin_ValidPin_ReturnsOK)
{
    // Arrange
    GpioDriver_PinConfig_t config = {
        BPB_GPIO_MODE_OUTPUT,
        BPB_GPIO_PULL_NONE,
        BPB_GPIO_SPEED_HIGH,
        BPB_GPIO_STATE_LOW
    };
    
    // Act
    GpioDriver_Status_t status = call_GpioDriverUnit_ConfigurePin(0, &config);
    
    // Assert
    EXPECT_EQ(BPB_GPIO_STATUS_OK, status);
}

//------------------------------------------------------------------------------
// Test Cases for GpioDriverUnit_WritePin
//------------------------------------------------------------------------------
TEST_F(GpioDriver, GpioDriver_WritePin_ValidPin_ReturnsOK)
{
    // Arrange
    GpioDriver_PinConfig_t config = {
        BPB_GPIO_MODE_OUTPUT,
        BPB_GPIO_PULL_NONE,
        BPB_GPIO_SPEED_HIGH,
        BPB_GPIO_STATE_LOW
    };
    call_GpioDriverUnit_ConfigurePin(0, &config);
    
    // Act
    GpioDriver_Status_t status = call_GpioDriverUnit_WritePin(0, BPB_GPIO_STATE_HIGH);
    
    // Assert
    EXPECT_EQ(BPB_GPIO_STATUS_OK, status);
}

//------------------------------------------------------------------------------
// Test Cases for GpioDriverUnit_ReadPin
//------------------------------------------------------------------------------
TEST_F(GpioDriver, GpioDriver_ReadPin_ValidPin_ReturnsOK)
{
    // Arrange
    GpioDriver_State_t state = BPB_GPIO_STATE_LOW;
    
    // Act
    GpioDriver_Status_t status = call_GpioDriverUnit_ReadPin(0, &state);
    
    // Assert
    EXPECT_EQ(BPB_GPIO_STATUS_OK, status);
}

//------------------------------------------------------------------------------
// Test Cases for GpioDriverUnit_SetIOCapability
//------------------------------------------------------------------------------
TEST_F(GpioDriver, GpioDriver_SetIOCapability_ValidPin_ReturnsOK)
{
    // Arrange
    GpioDriver_Config_t config = {false, false};
    call_GpioDriverUnit_Init(&config);
    
    // Act
    GpioDriver_Status_t status = call_GpioDriverUnit_SetIOCapability(0, BPB_GPIO_IO_DRIVE_CAP_LV4);
    
    // Assert
    EXPECT_EQ(BPB_GPIO_STATUS_OK, status);
}

TEST_F(GpioDriver, GpioDriver_SetIOCapability_InvalidPin_ReturnsInvalid)
{
    // Arrange
    GpioDriver_Config_t config = {false, false};
    call_GpioDriverUnit_Init(&config);
    
    // Act
    GpioDriver_Status_t status = call_GpioDriverUnit_SetIOCapability(BPB_GPIO_MAX_PINS, BPB_GPIO_IO_DRIVE_CAP_LV4);
    
    // Assert
    EXPECT_EQ(BPB_GPIO_STATUS_INVALID_PIN, status);
}

TEST_F(GpioDriver, GpioDriver_SetIOCapability_NotInitialized_ReturnsNotInit)
{
    // Arrange
    // No Init call
    
    // Act
    GpioDriver_Status_t status = call_GpioDriverUnit_SetIOCapability(0, BPB_GPIO_IO_DRIVE_CAP_LV7);
    
    // Assert
    EXPECT_EQ(BPB_GPIO_STATUS_NOT_INITIALIZED, status);
}

//------------------------------------------------------------------------------
// Test Cases for GpioDriverUnit_DeInit
//------------------------------------------------------------------------------
TEST_F(GpioDriver, GpioDriver_DeInit_ValidState_ReturnsOK)
{
    // Arrange
    // ... setup code ...
    
    // Act
    GpioDriver_Status_t status = call_GpioDriverUnit_DeInit();
    
    // Assert
    EXPECT_EQ(BPB_GPIO_STATUS_OK, status);
}
