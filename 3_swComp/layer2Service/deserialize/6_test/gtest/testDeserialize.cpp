#include <gtest/gtest.h>

extern "C" {
#include "deserialize.h"
}

TEST(DeserializeTest, ParseValidFrame) {
    uint8_t frame[16] = {0};
    frame[0] = 0x02; // ADC_READ
    frame[1] = 0x01; // seq
    frame[2] = 0x00; // type
    frame[3] = 0x00; // payload length LSB
    frame[4] = 0x00; // payload length MSB
    uint16_t crc = 0;
    Deserialize_Frame_t f = { frame, 7 };
    Deserialize_Request_t req = {0};
    Deserialize_Init();
    EXPECT_EQ(DESERIALIZE_STATUS_OK, Deserialize_ComputeCrc(frame, 5, &crc));
    frame[5] = (uint8_t)(crc & 0xFFU);
    frame[6] = (uint8_t)((crc >> 8U) & 0xFFU);
    EXPECT_EQ(DESERIALIZE_STATUS_OK, Deserialize_ParseFrame(&f, &req));
}
