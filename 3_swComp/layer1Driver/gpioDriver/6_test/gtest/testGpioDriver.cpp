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
    // ... setup code ...
    
    // Act
    GpioDriver_Status_t status = call_GpioDriverUnit_Init();
    
    // Assert
    EXPECT_EQ(GPIO_STATUS_OK, status);
}

//------------------------------------------------------------------------------
// Test Cases for GpioDriverUnit_ConfigurePin
//------------------------------------------------------------------------------
TEST_F(GpioDriver, GpioDriver_ConfigurePin_ValidPin_ReturnsOK)
{
    // Arrange
    GpioDriver_PinConfig_t config = {
        GPIO_MODE_OUTPUT,
        GPIO_PULL_NONE,
        GPIO_SPEED_HIGH,
        GPIO_STATE_LOW
    };
    
    // Act
    GpioDriver_Status_t status = call_GpioDriverUnit_ConfigurePin(0, &config);
    
    // Assert
    EXPECT_EQ(GPIO_STATUS_OK, status);
}

//------------------------------------------------------------------------------
// Test Cases for GpioDriverUnit_WritePin
//------------------------------------------------------------------------------
TEST_F(GpioDriver, GpioDriver_WritePin_ValidPin_ReturnsOK)
{
    // Arrange
    GpioDriver_PinConfig_t config = {
        GPIO_MODE_OUTPUT,
        GPIO_PULL_NONE,
        GPIO_SPEED_HIGH,
        GPIO_STATE_LOW
    };
    call_GpioDriverUnit_ConfigurePin(0, &config);
    
    // Act
    GpioDriver_Status_t status = call_GpioDriverUnit_WritePin(0, GPIO_STATE_HIGH);
    
    // Assert
    EXPECT_EQ(GPIO_STATUS_OK, status);
}

//------------------------------------------------------------------------------
// Test Cases for GpioDriverUnit_ReadPin
//------------------------------------------------------------------------------
TEST_F(GpioDriver, GpioDriver_ReadPin_ValidPin_ReturnsOK)
{
    // Arrange
    GpioDriver_State_t state = GPIO_STATE_LOW;
    
    // Act
    GpioDriver_Status_t status = call_GpioDriverUnit_ReadPin(0, &state);
    
    // Assert
    EXPECT_EQ(GPIO_STATUS_OK, status);
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
    EXPECT_EQ(GPIO_STATUS_OK, status);
}
