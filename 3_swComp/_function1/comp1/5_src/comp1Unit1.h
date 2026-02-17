// This file is used to define the public interface of the component unit.
// It contains public macros, types, variables, and function prototypes that shall be included in component headers file (comp1.h)

#ifndef COMP1UNIT1_H
#define COMP1UNIT1_H

//============================================================================
// Dependencies
//============================================================================
#include "comp1Cfg.h"

//============================================================================
// Public Macros
//============================================================================
#define COMP1_MACRO_NAME     VALUE   

//============================================================================
// Public Types
//============================================================================
typedef enum
{
    COMP1_ENUM_VALUE1 = 0,
    COMP1_ENUM_VALUE2 = 1
} Comp1_EnumType;


//============================================================================
// Public Variables
//============================================================================
extern uint8_t Comp1_PublicVariable;

//============================================================================
// Public Functions
//============================================================================
void Comp1Unit1PublicFunction(void);


#endif /* COMP1UNIT1_H */