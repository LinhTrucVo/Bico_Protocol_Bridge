#ifndef CENTRAL_APP_CONTROLLERUNIT_H
#define CENTRAL_APP_CONTROLLERUNIT_H
#include <stdint.h>
#include "centralAppControllerCfg.h"

//============================================================================
// Configuration Macros
//============================================================================
#define CENTRAL_APP_CFG_MAX_FRAME_SIZE      256
#define CENTRAL_APP_CFG_RESPONSE_TIMEOUT_MS 10

//============================================================================
// Type Definitions
//============================================================================
typedef enum
{
    CentralAppController_STATE_IDLE = 0,
    CentralAppController_STATE_PROCESSING = 1,
    CentralAppController_STATE_WAITING = 2,
    CentralAppController_STATE_ERROR = 3
} CentralAppController_State_t;

typedef struct
{
    const uint8_t *pFrame;
    uint16_t frameLength;
} CentralAppController_Frame_t;

typedef struct
{
    uint8_t *pFrame;
    uint16_t frameLength;
} CentralAppController_OutFrame_t;

typedef enum
{
    CENTRAL_APP_CONTROLLER_STATUS_OK = 0,
    CENTRAL_APP_CONTROLLER_STATUS_ERROR = 1,
    CENTRAL_APP_CONTROLLER_STATUS_INVALID_PARAM = 2,
    CENTRAL_APP_CONTROLLER_STATUS_TIMEOUT = 3,
    CENTRAL_APP_CONTROLLER_STATUS_BUSY = 4,
    CENTRAL_APP_CONTROLLER_STATUS_NOT_INITIALIZED = 5
} CentralAppController_Status_t;

typedef void (*CentralAppController_ErrorCallback_t)(uint8_t errorCode);

//============================================================================
// Public Functions
//============================================================================
CentralAppController_Status_t CentralAppControllerUnit_Init(void);
CentralAppController_Status_t CentralAppControllerUnit_DeInit(void);
CentralAppController_Status_t CentralAppControllerUnit_Run(void);
CentralAppController_Status_t CentralAppControllerUnit_GetState(CentralAppController_State_t *pState);
CentralAppController_Status_t CentralAppControllerUnit_ProcessFrame(const CentralAppController_Frame_t *pInFrame, CentralAppController_OutFrame_t *pOutFrame, uint16_t *pOutLength);
CentralAppController_Status_t CentralAppControllerUnit_RegisterErrorCallback(CentralAppController_ErrorCallback_t callback);

//============================================================================
// Backward Compatibility Macros
//============================================================================
#define CentralAppControllerUnit_Init CentralAppController_Init
#define CentralAppControllerUnit_DeInit CentralAppController_DeInit
#define CentralAppControllerUnit_Run CentralAppController_Run
#define CentralAppControllerUnit_GetState CentralAppController_GetState
#define CentralAppControllerUnit_ProcessFrame CentralAppController_ProcessFrame
#define CentralAppControllerUnit_RegisterErrorCallback CentralAppController_RegisterErrorCallback

#endif
