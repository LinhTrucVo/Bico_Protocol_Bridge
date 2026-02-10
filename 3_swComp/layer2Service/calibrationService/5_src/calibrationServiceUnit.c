// CalibrationService Implementation

#include "calibrationService.h"
#include "calibrationServiceCfg.h"

typedef struct
{
    bool initialized;
    CalibrationService_Data_t data[CALIBRATION_CFG_MAX_CHANNELS];
} CalibrationService_Context_t;

static CalibrationService_Context_t context = {0};

CalibrationService_Status_t CalibrationService_Init(void)
{
    context.initialized = true;
    for (uint8_t i = 0; i < CALIBRATION_CFG_MAX_CHANNELS; i++)
    {
        context.data[i].gain = CALIBRATION_CFG_DEFAULT_GAIN;
        context.data[i].offset = CALIBRATION_CFG_DEFAULT_OFFSET;
        context.data[i].valid = false;
    }
    return CALIBRATION_SERVICE_STATUS_OK;
}

CalibrationService_Status_t CalibrationService_DeInit(void)
{
    context.initialized = false;
    return CALIBRATION_SERVICE_STATUS_OK;
}

CalibrationService_Status_t CalibrationService_SetCalibration(uint8_t channelId, const CalibrationService_Data_t *pData)
{
    if (!context.initialized)
    {
        return CALIBRATION_SERVICE_STATUS_NOT_INITIALIZED;
    }
    if (pData == NULL || channelId >= CALIBRATION_CFG_MAX_CHANNELS)
    {
        return CALIBRATION_SERVICE_STATUS_INVALID_PARAM;
    }

    context.data[channelId] = *pData;
    context.data[channelId].valid = true;
    return CALIBRATION_SERVICE_STATUS_OK;
}

CalibrationService_Status_t CalibrationService_GetCalibration(uint8_t channelId, CalibrationService_Data_t *pData)
{
    if (!context.initialized)
    {
        return CALIBRATION_SERVICE_STATUS_NOT_INITIALIZED;
    }
    if (pData == NULL || channelId >= CALIBRATION_CFG_MAX_CHANNELS)
    {
        return CALIBRATION_SERVICE_STATUS_INVALID_PARAM;
    }

    *pData = context.data[channelId];
    return CALIBRATION_SERVICE_STATUS_OK;
}

CalibrationService_Status_t CalibrationService_ClearCalibration(uint8_t channelId)
{
    if (!context.initialized)
    {
        return CALIBRATION_SERVICE_STATUS_NOT_INITIALIZED;
    }
    if (channelId >= CALIBRATION_CFG_MAX_CHANNELS)
    {
        return CALIBRATION_SERVICE_STATUS_INVALID_PARAM;
    }

    context.data[channelId].gain = CALIBRATION_CFG_DEFAULT_GAIN;
    context.data[channelId].offset = CALIBRATION_CFG_DEFAULT_OFFSET;
    context.data[channelId].valid = false;
    return CALIBRATION_SERVICE_STATUS_OK;
}

CalibrationService_Status_t CalibrationService_ClearAll(void)
{
    if (!context.initialized)
    {
        return CALIBRATION_SERVICE_STATUS_NOT_INITIALIZED;
    }
    for (uint8_t i = 0; i < CALIBRATION_CFG_MAX_CHANNELS; i++)
    {
        context.data[i].gain = CALIBRATION_CFG_DEFAULT_GAIN;
        context.data[i].offset = CALIBRATION_CFG_DEFAULT_OFFSET;
        context.data[i].valid = false;
    }
    return CALIBRATION_SERVICE_STATUS_OK;
}

CalibrationService_Status_t CalibrationService_Apply(uint8_t channelId, float inputValue, float *pOutputValue)
{
    if (!context.initialized)
    {
        return CALIBRATION_SERVICE_STATUS_NOT_INITIALIZED;
    }
    if (pOutputValue == NULL || channelId >= CALIBRATION_CFG_MAX_CHANNELS)
    {
        return CALIBRATION_SERVICE_STATUS_INVALID_PARAM;
    }

    CalibrationService_Data_t *pData = &context.data[channelId];
    float gain = pData->valid ? pData->gain : CALIBRATION_CFG_DEFAULT_GAIN;
    float offset = pData->valid ? pData->offset : CALIBRATION_CFG_DEFAULT_OFFSET;
    *pOutputValue = (inputValue + offset) * gain;
    return CALIBRATION_SERVICE_STATUS_OK;
}

CalibrationService_Status_t CalibrationService_ComputeTwoPoint(const CalibrationService_TwoPoint_t *pTwoPoint, CalibrationService_Data_t *pOutData)
{
    if (pTwoPoint == NULL || pOutData == NULL)
    {
        return CALIBRATION_SERVICE_STATUS_INVALID_PARAM;
    }
    float rawDelta = pTwoPoint->rawHigh - pTwoPoint->rawLow;
    if (rawDelta == 0.0f)
    {
        return CALIBRATION_SERVICE_STATUS_ERROR;
    }

    pOutData->gain = (pTwoPoint->actualHigh - pTwoPoint->actualLow) / rawDelta;
    pOutData->offset = pTwoPoint->actualLow - (pTwoPoint->rawLow * pOutData->gain);
    pOutData->valid = true;
    return CALIBRATION_SERVICE_STATUS_OK;
}

CalibrationService_Status_t CalibrationService_SaveToNvm(void)
{
    // TODO: Persist calibration data using NvmService
    return CALIBRATION_SERVICE_STATUS_OK;
}

CalibrationService_Status_t CalibrationService_LoadFromNvm(void)
{
    // TODO: Load calibration data using NvmService
    return CALIBRATION_SERVICE_STATUS_OK;
}
