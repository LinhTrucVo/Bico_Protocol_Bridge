#include <gtest/gtest.h>
extern "C" {
#include "calibrationService.h"
}

TEST(CalibrationServiceTest, InitSuccess) {
    EXPECT_EQ(CALIBRATION_SERVICE_STATUS_OK, CalibrationService_Init());
}

TEST(CalibrationServiceTest, ProcessSuccess) {
    CalibrationService_Init();
    EXPECT_EQ(CALIBRATION_SERVICE_STATUS_OK, CalibrationService_Process());
}
