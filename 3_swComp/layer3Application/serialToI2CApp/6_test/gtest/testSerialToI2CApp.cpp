#include <gtest/gtest.h>

extern "C" {
#include "serialToI2CApp.h"
}

TEST(SerialToI2CAppTest, ConfigureAndRead) {
    SerialToI2CApp_Config_t cfg = {100000, SERIAL_TO_I2C_ADDR_7BIT, 100};
    uint8_t data[2] = {0};
    EXPECT_EQ(SERIAL_TO_I2C_APP_STATUS_OK, SerialToI2CApp_Init());
    EXPECT_EQ(SERIAL_TO_I2C_APP_STATUS_OK, SerialToI2CApp_Configure(&cfg));
    EXPECT_EQ(SERIAL_TO_I2C_APP_STATUS_OK, SerialToI2CApp_Read(0x50, data, 2));
}
