#include <gtest/gtest.h>
extern "C" {
#include "deserialize.h"
}

TEST(DeserializeTest, InitSuccess) {
    EXPECT_EQ(DESERIALIZE_STATUS_OK, Deserialize_Init());
}

TEST(DeserializeTest, ProcessSuccess) {
    Deserialize_Init();
    EXPECT_EQ(DESERIALIZE_STATUS_OK, Deserialize_Process());
}
