// CentralAppController Implementation

#include "centralAppController.h"
#include "deserialize.h"
#include "serialize.h"

typedef struct
{
    bool initialized;
    CentralAppController_State_t currentState;
    CentralAppController_ErrorCallback_t errorCallback;
} CentralAppController_Context_t;

static CentralAppController_Context_t context = {0};

CentralAppController_Status_t CentralAppController_Init(void)
{
    context.initialized = true;
    context.currentState = CentralAppController_STATE_IDLE;
    context.errorCallback = NULL;
    (void)Deserialize_Init();
    (void)Serialize_Init();
    return CENTRAL_APP_CONTROLLER_STATUS_OK;
}

CentralAppController_Status_t CentralAppController_Run(void)
{
    if (!context.initialized)
    {
        return CENTRAL_APP_CONTROLLER_STATUS_ERROR;
    }
    return CENTRAL_APP_CONTROLLER_STATUS_OK;
}

CentralAppController_Status_t CentralAppController_GetState(CentralAppController_State_t *pState)
{
    if (pState == NULL)
    {
        return CENTRAL_APP_CONTROLLER_STATUS_INVALID_PARAM;
    }
    *pState = context.currentState;
    return CENTRAL_APP_CONTROLLER_STATUS_OK;
}

CentralAppController_Status_t CentralAppController_ProcessFrame(const CentralAppController_Frame_t *pInFrame, CentralAppController_OutFrame_t *pOutFrame, uint16_t *pOutLength)
{
    if (!context.initialized)
    {
        return CENTRAL_APP_CONTROLLER_STATUS_NOT_INITIALIZED;
    }
    if (pInFrame == NULL || pOutFrame == NULL || pOutLength == NULL || pOutFrame->pFrame == NULL)
    {
        return CENTRAL_APP_CONTROLLER_STATUS_INVALID_PARAM;
    }

    context.currentState = CentralAppController_STATE_PROCESSING;
    Deserialize_Request_t request = {0};
    Deserialize_Frame_t frame = { pInFrame->pFrame, pInFrame->frameLength };
    Deserialize_Status_t dstatus = Deserialize_ParseFrame(&frame, &request);
    if (dstatus != DESERIALIZE_STATUS_OK)
    {
        Serialize_Buffer_t outBuf = { pOutFrame->pFrame, pOutFrame->maxLength };
        (void)Serialize_BuildError(request.commandId, request.sequenceId, SERIALIZE_ERROR_INVALID_CMD, &outBuf, pOutLength);
        context.currentState = CentralAppController_STATE_ERROR;
        if (context.errorCallback != NULL)
        {
            context.errorCallback((uint8_t)dstatus);
        }
        return CENTRAL_APP_CONTROLLER_STATUS_ERROR;
    }

    // TODO: Dispatch to application handlers based on request.command
    Serialize_Message_t response = {
        .header = { request.commandId, request.sequenceId, SERIALIZE_MSG_TYPE_RESPONSE },
        .pPayload = NULL,
        .payloadLength = 0
    };
    Serialize_Buffer_t outBuf = { pOutFrame->pFrame, pOutFrame->maxLength };
    (void)Serialize_BuildFrame(&response, &outBuf, pOutLength);

    context.currentState = CentralAppController_STATE_IDLE;
    return CENTRAL_APP_CONTROLLER_STATUS_OK;
}

CentralAppController_Status_t CentralAppController_RegisterErrorCallback(CentralAppController_ErrorCallback_t callback)
{
    if (!context.initialized)
    {
        return CENTRAL_APP_CONTROLLER_STATUS_NOT_INITIALIZED;
    }
    context.errorCallback = callback;
    return CENTRAL_APP_CONTROLLER_STATUS_OK;
}

CentralAppController_Status_t CentralAppController_DeInit(void)
{
    context.initialized = false;
    context.currentState = CentralAppController_STATE_IDLE;
    return CENTRAL_APP_CONTROLLER_STATUS_OK;
}
