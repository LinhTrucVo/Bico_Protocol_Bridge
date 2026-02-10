#include <gtest/gtest.h>

extern "C" {
#include "i2cMasterDriver.h"
}

TEST(I2cMasterDriverTest, InitAndWrite) {
    I2cMasterDriver_Config_t cfg = { I2C_SPEED_STANDARD, I2C_ADDRESS_7BIT, false, false, 100 };
    uint8_t data[2] = {0x01, 0x02};
    EXPECT_EQ(I2C_MASTER_STATUS_OK, I2cMasterDriver_Init(&cfg));
    EXPECT_EQ(I2C_MASTER_STATUS_OK, I2cMasterDriver_Write(0x50, data, 2));
}
