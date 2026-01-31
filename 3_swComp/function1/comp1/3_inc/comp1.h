// This file is used to define the public interface of the component.
// It contains public macros, types, variables, and function prototypes of component itself and Units in this component.

#ifndef COMP1_H
#define COMP1_H

//============================================================================
// Dependencies
//============================================================================
#include "comp1Cfg.h"
#include "comp1Unit1.h"

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
extern uint8_t Comp1Unit1_PublicVariable;

//============================================================================
// Public Functions
//============================================================================
void Comp1Unit1PublicFunction(void);


#endif /* COMP1_H */