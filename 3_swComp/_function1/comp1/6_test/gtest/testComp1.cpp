//----------------------------------------------------------------------------
// Unit Test file for the simple_calculator module.
//----------------------------------------------------------------------------

#include "gtest/gtest.h"
#include "gmock/gmock.h"

// Unit under test
extern "C"
{
#include "mockComp1.h"
}

//------------------------------------------------------------------------------
// Test Fixture Class
//------------------------------------------------------------------------------
class Comp1 : public ::testing::Test 
{
protected:
    void SetUp() override 
    {
        // Reset all fake functions before each test
        RESET_FAKE(Comp2Unit2PublicFunction);
        FFF_RESET_HISTORY();

    }

    void TearDown() override 
    {
        // Clean up after each test if needed
    }
};

//------------------------------------------------------------------------------
// Test Cases for Comp1Unit1PublicFunction_Test1 function, input 1, get return 2
//------------------------------------------------------------------------------
TEST_F(Comp1, Comp1Unit1PublicFunction_Test1)
{
    // Arrange
    int input = 1;
    int output = 0;
    int expected = 2;

    // Act
    output = call_Comp1Unit1PublicFunction(input);
    // Assert
    EXPECT_EQ(output, expected);
}

//------------------------------------------------------------------------------
// Test Cases for Comp1Unit1PublicFunction_Test2 function, input 2, get return 3
//------------------------------------------------------------------------------
TEST_F(Comp1, Comp1Unit1PublicFunction_Test2)
{
    // Arrange
    int input = 2;
    int output = 0;
    int expected = 3;

    // Act
    output = call_Comp1Unit1PublicFunction(input);
    // Assert
    EXPECT_EQ(output, expected);
}
