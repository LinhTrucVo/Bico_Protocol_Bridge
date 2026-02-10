#include <gtest/gtest.h>

extern "C" {
#include "nvmService.h"
}

TEST(NvmServiceTest, SaveLoad) {
    uint8_t data[2] = {0x11, 0x22};
    uint8_t out[4] = {0};
    uint16_t outLen = 0;
    NvmService_Blob_t blob = { NVM_SERVICE_KEY_SYSTEM_CONFIG, 2, data };
    EXPECT_EQ(NVM_SERVICE_STATUS_OK, NvmService_Init());
    EXPECT_EQ(NVM_SERVICE_STATUS_OK, NvmService_Save(&blob));
    EXPECT_EQ(NVM_SERVICE_STATUS_OK, NvmService_Load(NVM_SERVICE_KEY_SYSTEM_CONFIG, out, sizeof(out), &outLen));
    EXPECT_EQ(outLen, 2);
}
