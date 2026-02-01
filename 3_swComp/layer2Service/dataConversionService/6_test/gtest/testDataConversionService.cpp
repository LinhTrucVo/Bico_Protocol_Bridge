#include <gtest/gtest.h>
extern "C" {
#include "dataConversionService.h"
}

TEST(DataConversionServiceTest, InitSuccess) {
    EXPECT_EQ(DATA_CONVERSION_SERVICE_STATUS_OK, DataConversionService_Init());
}

TEST(DataConversionServiceTest, ProcessSuccess) {
    DataConversionService_Init();
    EXPECT_EQ(DATA_CONVERSION_SERVICE_STATUS_OK, DataConversionService_Process());
}
