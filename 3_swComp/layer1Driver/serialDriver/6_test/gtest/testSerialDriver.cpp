#include <gtest/gtest.h>
extern "C" {
#include "serialDriver.h"
}

TEST(SerialDriverTest, InitSuccess) {
    EXPECT_EQ(SERIAL_STATUS_OK, SerialDriver_Init(SERIAL_BAUDRATE_115200));
}
