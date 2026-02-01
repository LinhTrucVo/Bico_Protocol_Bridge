#include <gtest/gtest.h>
extern "C" {
#include "pwmDriver.h"
}
TEST(PwmDriverTest, InitSuccess) {
    EXPECT_EQ(PWM_STATUS_OK, PwmDriver_Init());
}
