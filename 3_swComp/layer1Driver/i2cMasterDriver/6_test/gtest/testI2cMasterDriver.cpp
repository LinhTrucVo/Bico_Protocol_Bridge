#include <gtest/gtest.h>
extern "C" {
#include "i2cMasterDriver.h"
}

TEST(I2cMasterDriverTest, InitSuccess) {
    EXPECT_EQ(I2C_MASTER_STATUS_OK, I2cMasterDriver_Init());
}
