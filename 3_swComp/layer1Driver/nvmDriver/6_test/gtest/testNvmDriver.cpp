#include <gtest/gtest.h>
extern "C" {
#include "nvmDriver.h"
}
TEST(NvmDriverTest, InitSuccess) {
    EXPECT_EQ(NVM_STATUS_OK, NvmDriver_Init());
}
