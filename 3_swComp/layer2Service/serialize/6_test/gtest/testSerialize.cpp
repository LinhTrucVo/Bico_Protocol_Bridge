#include <gtest/gtest.h>
extern "C" {
#include "serialize.h"
}

TEST(SerializeTest, InitSuccess) {
    EXPECT_EQ(SERIALIZE_STATUS_OK, Serialize_Init());
}

TEST(SerializeTest, ProcessSuccess) {
    Serialize_Init();
    EXPECT_EQ(SERIALIZE_STATUS_OK, Serialize_Process());
}
