#include <gtest/gtest.h>
extern "C" {
#include "serialToSPIApp.h"
}

TEST(SerialToSPIAppTest, InitSuccess) {
    EXPECT_EQ(SERIAL_TO_SPI_APP_STATUS_OK, SerialToSPIApp_Init());
}

TEST(SerialToSPIAppTest, RunSuccess) {
    SerialToSPIApp_Init();
    EXPECT_EQ(SERIAL_TO_SPI_APP_STATUS_OK, SerialToSPIApp_Run());
}

TEST(SerialToSPIAppTest, GetStateSuccess) {
    SerialToSPIApp_State_t state;
    SerialToSPIApp_Init();
    EXPECT_EQ(SERIAL_TO_SPI_APP_STATUS_OK, SerialToSPIApp_GetState(&state));
    EXPECT_EQ(SerialToSPIApp_STATE_IDLE, state);
}
