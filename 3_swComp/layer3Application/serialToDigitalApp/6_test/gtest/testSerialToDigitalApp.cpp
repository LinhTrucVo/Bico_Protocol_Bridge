#include <gtest/gtest.h>

extern "C" {
#include "serialToDigitalApp.h"
}

TEST(SerialToDigitalAppTest, ConfigurePinAndWrite) {
    SerialToDigitalApp_PinConfig_t cfg = {0, SERIAL_TO_DIGITAL_DIR_OUTPUT, SERIAL_TO_DIGITAL_STATE_LOW, false};
    SerialToDigitalApp_StateValue_t state = SERIAL_TO_DIGITAL_STATE_LOW;
    EXPECT_EQ(SERIAL_TO_DIGITAL_APP_STATUS_OK, SerialToDigitalApp_Init());
    EXPECT_EQ(SERIAL_TO_DIGITAL_APP_STATUS_OK, SerialToDigitalApp_ConfigurePin(&cfg));
    EXPECT_EQ(SERIAL_TO_DIGITAL_APP_STATUS_OK, SerialToDigitalApp_WritePin(0, SERIAL_TO_DIGITAL_STATE_HIGH));
    EXPECT_EQ(SERIAL_TO_DIGITAL_APP_STATUS_OK, SerialToDigitalApp_ReadPin(0, &state));
}
