#include <gtest/gtest.h>
extern "C" {
#include "serialToDigitalApp.h"
}

TEST(SerialToDigitalAppTest, InitSuccess) {
    EXPECT_EQ(SERIAL_TO_DIGITAL_APP_STATUS_OK, SerialToDigitalApp_Init());
}

TEST(SerialToDigitalAppTest, RunSuccess) {
    SerialToDigitalApp_Init();
    EXPECT_EQ(SERIAL_TO_DIGITAL_APP_STATUS_OK, SerialToDigitalApp_Run());
}

TEST(SerialToDigitalAppTest, GetStateSuccess) {
    SerialToDigitalApp_State_t state;
    SerialToDigitalApp_Init();
    EXPECT_EQ(SERIAL_TO_DIGITAL_APP_STATUS_OK, SerialToDigitalApp_GetState(&state));
    EXPECT_EQ(SerialToDigitalApp_STATE_IDLE, state);
}
