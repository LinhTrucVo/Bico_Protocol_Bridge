#include <gtest/gtest.h>

extern "C" {
#include "spiMasterDriver.h"
}

TEST(SpiMasterDriverTest, InitAndTransmit) {
    SpiMasterDriver_Config_t cfg = { 1000000, SPI_MODE_0, SPI_BITORDER_MSB_FIRST, SPI_DATASIZE_8BIT, SPI_CS_MODE_MANUAL, false, false };
    uint8_t data[2] = {0x01, 0x02};
    EXPECT_EQ(SPI_MASTER_STATUS_OK, SpiMasterDriver_Init(&cfg));
    EXPECT_EQ(SPI_MASTER_STATUS_OK, SpiMasterDriver_Transmit(data, 2));
}
