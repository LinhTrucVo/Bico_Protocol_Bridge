// GPIO Driver Test Cases

#include <gtest/gtest.h>

extern "C" {
#include "gpioDriver.h"
}

class GpioDriverTest : public ::testing::Test {
protected:
    void SetUp() override {
        GpioDriver_Init();
    }
};

TEST_F(GpioDriverTest, InitSuccess) {
    GpioDriver_Status_t status = GpioDriver_Init();
    EXPECT_EQ(GPIO_STATUS_OK, status);
}

TEST_F(GpioDriverTest, WritePinSuccess) {
    GpioDriver_Status_t status = GpioDriver_WritePin(0, GPIO_STATE_HIGH);
    EXPECT_EQ(GPIO_STATUS_OK, status);
}
