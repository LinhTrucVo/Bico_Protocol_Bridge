#include <gtest/gtest.h>

extern "C" {
#include "dataConversionService.h"
}

TEST(DataConversionServiceTest, ConvertRawToVoltage) {
    float voltage = 0.0f;
    EXPECT_EQ(DATA_CONVERSION_SERVICE_STATUS_OK, DataConversionService_Init());
    EXPECT_EQ(DATA_CONVERSION_SERVICE_STATUS_OK, DataConversionService_ConvertRawToVoltage(2048, 12, 3.3f, &voltage));
    EXPECT_GT(voltage, 0.0f);
}
