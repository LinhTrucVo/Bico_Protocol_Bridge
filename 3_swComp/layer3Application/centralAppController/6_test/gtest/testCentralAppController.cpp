#include <gtest/gtest.h>
extern "C" {
#include "centralAppController.h"
}

TEST(CentralAppControllerTest, InitSuccess) {
    EXPECT_EQ(CENTRAL_APP_CONTROLLER_STATUS_OK, CentralAppController_Init());
}

TEST(CentralAppControllerTest, RunSuccess) {
    CentralAppController_Init();
    EXPECT_EQ(CENTRAL_APP_CONTROLLER_STATUS_OK, CentralAppController_Run());
}

TEST(CentralAppControllerTest, GetStateSuccess) {
    CentralAppController_State_t state;
    CentralAppController_Init();
    EXPECT_EQ(CENTRAL_APP_CONTROLLER_STATUS_OK, CentralAppController_GetState(&state));
    EXPECT_EQ(CentralAppController_STATE_IDLE, state);
}
