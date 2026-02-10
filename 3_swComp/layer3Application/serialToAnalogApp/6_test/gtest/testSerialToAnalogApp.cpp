#include <gtest/gtest.h>

extern "C" {
#include "serialToAnalogApp.h"
}

TEST(SerialToAnalogAppTest, ConfigureChannel) {
    SerialToAnalogApp_ChannelConfig_t cfg = {0, true, SERIAL_TO_ANALOG_RESOLUTION_12BIT, SERIAL_TO_ANALOG_RANGE_3V3, 1000, 1, false, 0.0f, 0.0f};
    EXPECT_EQ(SERIAL_TO_ANALOG_APP_STATUS_OK, SerialToAnalogApp_Init());
    EXPECT_EQ(SERIAL_TO_ANALOG_APP_STATUS_OK, SerialToAnalogApp_ConfigureChannel(&cfg));
}
