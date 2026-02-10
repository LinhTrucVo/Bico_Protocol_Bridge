#include <gtest/gtest.h>

extern "C" {
#include "spiSlaveDriver.h"
}

TEST(SpiSlaveDriverTest, InitAndBuffers) {
    SpiSlaveDriver_Config_t cfg = { SPI_SLAVE_MODE_0, SPI_SLAVE_BITORDER_MSB_FIRST, false, false };
    uint8_t rx[4] = {0};
    uint8_t tx[2] = {0xAA, 0x55};
    EXPECT_EQ(SPI_SLAVE_STATUS_OK, SpiSlaveDriver_Init(&cfg));
    EXPECT_EQ(SPI_SLAVE_STATUS_OK, SpiSlaveDriver_SetRxBuffer(rx, sizeof(rx)));
    EXPECT_EQ(SPI_SLAVE_STATUS_OK, SpiSlaveDriver_SetTxBuffer(tx, sizeof(tx)));
}
