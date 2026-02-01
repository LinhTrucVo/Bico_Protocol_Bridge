#include <gtest/gtest.h>
extern "C" {
#include "serialToI2CApp.h"
}

TEST(SerialToI2CAppTest, InitSuccess) {
    EXPECT_EQ(SERIAL_TO_I2C_APP_STATUS_OK, SerialToI2CApp_Init());
}

TEST(SerialToI2CAppTest, RunSuccess) {
    SerialToI2CApp_Init();
    EXPECT_EQ(SERIAL_TO_I2C_APP_STATUS_OK, SerialToI2CApp_Run());
}

TEST(SerialToI2CAppTest, GetStateSuccess) {
    SerialToI2CApp_State_t state;
    SerialToI2CApp_Init();
    EXPECT_EQ(SERIAL_TO_I2C_APP_STATUS_OK, SerialToI2CApp_GetState(&state));
    EXPECT_EQ(SerialToI2CApp_STATE_IDLE, state);
}
