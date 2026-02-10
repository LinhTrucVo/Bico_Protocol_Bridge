#include <gtest/gtest.h>

extern "C" {
#include "centralAppController.h"
#include "deserialize.h"
}

TEST(CentralAppControllerTest, ProcessFrame) {
    uint8_t inFrame[8] = {0};
    uint8_t outFrame[64] = {0};
    uint16_t outLen = 0;
    CentralAppController_Frame_t in = { inFrame, 7 };
    CentralAppController_OutFrame_t out = { outFrame, sizeof(outFrame) };
    uint16_t crc = 0;

    inFrame[0] = 0x02; // ADC_READ
    inFrame[1] = 0x01; // seq
    inFrame[2] = 0x00;
    inFrame[3] = 0x00;
    inFrame[4] = 0x00;
    Deserialize_Init();
    Deserialize_ComputeCrc(inFrame, 5, &crc);
    inFrame[5] = (uint8_t)(crc & 0xFFU);
    inFrame[6] = (uint8_t)((crc >> 8U) & 0xFFU);

    EXPECT_EQ(CENTRAL_APP_CONTROLLER_STATUS_OK, CentralAppController_Init());
    EXPECT_EQ(CENTRAL_APP_CONTROLLER_STATUS_OK, CentralAppController_ProcessFrame(&in, &out, &outLen));
    EXPECT_GT(outLen, 0U);
}

TEST(CentralAppControllerTest, GetStateSuccess) {
    CentralAppController_State_t state;
    CentralAppController_Init();
    EXPECT_EQ(CENTRAL_APP_CONTROLLER_STATUS_OK, CentralAppController_GetState(&state));
    EXPECT_EQ(CentralAppController_STATE_IDLE, state);
}
