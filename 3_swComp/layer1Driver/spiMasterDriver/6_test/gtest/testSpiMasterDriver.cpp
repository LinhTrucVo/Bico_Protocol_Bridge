#include <gtest/gtest.h>
extern "C" {
#include "spiMasterDriver.h"
}
TEST(SpiMasterDriverTest, InitSuccess) {
    EXPECT_EQ(SPI_MASTER_STATUS_OK, SpiMasterDriver_Init());
}
