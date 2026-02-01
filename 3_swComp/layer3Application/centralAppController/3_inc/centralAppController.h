// CentralAppController - Public Interface

#ifndef CENTRAL_APP_CONTROLLER_H
#define CENTRAL_APP_CONTROLLER_H

#include <stdint.h>
#include <stdbool.h>
#include "centralAppControllerCfg.h"
#include "centralAppControllerUnit.h"

typedef enum
{
    CENTRAL_APP_CONTROLLER_STATUS_OK = 0,
    CENTRAL_APP_CONTROLLER_STATUS_ERROR,
    CENTRAL_APP_CONTROLLER_STATUS_BUSY
} CentralAppController_Status_t;

typedef enum
{
    CentralAppController_STATE_IDLE = 0,
    CentralAppController_STATE_PROCESSING,
    CentralAppController_STATE_ERROR
} CentralAppController_State_t;

CentralAppController_Status_t CentralAppController_Init(void);
CentralAppController_Status_t CentralAppController_Run(void);
CentralAppController_Status_t CentralAppController_GetState(CentralAppController_State_t *pState);
CentralAppController_Status_t CentralAppController_DeInit(void);

#endif /* CENTRAL_APP_CONTROLLER_H */
