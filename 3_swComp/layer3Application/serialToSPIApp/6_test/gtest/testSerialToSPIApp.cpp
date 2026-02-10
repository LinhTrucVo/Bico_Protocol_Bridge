#include <gtest/gtest.h>

extern "C" {
#include "serialToSPIApp.h"
}

TEST(SerialToSPIAppTest, ConfigureAndTransfer) {
    SerialToSPIApp_Config_t cfg = {1000000, SERIAL_TO_SPI_MODE_0, SERIAL_TO_SPI_BITORDER_MSB_FIRST};
    uint8_t rx[2] = {0};
    SerialToSPIApp_Transfer_t transfer = { nullptr, rx, 2 };
    EXPECT_EQ(SERIAL_TO_SPI_APP_STATUS_OK, SerialToSPIApp_Init());
    EXPECT_EQ(SERIAL_TO_SPI_APP_STATUS_OK, SerialToSPIApp_Configure(&cfg));
    EXPECT_EQ(SERIAL_TO_SPI_APP_STATUS_OK, SerialToSPIApp_Transfer(&transfer));
}
