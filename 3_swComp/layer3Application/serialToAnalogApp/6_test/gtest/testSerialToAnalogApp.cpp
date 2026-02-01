#include <gtest/gtest.h>
extern "C" {
#include "serialToAnalogApp.h"
}

TEST(SerialToAnalogAppTest, InitSuccess) {
    EXPECT_EQ(SERIAL_TO_ANALOG_APP_STATUS_OK, SerialToAnalogApp_Init());
}

TEST(SerialToAnalogAppTest, RunSuccess) {
    SerialToAnalogApp_Init();
    EXPECT_EQ(SERIAL_TO_ANALOG_APP_STATUS_OK, SerialToAnalogApp_Run());
}

TEST(SerialToAnalogAppTest, GetStateSuccess) {
    SerialToAnalogApp_State_t state;
    SerialToAnalogApp_Init();
    EXPECT_EQ(SERIAL_TO_ANALOG_APP_STATUS_OK, SerialToAnalogApp_GetState(&state));
    EXPECT_EQ(SerialToAnalogApp_STATE_IDLE, state);
}
