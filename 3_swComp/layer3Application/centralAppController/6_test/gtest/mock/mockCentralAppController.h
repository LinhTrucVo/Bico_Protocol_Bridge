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
// Static function wrapper declarations
//============================================================================

CentralAppController_Status_t call_CentralAppControllerUnit_Init(void);
CentralAppController_Status_t call_CentralAppControllerUnit_DeInit(void);
CentralAppController_Status_t call_CentralAppControllerUnit_Run(void);
CentralAppController_Status_t call_CentralAppControllerUnit_GetState(CentralAppController_State_t *pState);
CentralAppController_Status_t call_CentralAppControllerUnit_Dispatch(const uint8_t *pRequestFrame, uint16_t requestLength, uint8_t *pResponseBuffer, uint16_t bufferSize, uint16_t *pResponseLength);
CentralAppController_Status_t call_CentralAppControllerUnit_RegisterErrorCallback(CentralAppController_ErrorCallback_t callback);

#endif /* MOCKCENTRALAPPCONTROLLER_H */