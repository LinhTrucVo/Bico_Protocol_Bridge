#include <gtest/gtest.h>

extern "C" {
#include "nvmDriver.h"
}

TEST(NvmDriverTest, InitAndWriteRead) {
    NvmDriver_Config_t cfg = { NVM_TYPE_FLASH, 0x00000000U, 0x00010000U, 256, 4096, false };
    uint8_t data[2] = {0x11, 0x22};
    uint8_t out[2] = {0};
    EXPECT_EQ(NVM_STATUS_OK, NvmDriver_Init(&cfg));
    EXPECT_EQ(NVM_STATUS_OK, NvmDriver_Write(0, data, 2));
    EXPECT_EQ(NVM_STATUS_OK, NvmDriver_Read(0, out, 2));
}
