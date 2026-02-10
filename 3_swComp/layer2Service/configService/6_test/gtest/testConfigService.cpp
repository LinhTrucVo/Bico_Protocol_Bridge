#include <gtest/gtest.h>

extern "C" {
#include "configService.h"
}

TEST(ConfigServiceTest, SetGetAnalogConfig) {
    ConfigService_AnalogChannelConfig_t cfg = {0, 12, 3.3f, 1000, 1, 1.0f, 0.0f, false};
    ConfigService_AnalogChannelConfig_t out = {0};
    EXPECT_EQ(CONFIG_SERVICE_STATUS_OK, ConfigService_Init());
    EXPECT_EQ(CONFIG_SERVICE_STATUS_OK, ConfigService_SetAnalogChannelConfig(0, &cfg));
    EXPECT_EQ(CONFIG_SERVICE_STATUS_OK, ConfigService_GetAnalogChannelConfig(0, &out));
}
