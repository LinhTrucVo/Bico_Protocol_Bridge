#include <gtest/gtest.h>

extern "C" {
#include "serialize.h"
}

TEST(SerializeTest, BuildFrameSuccess) {
    uint8_t payload[2] = {0x01, 0x02};
    uint8_t buffer[64] = {0};
    Serialize_Message_t msg = { {0x10, 0x01, SERIALIZE_MSG_TYPE_RESPONSE}, payload, 2 };
    Serialize_Buffer_t out = { buffer, sizeof(buffer) };
    uint16_t frameLen = 0;
    EXPECT_EQ(SERIALIZE_STATUS_OK, Serialize_Init());
    EXPECT_EQ(SERIALIZE_STATUS_OK, Serialize_BuildFrame(&msg, &out, &frameLen));
    EXPECT_GT(frameLen, 0U);
}
