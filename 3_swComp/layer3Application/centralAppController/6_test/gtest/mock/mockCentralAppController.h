// This file declares the FFF for functions and MOCK functions for CentralAppController testing

#ifndef MOCKCENTRALAPPCONTROLLER_H
#define MOCKCENTRALAPPCONTROLLER_H

//============================================================================
// Dependencies
//============================================================================
#include "fff.h"

#include "centralAppController.h"
#include "centralAppControllerUnit.h"

//============================================================================
// Mock function declarations
//============================================================================
// Declare fake functions for external dependencies if any
// DECLARE_FAKE_VALUE_FUNC(int, ExternalFunction, int);

//============================================================================
// Static function wrapper declarations
//============================================================================

CentralAppController_Status_t call_CentralAppControllerUnit_Init(void);
CentralAppController_Status_t call_CentralAppControllerUnit_DeInit(void);
CentralAppController_Status_t call_CentralAppControllerUnit_Run(void);
CentralAppController_Status_t call_CentralAppControllerUnit_GetState(CentralAppController_State_t *pState);
CentralAppController_Status_t call_CentralAppControllerUnit_ProcessFrame(const CentralAppController_Frame_t *pInFrame, CentralAppController_OutFrame_t *pOutFrame, uint16_t *pOutLength);
CentralAppController_Status_t call_CentralAppControllerUnit_RegisterErrorCallback(CentralAppController_ErrorCallback_t callback);

#endif /* MOCKCENTRALAPPCONTROLLER_H */
