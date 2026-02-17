
//============================================================================
// Dependencies
//============================================================================
#include "mockComp1.h"

// Include the .c file to get access to static variables and functions
#include "comp1Unit1.c"

//============================================================================
// Mock function definitions
//============================================================================

// Required for FFF
DEFINE_FFF_GLOBALS;

DEFINE_FAKE_VOID_FUNC(dummyFunction01);

DEFINE_FAKE_VALUE_FUNC(int, dummyFunction02, int);

DEFINE_FAKE_VALUE_FUNC_VARARG(int, dummyFunction03, int, int, ...);

DEFINE_FAKE_VALUE_FUNC(int, dummyFunction04, int);

//============================================================================
// Static variable getter function definitions
//============================================================================

uint8_t get_COMP1UNIT1_ARRAYSIZE(void)
{
    return COMP1UNIT1_ARRAYSIZE;
}

//============================================================================
// Static function wrapper definitions
//============================================================================

uint32_t call_Comp1Unit1PublicFunction(void)
{
    return Comp1Unit1PublicFunction();
}
