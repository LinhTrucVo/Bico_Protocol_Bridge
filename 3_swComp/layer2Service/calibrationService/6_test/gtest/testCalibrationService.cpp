#include <gtest/gtest.h>

extern "C" {
#include "calibrationService.h"
}

TEST(CalibrationServiceTest, SetAndApplyCalibration) {
    CalibrationService_Data_t data = { 1.0f, 2.0f, true };
    float out = 0.0f;
    EXPECT_EQ(CALIBRATION_SERVICE_STATUS_OK, CalibrationService_Init());
    EXPECT_EQ(CALIBRATION_SERVICE_STATUS_OK, CalibrationService_SetCalibration(0, &data));
    EXPECT_EQ(CALIBRATION_SERVICE_STATUS_OK, CalibrationService_Apply(0, 1.0f, &out));
    EXPECT_NEAR(out, 4.0f, 0.001f);
}
