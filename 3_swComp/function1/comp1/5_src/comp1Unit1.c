// This file is used to define the public interface of the component unit.
// It contains public macros, private variables, and function definitions.


//============================================================================
// Dependencies
//============================================================================
#include "comp1.h"
#include "comp1Cfg.h"
#include "comp1Unit1.h"


//============================================================================
// Local Macros
//============================================================================
#define COMP1UNIT1_ARRAYSIZE     3                   //!< Misra doesn't like automatic sizes

//============================================================================
// Local Types
//============================================================================

//----------------------------------------------------------------------------
/** \brief Component Unit Types
*/
//----------------------------------------------------------------------------
typedef enum
{
    RBD_MODULENAME_STATE_INVALID = 0,    //!< Invalid State
    RBD_MODULENAME_STATE_INIT    = 1,    //!< Initialisation State
    RBD_MODULENAME_STATE_READY   = 2     //!< Ready State
} compUnit1_States_en;


//============================================================================
// Variables
//============================================================================

//----------------------------------------------------------------------------
/** \brief Description of the variable.
*/
//----------------------------------------------------------------------------
static uint32_t comp1Unit1Var [COMP1UNIT1_ARRAYSIZE] =
{
    1,          // Some dummy data
    2,
    3
};

uint8_t Comp1_PublicVariable = 0;  //!< Public variable definition

//============================================================================
// Function Definitions
//============================================================================

//----------------------------------------------------------------------------
/** \brief Description of the function
@rst
..  satisfy: requirementid
@endrst
*/
//----------------------------------------------------------------------------
void Comp1Unit1PublicFunction(void)
{
    // Implementation of the public function.
}
