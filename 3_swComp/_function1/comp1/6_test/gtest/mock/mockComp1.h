// This file declares the FFF for functions and MOCK functions for Comp1 testing

#ifndef MOCKCOMP1_H
#define MOCKCOMP1_H

//============================================================================
// Dependencies
//============================================================================
#include "fff.h"

#include "comp1.h"
#include "comp1Unit1.h"

//============================================================================
// Mock function declarations
//============================================================================
// DECLARE_FAKE_VOID_FUNC(dummyFunction01);

DECLARE_FAKE_VALUE_FUNC(int, Comp2Unit2PublicFunction, int);

// DECLARE_FAKE_VALUE_FUNC_VARARG(int, dummyFunction03, int, int, ...);

// DECLARE_FAKE_VALUE_FUNC(int, dummyFunction04, int);

//============================================================================
// Static variable and macro getter function declarations
//============================================================================

uint8_t get_COMP1UNIT1_ARRAYSIZE(void);

//============================================================================
// Static function wrapper declarations
//============================================================================

void call_Comp1Unit1PublicFunction(void);

#endif // MOCKCOMP1_H
