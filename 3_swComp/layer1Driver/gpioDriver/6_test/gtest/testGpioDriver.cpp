// GPIO Driver Test Cases

#include <gtest/gtest.h>

extern "C" {
#include "gpioDriver.h"
}

TEST(GpioDriverTest, InitAndConfigurePin) {
    GpioDriver_PinConfig_t cfg = {
        GPIO_MODE_OUTPUT,
        GPIO_PULL_NONE,
        GPIO_SPEED_LOW,
        GPIO_STATE_LOW
    };
    EXPECT_EQ(GPIO_STATUS_OK, GpioDriver_Init());
    EXPECT_EQ(GPIO_STATUS_OK, GpioDriver_ConfigurePin(0, &cfg));
}

TEST(GpioDriverTest, WriteReadTogglePin) {
    GpioDriver_PinConfig_t cfg = {
        GPIO_MODE_OUTPUT,
        GPIO_PULL_NONE,
        GPIO_SPEED_LOW,
        GPIO_STATE_LOW
    };
    GpioDriver_State_t state = GPIO_STATE_LOW;
    GpioDriver_Init();
    GpioDriver_ConfigurePin(0, &cfg);
    EXPECT_EQ(GPIO_STATUS_OK, GpioDriver_WritePin(0, GPIO_STATE_HIGH));
    EXPECT_EQ(GPIO_STATUS_OK, GpioDriver_ReadPin(0, &state));
    EXPECT_EQ(GPIO_STATE_HIGH, state);
    EXPECT_EQ(GPIO_STATUS_OK, GpioDriver_TogglePin(0));
}
