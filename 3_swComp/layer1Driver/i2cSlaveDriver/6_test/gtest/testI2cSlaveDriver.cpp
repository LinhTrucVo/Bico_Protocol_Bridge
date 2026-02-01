#include <gtest/gtest.h>
extern "C" {
#include "i2cSlaveDriver.h"
}
TEST(I2cSlaveDriverTest, InitSuccess) {
    EXPECT_EQ(I2C_SLAVE_STATUS_OK, I2cSlaveDriver_Init());
}
