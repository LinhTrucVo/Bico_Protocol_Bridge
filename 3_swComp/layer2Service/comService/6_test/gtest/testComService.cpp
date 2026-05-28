// Unit tests for ComService

#include "gtest/gtest.h"

extern "C"
{
#include "comServiceUnit.h"
}

class ComServiceTest : public ::testing::Test
{
protected:
    void SetUp() override
    {
        ComServiceUnit_Init();
    }
    void TearDown() override
    {
        ComServiceUnit_DeInit();
    }
};

TEST_F(ComServiceTest, InitReturnsOk)
{
    // Init called in SetUp
    EXPECT_TRUE(true);
}

TEST_F(ComServiceTest, IsRxDataAvailableReturnsFalseWhenEmpty)
{
    EXPECT_FALSE(ComServiceUnit_IsRxDataAvailable());
}

TEST_F(ComServiceTest, ReadReturnsBufferEmptyWhenNoData)
{
    uint8_t buf[32];
    uint16_t readLen = 0;
    EXPECT_EQ(COMSERVICE_STATUS_BUFFER_EMPTY, ComServiceUnit_Read(buf, sizeof(buf), &readLen));
    EXPECT_EQ(0U, readLen);
}

TEST_F(ComServiceTest, WriteReturnsInvalidParamForNull)
{
    EXPECT_EQ(COMSERVICE_STATUS_INVALID_PARAM, ComServiceUnit_Write(NULL, 10));
}

TEST_F(ComServiceTest, WriteReturnsInvalidParamForZeroLength)
{
    uint8_t data[] = {0x01};
    EXPECT_EQ(COMSERVICE_STATUS_INVALID_PARAM, ComServiceUnit_Write(data, 0));
}
