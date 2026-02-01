#include <gtest/gtest.h>
extern "C" {
#include "nvmService.h"
}

TEST(NvmServiceTest, InitSuccess) {
    EXPECT_EQ(NVM_SERVICE_STATUS_OK, NvmService_Init());
}

TEST(NvmServiceTest, ProcessSuccess) {
    NvmService_Init();
    EXPECT_EQ(NVM_SERVICE_STATUS_OK, NvmService_Process());
}
