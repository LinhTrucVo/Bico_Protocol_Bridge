#include <gtest/gtest.h>
extern "C" {
#include "spiSlaveDriver.h"
}
TEST(SpiSlaveDriverTest, InitSuccess) {
    EXPECT_EQ(SPI_SLAVE_STATUS_OK, SpiSlaveDriver_Init());
}
