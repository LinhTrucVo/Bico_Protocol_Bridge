#include <gtest/gtest.h>

extern "C" {
#include "i2cSlaveDriver.h"
}

TEST(I2cSlaveDriverTest, InitAndBuffers) {
    I2cSlaveDriver_Config_t cfg = { 0x10, I2C_SLAVE_ADDRESS_7BIT, false, false, false };
    uint8_t rx[4] = {0};
    uint8_t tx[2] = {0xAA, 0x55};
    EXPECT_EQ(I2C_SLAVE_STATUS_OK, I2cSlaveDriver_Init(&cfg));
    EXPECT_EQ(I2C_SLAVE_STATUS_OK, I2cSlaveDriver_SetRxBuffer(rx, sizeof(rx)));
    EXPECT_EQ(I2C_SLAVE_STATUS_OK, I2cSlaveDriver_SetTxBuffer(tx, sizeof(tx)));
}
