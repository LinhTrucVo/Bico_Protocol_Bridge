#include <gtest/gtest.h>

extern "C" {
#include "pwmDriver.h"
}

TEST(PwmDriverTest, InitAndConfigure) {
    PwmDriver_ChannelConfig_t cfg = { 1000, 5000, PWM_POLARITY_NORMAL, PWM_ALIGNMENT_EDGE, false, 0 };
    EXPECT_EQ(PWM_STATUS_OK, PwmDriver_Init());
    EXPECT_EQ(PWM_STATUS_OK, PwmDriver_ConfigureChannel(PWM_CHANNEL_0, &cfg));
    EXPECT_EQ(PWM_STATUS_OK, PwmDriver_StartChannel(PWM_CHANNEL_0));
}
