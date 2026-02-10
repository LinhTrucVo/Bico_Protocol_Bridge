#include <gtest/gtest.h>

extern "C" {
#include "serialDriver.h"
}

TEST(SerialDriverTest, InitAndSend) {
    SerialDriver_Config_t cfg = {
        SERIAL_BAUDRATE_115200,
        SERIAL_PARITY_NONE,
        SERIAL_STOPBITS_1,
        SERIAL_DATABITS_8,
        SERIAL_FLOWCONTROL_NONE,
        false,
        false
    };
    uint8_t data[2] = {0xAA, 0x55};
    EXPECT_EQ(SERIAL_STATUS_OK, SerialDriver_Init(&cfg));
    EXPECT_EQ(SERIAL_STATUS_OK, SerialDriver_Send(data, 2));
}
