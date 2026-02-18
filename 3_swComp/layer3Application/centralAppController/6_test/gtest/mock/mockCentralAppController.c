// This file defines the FFF for functions and MOCK functions for CentralAppController testing

//============================================================================
// Dependencies
//============================================================================
#include "mockCentralAppController.h"

// Include the .c file to get access to static variables and functions
#include "centralAppControllerUnit.c"

//============================================================================
// Mock function definitions
//============================================================================

// Required for FFF
DEFINE_FFF_GLOBALS;

// DEFINE_FAKE_VALUE_FUNC(int, ExternalFunction, int);

//============================================================================
// Static function wrapper definitions
//============================================================================

CentralAppController_Status_t call_CentralAppControllerUnit_Init(void)
{
    return CentralAppControllerUnit_Init();
}

CentralAppController_Status_t call_CentralAppControllerUnit_DeInit(void)
{
    return CentralAppControllerUnit_DeInit();
}

CentralAppController_Status_t call_CentralAppControllerUnit_Run(void)
{
    return CentralAppControllerUnit_Run();
}

CentralAppController_Status_t call_CentralAppControllerUnit_GetState(CentralAppController_State_t *pState)
{
    return CentralAppControllerUnit_GetState(pState);
}

CentralAppController_Status_t call_CentralAppControllerUnit_ProcessFrame(const CentralAppController_Frame_t *pInFrame, CentralAppController_OutFrame_t *pOutFrame, uint16_t *pOutLength)
{
    return CentralAppControllerUnit_ProcessFrame(pInFrame, pOutFrame, pOutLength);
}

CentralAppController_Status_t call_CentralAppControllerUnit_RegisterErrorCallback(CentralAppController_ErrorCallback_t callback)
{
    return CentralAppControllerUnit_RegisterErrorCallback(callback);
}
