#include <gtest/gtest.h>
extern "C" {
#include "configService.h"
}

TEST(ConfigServiceTest, InitSuccess) {
    EXPECT_EQ(CONFIG_SERVICE_STATUS_OK, ConfigService_Init());
}

TEST(ConfigServiceTest, ProcessSuccess) {
    ConfigService_Init();
    EXPECT_EQ(CONFIG_SERVICE_STATUS_OK, ConfigService_Process());
}
