// DataConversionService Implementation

#include "dataConversionService.h"
#include "dataConversionServiceCfg.h"

typedef struct
{
    bool initialized;
    DataConversionService_ChannelConfig_t config[DATA_CONVERSION_CFG_MAX_CHANNELS];
} DataConversionService_Context_t;

static DataConversionService_Context_t context = {0};

DataConversionService_Status_t DataConversionService_Init(void)
{
    context.initialized = true;
    for (uint8_t i = 0; i < DATA_CONVERSION_CFG_MAX_CHANNELS; i++)
    {
        context.config[i].resolutionBits = DATA_CONVERSION_CFG_DEFAULT_RES;
        context.config[i].vRef = DATA_CONVERSION_CFG_DEFAULT_VREF;
        context.config[i].scale = DATA_CONVERSION_CFG_DEFAULT_SCALE;
        context.config[i].offset = DATA_CONVERSION_CFG_DEFAULT_OFFSET;
        context.config[i].unit = DATA_CONVERSION_UNIT_VOLT;
    }
    return DATA_CONVERSION_SERVICE_STATUS_OK;
}

DataConversionService_Status_t DataConversionService_DeInit(void)
{
    context.initialized = false;
    return DATA_CONVERSION_SERVICE_STATUS_OK;
}

DataConversionService_Status_t DataConversionService_SetChannelConfig(uint8_t channelId, const DataConversionService_ChannelConfig_t *pConfig)
{
    if (!context.initialized)
    {
        return DATA_CONVERSION_SERVICE_STATUS_NOT_INITIALIZED;
    }
    if (pConfig == NULL || channelId >= DATA_CONVERSION_CFG_MAX_CHANNELS)
    {
        return DATA_CONVERSION_SERVICE_STATUS_INVALID_PARAM;
    }
    context.config[channelId] = *pConfig;
    return DATA_CONVERSION_SERVICE_STATUS_OK;
}

DataConversionService_Status_t DataConversionService_GetChannelConfig(uint8_t channelId, DataConversionService_ChannelConfig_t *pConfig)
{
    if (!context.initialized)
    {
        return DATA_CONVERSION_SERVICE_STATUS_NOT_INITIALIZED;
    }
    if (pConfig == NULL || channelId >= DATA_CONVERSION_CFG_MAX_CHANNELS)
    {
        return DATA_CONVERSION_SERVICE_STATUS_INVALID_PARAM;
    }
    *pConfig = context.config[channelId];
    return DATA_CONVERSION_SERVICE_STATUS_OK;
}

DataConversionService_Status_t DataConversionService_ConvertRawToVoltage(uint16_t rawValue, uint16_t resolutionBits, float vRef, float *pVoltage)
{
    if (pVoltage == NULL || resolutionBits == 0)
    {
        return DATA_CONVERSION_SERVICE_STATUS_INVALID_PARAM;
    }
    uint32_t maxValue = (1U << resolutionBits) - 1U;
    *pVoltage = ((float)rawValue / (float)maxValue) * vRef;
    return DATA_CONVERSION_SERVICE_STATUS_OK;
}

DataConversionService_Status_t DataConversionService_Convert(uint8_t channelId, uint16_t rawValue, float *pValue)
{
    if (!context.initialized)
    {
        return DATA_CONVERSION_SERVICE_STATUS_NOT_INITIALIZED;
    }
    if (pValue == NULL || channelId >= DATA_CONVERSION_CFG_MAX_CHANNELS)
    {
        return DATA_CONVERSION_SERVICE_STATUS_INVALID_PARAM;
    }

    DataConversionService_ChannelConfig_t *cfg = &context.config[channelId];
    float voltage = 0.0f;
    (void)DataConversionService_ConvertRawToVoltage(rawValue, cfg->resolutionBits, cfg->vRef, &voltage);
    float value = (voltage * cfg->scale) + cfg->offset;

    switch (cfg->unit)
    {
        case DATA_CONVERSION_UNIT_MILLIVOLT:
            value *= 1000.0f;
            break;
        case DATA_CONVERSION_UNIT_PERCENT:
            value = (value / cfg->vRef) * 100.0f;
            break;
        case DATA_CONVERSION_UNIT_RAW:
        default:
            value = (float)rawValue;
            break;
    }

    *pValue = value;
    return DATA_CONVERSION_SERVICE_STATUS_OK;
}
