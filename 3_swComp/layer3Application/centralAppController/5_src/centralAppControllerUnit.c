// CentralAppController Implementation - UDS Command Dispatcher

#include <stddef.h>
#include <string.h>
#include "centralAppController.h"
#include "comService.h"
#include "nvmService.h"
#include "analogService.h"
#include "digitalService.h"
#include "i2cService.h"
#include "spiService.h"
#include "deserialize.h"
#include "serialize.h"
#include "configService.h"

//============================================================================
// Frame Parser States
//============================================================================
typedef enum
{
    FRAME_PARSE_STATE_WAIT_PREFIX_HIGH = 0,
    FRAME_PARSE_STATE_WAIT_PREFIX_LOW,
    FRAME_PARSE_STATE_RECEIVE_PAYLOAD,
    FRAME_PARSE_STATE_FRAME_COMPLETE
} FrameParseState_t;

typedef struct
{
    FrameParseState_t state;
    uint8_t           frameBuffer[CENTRAL_APP_CFG_MAX_FRAME_SIZE];
    uint16_t          frameIndex;
    bool              frameReady;
} FrameParser_t;

typedef struct
{
    bool initialized;
    CentralAppController_State_t currentState;
    CentralAppController_ErrorCallback_t errorCallback;
    FrameParser_t parser;
} CentralAppController_Context_t;

static CentralAppController_Context_t context = {0};

/* Forward declarations for internal handlers */
static CentralAppController_Status_t HandleReadDataById(const Deserialize_UdsRequest_t *pReq, Serialize_UdsResponse_t *pResp);
static CentralAppController_Status_t HandleWriteDataById(const Deserialize_UdsRequest_t *pReq, Serialize_UdsResponse_t *pResp);
static CentralAppController_Status_t HandleRoutineControl(const Deserialize_UdsRequest_t *pReq, Serialize_UdsResponse_t *pResp);
static void FrameParser_Reset(FrameParser_t *pParser);
static void FrameParser_ProcessByte(FrameParser_t *pParser, uint8_t byte);
static void SendFramedResponse(const uint8_t *pData, uint16_t length);

CentralAppController_Status_t CentralAppControllerUnit_Init(void)
{
    /* Layer 2: Services (each service initializes its own L1 driver) */
    (void)ComServiceUnit_Init();
    (void)NvmServiceUnit_Init();
    (void)AnalogServiceUnit_Init();
    (void)DigitalServiceUnit_Init();
    (void)I2cServiceUnit_Init();
    (void)SpiServiceUnit_Init();
    (void)DeserializeUnit_Init();
    (void)SerializeUnit_Init();
    (void)ConfigServiceUnit_Init();

    FrameParser_Reset(&context.parser);

    context.initialized = true;
    context.currentState = CentralAppController_STATE_IDLE;
    context.errorCallback = NULL;
    return CENTRAL_APP_CONTROLLER_STATUS_OK;
}

CentralAppController_Status_t CentralAppControllerUnit_DeInit(void)
{
    /* Services (reverse order - each service deinits its own L1 driver) */
    (void)ConfigServiceUnit_DeInit();
    (void)SerializeUnit_DeInit();
    (void)DeserializeUnit_DeInit();
    (void)SpiServiceUnit_DeInit();
    (void)I2cServiceUnit_DeInit();
    (void)DigitalServiceUnit_DeInit();
    (void)AnalogServiceUnit_DeInit();
    (void)NvmServiceUnit_DeInit();
    (void)ComServiceUnit_DeInit();

    context.initialized = false;
    context.currentState = CentralAppController_STATE_IDLE;
    return CENTRAL_APP_CONTROLLER_STATUS_OK;
}

CentralAppController_Status_t CentralAppControllerUnit_Run(void)
{
    if (!context.initialized)
    {
        return CENTRAL_APP_CONTROLLER_STATUS_NOT_INITIALIZED;
    }

    /* Read available bytes from ComService and feed to frame parser */
    if (ComServiceUnit_IsRxDataAvailable())
    {
        uint8_t  rxBuf[CENTRAL_APP_CFG_MAX_FRAME_SIZE];
        uint16_t rxLen = 0U;

        if (ComServiceUnit_Read(rxBuf, sizeof(rxBuf), &rxLen) == COMSERVICE_STATUS_OK)
        {
            for (uint16_t i = 0U; i < rxLen; i++)
            {
                FrameParser_ProcessByte(&context.parser, rxBuf[i]);

                if (context.parser.frameReady)
                {
                    /* Complete frame received - dispatch UDS request */
                    uint8_t  responseBuffer[CENTRAL_APP_CFG_MAX_FRAME_SIZE];
                    uint16_t responseLength = 0U;

                    (void)CentralAppControllerUnit_Dispatch(
                        context.parser.frameBuffer,
                        context.parser.frameIndex,
                        responseBuffer,
                        sizeof(responseBuffer),
                        &responseLength);

                    /* Send framed response back */
                    if (responseLength > 0U)
                    {
                        SendFramedResponse(responseBuffer, responseLength);
                    }

                    FrameParser_Reset(&context.parser);
                }
            }
        }
    }

    return CENTRAL_APP_CONTROLLER_STATUS_OK;
}

CentralAppController_Status_t CentralAppControllerUnit_GetState(CentralAppController_State_t *pState)
{
    if (pState == NULL)
    {
        return CENTRAL_APP_CONTROLLER_STATUS_INVALID_PARAM;
    }
    *pState = context.currentState;
    return CENTRAL_APP_CONTROLLER_STATUS_OK;
}

CentralAppController_Status_t CentralAppControllerUnit_RegisterErrorCallback(CentralAppController_ErrorCallback_t callback)
{
    if (!context.initialized)
    {
        return CENTRAL_APP_CONTROLLER_STATUS_NOT_INITIALIZED;
    }
    context.errorCallback = callback;
    return CENTRAL_APP_CONTROLLER_STATUS_OK;
}

CentralAppController_Status_t CentralAppControllerUnit_Dispatch(
    const uint8_t *pRequestFrame,
    uint16_t requestLength,
    uint8_t *pResponseBuffer,
    uint16_t bufferSize,
    uint16_t *pResponseLength)
{
    if (!context.initialized)
    {
        return CENTRAL_APP_CONTROLLER_STATUS_NOT_INITIALIZED;
    }
    if (pRequestFrame == NULL || pResponseBuffer == NULL || pResponseLength == NULL)
    {
        return CENTRAL_APP_CONTROLLER_STATUS_INVALID_PARAM;
    }

    context.currentState = CentralAppController_STATE_PROCESSING;

    /* Parse UDS request */
    Deserialize_Frame_t frame = { pRequestFrame, requestLength };
    Deserialize_UdsRequest_t request = {0};
    Deserialize_Status_t dStatus = DeserializeUnit_Parse(&frame, &request);

    Serialize_UdsResponse_t response = {0};

    if (dStatus != DESERIALIZE_STATUS_OK)
    {
        /* Build negative response: serviceNotSupported or incorrectMessageLength */
        uint8_t nrc = (dStatus == DESERIALIZE_STATUS_UNSUPPORTED_SID)
            ? SERIALIZE_NRC_SERVICE_NOT_SUPPORTED
            : SERIALIZE_NRC_INCORRECT_MSG_LENGTH;
        uint8_t sid = (requestLength > 0U) ? pRequestFrame[0] : 0U;
        (void)SerializeUnit_BuildNegativeResponse(sid, nrc, &response);
        context.currentState = CentralAppController_STATE_ERROR;
        if (context.errorCallback != NULL)
        {
            context.errorCallback(nrc);
        }
    }
    else
    {
        CentralAppController_Status_t status;
        switch (request.sid)
        {
            case DESERIALIZE_SID_READ_DATA_BY_ID:
                status = HandleReadDataById(&request, &response);
                break;
            case DESERIALIZE_SID_WRITE_DATA_BY_ID:
                status = HandleWriteDataById(&request, &response);
                break;
            case DESERIALIZE_SID_ROUTINE_CONTROL:
                status = HandleRoutineControl(&request, &response);
                break;
            default:
                (void)SerializeUnit_BuildNegativeResponse(request.sid, SERIALIZE_NRC_SERVICE_NOT_SUPPORTED, &response);
                status = CENTRAL_APP_CONTROLLER_STATUS_ERROR;
                break;
        }
        context.currentState = (status == CENTRAL_APP_CONTROLLER_STATUS_OK)
            ? CentralAppController_STATE_IDLE
            : CentralAppController_STATE_ERROR;
    }

    /* Copy response to output buffer */
    if (response.length > bufferSize)
    {
        *pResponseLength = 0U;
        return CENTRAL_APP_CONTROLLER_STATUS_ERROR;
    }
    (void)memcpy(pResponseBuffer, response.buffer, response.length);
    *pResponseLength = response.length;

    return CENTRAL_APP_CONTROLLER_STATUS_OK;
}

/*============================================================================
 * SID 0x22 - ReadDataByIdentifier Handler
 *===========================================================================*/
static CentralAppController_Status_t HandleReadDataById(const Deserialize_UdsRequest_t *pReq, Serialize_UdsResponse_t *pResp)
{
    uint8_t data[32] = {0};
    uint16_t dataLen = 0U;

    switch (pReq->id)
    {
        case CAC_DID_ADC_SAMPLE_RATE:
        {
            ConfigService_AnalogChannelConfig_t cfg = {0};
            if (ConfigServiceUnit_GetAnalogChannelConfig(0U, &cfg) == CONFIG_SERVICE_STATUS_OK)
            {
                uint32_t rate = cfg.samplingFrequency;
                data[0] = (uint8_t)((rate >> 24U) & 0xFFU);
                data[1] = (uint8_t)((rate >> 16U) & 0xFFU);
                data[2] = (uint8_t)((rate >> 8U) & 0xFFU);
                data[3] = (uint8_t)(rate & 0xFFU);
                dataLen = 4U;
            }
            else
            {
                (void)SerializeUnit_BuildNegativeResponse(pReq->sid, SERIALIZE_NRC_CONDITIONS_NOT_CORRECT, pResp);
                return CENTRAL_APP_CONTROLLER_STATUS_ERROR;
            }
            break;
        }
        case CAC_DID_ADC_RESOLUTION:
        {
            ConfigService_AnalogChannelConfig_t cfg = {0};
            if (ConfigServiceUnit_GetAnalogChannelConfig(0U, &cfg) == CONFIG_SERVICE_STATUS_OK)
            {
                data[0] = cfg.resolutionBits;
                dataLen = 1U;
            }
            else
            {
                (void)SerializeUnit_BuildNegativeResponse(pReq->sid, SERIALIZE_NRC_CONDITIONS_NOT_CORRECT, pResp);
                return CENTRAL_APP_CONTROLLER_STATUS_ERROR;
            }
            break;
        }
        case CAC_DID_GPIO_CONFIG:
        {
            ConfigService_DigitalPinConfig_t cfg = {0};
            if (ConfigServiceUnit_GetDigitalPinConfig(0U, &cfg) == CONFIG_SERVICE_STATUS_OK)
            {
                data[0] = cfg.pinId;
                data[1] = cfg.direction;
                data[2] = cfg.initialState;
                dataLen = 3U;
            }
            else
            {
                (void)SerializeUnit_BuildNegativeResponse(pReq->sid, SERIALIZE_NRC_CONDITIONS_NOT_CORRECT, pResp);
                return CENTRAL_APP_CONTROLLER_STATUS_ERROR;
            }
            break;
        }
        case CAC_DID_PWM_CONFIG:
        {
            ConfigService_PwmConfig_t cfg = {0};
            if (ConfigServiceUnit_GetPwmConfig(0U, &cfg) == CONFIG_SERVICE_STATUS_OK)
            {
                data[0] = cfg.channelId;
                data[1] = (uint8_t)((cfg.frequency >> 24U) & 0xFFU);
                data[2] = (uint8_t)((cfg.frequency >> 16U) & 0xFFU);
                data[3] = (uint8_t)((cfg.frequency >> 8U) & 0xFFU);
                data[4] = (uint8_t)(cfg.frequency & 0xFFU);
                data[5] = (uint8_t)((cfg.dutyCycle >> 8U) & 0xFFU);
                data[6] = (uint8_t)(cfg.dutyCycle & 0xFFU);
                dataLen = 7U;
            }
            else
            {
                (void)SerializeUnit_BuildNegativeResponse(pReq->sid, SERIALIZE_NRC_CONDITIONS_NOT_CORRECT, pResp);
                return CENTRAL_APP_CONTROLLER_STATUS_ERROR;
            }
            break;
        }
        case CAC_DID_I2C_CONFIG:
        {
            ConfigService_I2cConfig_t cfg = {0};
            if (ConfigServiceUnit_GetI2cConfig(&cfg) == CONFIG_SERVICE_STATUS_OK)
            {
                data[0] = (uint8_t)((cfg.speed >> 24U) & 0xFFU);
                data[1] = (uint8_t)((cfg.speed >> 16U) & 0xFFU);
                data[2] = (uint8_t)((cfg.speed >> 8U) & 0xFFU);
                data[3] = (uint8_t)(cfg.speed & 0xFFU);
                data[4] = cfg.addressMode;
                data[5] = (uint8_t)((cfg.timeoutMs >> 8U) & 0xFFU);
                data[6] = (uint8_t)(cfg.timeoutMs & 0xFFU);
                dataLen = 7U;
            }
            else
            {
                (void)SerializeUnit_BuildNegativeResponse(pReq->sid, SERIALIZE_NRC_CONDITIONS_NOT_CORRECT, pResp);
                return CENTRAL_APP_CONTROLLER_STATUS_ERROR;
            }
            break;
        }
        case CAC_DID_SPI_CONFIG:
        {
            ConfigService_SpiConfig_t cfg = {0};
            if (ConfigServiceUnit_GetSpiConfig(&cfg) == CONFIG_SERVICE_STATUS_OK)
            {
                data[0] = (uint8_t)((cfg.clockSpeed >> 24U) & 0xFFU);
                data[1] = (uint8_t)((cfg.clockSpeed >> 16U) & 0xFFU);
                data[2] = (uint8_t)((cfg.clockSpeed >> 8U) & 0xFFU);
                data[3] = (uint8_t)(cfg.clockSpeed & 0xFFU);
                data[4] = cfg.mode;
                data[5] = cfg.bitOrder;
                dataLen = 6U;
            }
            else
            {
                (void)SerializeUnit_BuildNegativeResponse(pReq->sid, SERIALIZE_NRC_CONDITIONS_NOT_CORRECT, pResp);
                return CENTRAL_APP_CONTROLLER_STATUS_ERROR;
            }
            break;
        }
        case CAC_DID_SERIAL_CONFIG:
        {
            ConfigService_SerialConfig_t cfg = {0};
            if (ConfigServiceUnit_GetSerialConfig(&cfg) == CONFIG_SERVICE_STATUS_OK)
            {
                data[0] = (uint8_t)((cfg.baudrate >> 24U) & 0xFFU);
                data[1] = (uint8_t)((cfg.baudrate >> 16U) & 0xFFU);
                data[2] = (uint8_t)((cfg.baudrate >> 8U) & 0xFFU);
                data[3] = (uint8_t)(cfg.baudrate & 0xFFU);
                data[4] = cfg.dataBits;
                data[5] = cfg.stopBits;
                data[6] = cfg.parity;
                dataLen = 7U;
            }
            else
            {
                (void)SerializeUnit_BuildNegativeResponse(pReq->sid, SERIALIZE_NRC_CONDITIONS_NOT_CORRECT, pResp);
                return CENTRAL_APP_CONTROLLER_STATUS_ERROR;
            }
            break;
        }
        default:
            (void)SerializeUnit_BuildNegativeResponse(pReq->sid, SERIALIZE_NRC_REQUEST_OUT_OF_RANGE, pResp);
            return CENTRAL_APP_CONTROLLER_STATUS_ERROR;
    }

    (void)SerializeUnit_BuildReadResponse(pReq->id, data, dataLen, pResp);
    return CENTRAL_APP_CONTROLLER_STATUS_OK;
}

/*============================================================================
 * SID 0x2E - WriteDataByIdentifier Handler
 *===========================================================================*/
static CentralAppController_Status_t HandleWriteDataById(const Deserialize_UdsRequest_t *pReq, Serialize_UdsResponse_t *pResp)
{
    switch (pReq->id)
    {
        case CAC_DID_ADC_SAMPLE_RATE:
        {
            if (pReq->payloadLength < 4U)
            {
                (void)SerializeUnit_BuildNegativeResponse(pReq->sid, SERIALIZE_NRC_INCORRECT_MSG_LENGTH, pResp);
                return CENTRAL_APP_CONTROLLER_STATUS_ERROR;
            }
            ConfigService_AnalogChannelConfig_t cfg = {0};
            if (ConfigServiceUnit_GetAnalogChannelConfig(0U, &cfg) != CONFIG_SERVICE_STATUS_OK)
            {
                (void)SerializeUnit_BuildNegativeResponse(pReq->sid, SERIALIZE_NRC_CONDITIONS_NOT_CORRECT, pResp);
                return CENTRAL_APP_CONTROLLER_STATUS_ERROR;
            }
            cfg.samplingFrequency = ((uint32_t)pReq->pPayload[0] << 24U)
                                  | ((uint32_t)pReq->pPayload[1] << 16U)
                                  | ((uint32_t)pReq->pPayload[2] << 8U)
                                  | (uint32_t)pReq->pPayload[3];
            if (ConfigServiceUnit_SetAnalogChannelConfig(0U, &cfg) != CONFIG_SERVICE_STATUS_OK)
            {
                (void)SerializeUnit_BuildNegativeResponse(pReq->sid, SERIALIZE_NRC_REQUEST_OUT_OF_RANGE, pResp);
                return CENTRAL_APP_CONTROLLER_STATUS_ERROR;
            }
            break;
        }
        case CAC_DID_ADC_RESOLUTION:
        {
            if (pReq->payloadLength < 1U)
            {
                (void)SerializeUnit_BuildNegativeResponse(pReq->sid, SERIALIZE_NRC_INCORRECT_MSG_LENGTH, pResp);
                return CENTRAL_APP_CONTROLLER_STATUS_ERROR;
            }
            ConfigService_AnalogChannelConfig_t cfg = {0};
            if (ConfigServiceUnit_GetAnalogChannelConfig(0U, &cfg) != CONFIG_SERVICE_STATUS_OK)
            {
                (void)SerializeUnit_BuildNegativeResponse(pReq->sid, SERIALIZE_NRC_CONDITIONS_NOT_CORRECT, pResp);
                return CENTRAL_APP_CONTROLLER_STATUS_ERROR;
            }
            cfg.resolutionBits = pReq->pPayload[0];
            if (ConfigServiceUnit_SetAnalogChannelConfig(0U, &cfg) != CONFIG_SERVICE_STATUS_OK)
            {
                (void)SerializeUnit_BuildNegativeResponse(pReq->sid, SERIALIZE_NRC_REQUEST_OUT_OF_RANGE, pResp);
                return CENTRAL_APP_CONTROLLER_STATUS_ERROR;
            }
            break;
        }
        case CAC_DID_GPIO_CONFIG:
        {
            if (pReq->payloadLength < 3U)
            {
                (void)SerializeUnit_BuildNegativeResponse(pReq->sid, SERIALIZE_NRC_INCORRECT_MSG_LENGTH, pResp);
                return CENTRAL_APP_CONTROLLER_STATUS_ERROR;
            }
            ConfigService_DigitalPinConfig_t cfg = {0};
            cfg.pinId = pReq->pPayload[0];
            cfg.direction = pReq->pPayload[1];
            cfg.initialState = pReq->pPayload[2];
            if (ConfigServiceUnit_SetDigitalPinConfig(cfg.pinId, &cfg) != CONFIG_SERVICE_STATUS_OK)
            {
                (void)SerializeUnit_BuildNegativeResponse(pReq->sid, SERIALIZE_NRC_REQUEST_OUT_OF_RANGE, pResp);
                return CENTRAL_APP_CONTROLLER_STATUS_ERROR;
            }
            break;
        }
        case CAC_DID_PWM_CONFIG:
        {
            if (pReq->payloadLength < 7U)
            {
                (void)SerializeUnit_BuildNegativeResponse(pReq->sid, SERIALIZE_NRC_INCORRECT_MSG_LENGTH, pResp);
                return CENTRAL_APP_CONTROLLER_STATUS_ERROR;
            }
            ConfigService_PwmConfig_t cfg = {0};
            cfg.channelId = pReq->pPayload[0];
            cfg.frequency = ((uint32_t)pReq->pPayload[1] << 24U)
                          | ((uint32_t)pReq->pPayload[2] << 16U)
                          | ((uint32_t)pReq->pPayload[3] << 8U)
                          | (uint32_t)pReq->pPayload[4];
            cfg.dutyCycle = ((uint16_t)pReq->pPayload[5] << 8U)
                          | (uint16_t)pReq->pPayload[6];
            if (ConfigServiceUnit_SetPwmConfig(cfg.channelId, &cfg) != CONFIG_SERVICE_STATUS_OK)
            {
                (void)SerializeUnit_BuildNegativeResponse(pReq->sid, SERIALIZE_NRC_REQUEST_OUT_OF_RANGE, pResp);
                return CENTRAL_APP_CONTROLLER_STATUS_ERROR;
            }
            break;
        }
        case CAC_DID_I2C_CONFIG:
        {
            if (pReq->payloadLength < 7U)
            {
                (void)SerializeUnit_BuildNegativeResponse(pReq->sid, SERIALIZE_NRC_INCORRECT_MSG_LENGTH, pResp);
                return CENTRAL_APP_CONTROLLER_STATUS_ERROR;
            }
            ConfigService_I2cConfig_t cfg = {0};
            cfg.speed = ((uint32_t)pReq->pPayload[0] << 24U)
                      | ((uint32_t)pReq->pPayload[1] << 16U)
                      | ((uint32_t)pReq->pPayload[2] << 8U)
                      | (uint32_t)pReq->pPayload[3];
            cfg.addressMode = pReq->pPayload[4];
            cfg.timeoutMs = ((uint16_t)pReq->pPayload[5] << 8U)
                          | (uint16_t)pReq->pPayload[6];
            if (ConfigServiceUnit_SetI2cConfig(&cfg) != CONFIG_SERVICE_STATUS_OK)
            {
                (void)SerializeUnit_BuildNegativeResponse(pReq->sid, SERIALIZE_NRC_REQUEST_OUT_OF_RANGE, pResp);
                return CENTRAL_APP_CONTROLLER_STATUS_ERROR;
            }
            break;
        }
        case CAC_DID_SPI_CONFIG:
        {
            if (pReq->payloadLength < 6U)
            {
                (void)SerializeUnit_BuildNegativeResponse(pReq->sid, SERIALIZE_NRC_INCORRECT_MSG_LENGTH, pResp);
                return CENTRAL_APP_CONTROLLER_STATUS_ERROR;
            }
            ConfigService_SpiConfig_t cfg = {0};
            cfg.clockSpeed = ((uint32_t)pReq->pPayload[0] << 24U)
                           | ((uint32_t)pReq->pPayload[1] << 16U)
                           | ((uint32_t)pReq->pPayload[2] << 8U)
                           | (uint32_t)pReq->pPayload[3];
            cfg.mode = pReq->pPayload[4];
            cfg.bitOrder = pReq->pPayload[5];
            if (ConfigServiceUnit_SetSpiConfig(&cfg) != CONFIG_SERVICE_STATUS_OK)
            {
                (void)SerializeUnit_BuildNegativeResponse(pReq->sid, SERIALIZE_NRC_REQUEST_OUT_OF_RANGE, pResp);
                return CENTRAL_APP_CONTROLLER_STATUS_ERROR;
            }
            break;
        }
        case CAC_DID_SERIAL_CONFIG:
        {
            if (pReq->payloadLength < 7U)
            {
                (void)SerializeUnit_BuildNegativeResponse(pReq->sid, SERIALIZE_NRC_INCORRECT_MSG_LENGTH, pResp);
                return CENTRAL_APP_CONTROLLER_STATUS_ERROR;
            }
            ConfigService_SerialConfig_t cfg = {0};
            cfg.baudrate = ((uint32_t)pReq->pPayload[0] << 24U)
                         | ((uint32_t)pReq->pPayload[1] << 16U)
                         | ((uint32_t)pReq->pPayload[2] << 8U)
                         | (uint32_t)pReq->pPayload[3];
            cfg.dataBits = pReq->pPayload[4];
            cfg.stopBits = pReq->pPayload[5];
            cfg.parity = pReq->pPayload[6];
            if (ConfigServiceUnit_SetSerialConfig(&cfg) != CONFIG_SERVICE_STATUS_OK)
            {
                (void)SerializeUnit_BuildNegativeResponse(pReq->sid, SERIALIZE_NRC_REQUEST_OUT_OF_RANGE, pResp);
                return CENTRAL_APP_CONTROLLER_STATUS_ERROR;
            }
            break;
        }
        default:
            (void)SerializeUnit_BuildNegativeResponse(pReq->sid, SERIALIZE_NRC_REQUEST_OUT_OF_RANGE, pResp);
            return CENTRAL_APP_CONTROLLER_STATUS_ERROR;
    }

    (void)SerializeUnit_BuildWriteResponse(pReq->id, pResp);
    return CENTRAL_APP_CONTROLLER_STATUS_OK;
}

/*============================================================================
 * SID 0x31 - RoutineControl Handler
 *===========================================================================*/
static CentralAppController_Status_t HandleRoutineControl(const Deserialize_UdsRequest_t *pReq, Serialize_UdsResponse_t *pResp)
{
    uint8_t statusRecord[CENTRAL_APP_CFG_MAX_FRAME_SIZE];
    uint16_t statusLen = 0U;

    switch (pReq->id)
    {
        case CAC_RID_ADC_READ:
        {
            /* params[0] = channel */
            if (pReq->payloadLength < 1U)
            {
                (void)SerializeUnit_BuildNegativeResponse(pReq->sid, SERIALIZE_NRC_INCORRECT_MSG_LENGTH, pResp);
                return CENTRAL_APP_CONTROLLER_STATUS_ERROR;
            }
            uint8_t channel = pReq->pPayload[0];
            uint16_t rawValue = 0U;
            AnalogService_Status_t aStatus = AnalogServiceUnit_ReadAdc(channel, &rawValue);
            if (aStatus != ANALOGSERVICE_STATUS_OK)
            {
                (void)SerializeUnit_BuildNegativeResponse(pReq->sid, SERIALIZE_NRC_CONDITIONS_NOT_CORRECT, pResp);
                return CENTRAL_APP_CONTROLLER_STATUS_ERROR;
            }
            statusRecord[0] = (uint8_t)(rawValue >> 8U);
            statusRecord[1] = (uint8_t)(rawValue & 0xFFU);
            statusLen = 2U;
            break;
        }

        case CAC_RID_GPIO_WRITE:
        {
            /* params[0] = pin, params[1] = state */
            if (pReq->payloadLength < 2U)
            {
                (void)SerializeUnit_BuildNegativeResponse(pReq->sid, SERIALIZE_NRC_INCORRECT_MSG_LENGTH, pResp);
                return CENTRAL_APP_CONTROLLER_STATUS_ERROR;
            }
            uint8_t pin = pReq->pPayload[0];
            uint8_t state = pReq->pPayload[1];
            DigitalService_Status_t dStatus = DigitalServiceUnit_WriteGpio(pin, state);
            if (dStatus != DIGITALSERVICE_STATUS_OK)
            {
                (void)SerializeUnit_BuildNegativeResponse(pReq->sid, SERIALIZE_NRC_CONDITIONS_NOT_CORRECT, pResp);
                return CENTRAL_APP_CONTROLLER_STATUS_ERROR;
            }
            statusRecord[0] = 0x00U; /* success */
            statusLen = 1U;
            break;
        }

        case CAC_RID_GPIO_READ:
        {
            /* params[0] = pin */
            if (pReq->payloadLength < 1U)
            {
                (void)SerializeUnit_BuildNegativeResponse(pReq->sid, SERIALIZE_NRC_INCORRECT_MSG_LENGTH, pResp);
                return CENTRAL_APP_CONTROLLER_STATUS_ERROR;
            }
            uint8_t pin = pReq->pPayload[0];
            uint8_t pinState = 0U;
            DigitalService_Status_t dStatus = DigitalServiceUnit_ReadGpio(pin, &pinState);
            if (dStatus != DIGITALSERVICE_STATUS_OK)
            {
                (void)SerializeUnit_BuildNegativeResponse(pReq->sid, SERIALIZE_NRC_CONDITIONS_NOT_CORRECT, pResp);
                return CENTRAL_APP_CONTROLLER_STATUS_ERROR;
            }
            statusRecord[0] = pinState;
            statusLen = 1U;
            break;
        }

        case CAC_RID_PWM_START:
        {
            /* params[0] = channel */
            if (pReq->payloadLength < 1U)
            {
                (void)SerializeUnit_BuildNegativeResponse(pReq->sid, SERIALIZE_NRC_INCORRECT_MSG_LENGTH, pResp);
                return CENTRAL_APP_CONTROLLER_STATUS_ERROR;
            }
            uint8_t channel = pReq->pPayload[0];
            DigitalService_Status_t dStatus = DigitalServiceUnit_StartPwm(channel);
            if (dStatus != DIGITALSERVICE_STATUS_OK)
            {
                (void)SerializeUnit_BuildNegativeResponse(pReq->sid, SERIALIZE_NRC_CONDITIONS_NOT_CORRECT, pResp);
                return CENTRAL_APP_CONTROLLER_STATUS_ERROR;
            }
            statusRecord[0] = 0x00U;
            statusLen = 1U;
            break;
        }

        case CAC_RID_PWM_STOP:
        {
            /* params[0] = channel */
            if (pReq->payloadLength < 1U)
            {
                (void)SerializeUnit_BuildNegativeResponse(pReq->sid, SERIALIZE_NRC_INCORRECT_MSG_LENGTH, pResp);
                return CENTRAL_APP_CONTROLLER_STATUS_ERROR;
            }
            uint8_t channel = pReq->pPayload[0];
            DigitalService_Status_t dStatus = DigitalServiceUnit_StopPwm(channel);
            if (dStatus != DIGITALSERVICE_STATUS_OK)
            {
                (void)SerializeUnit_BuildNegativeResponse(pReq->sid, SERIALIZE_NRC_CONDITIONS_NOT_CORRECT, pResp);
                return CENTRAL_APP_CONTROLLER_STATUS_ERROR;
            }
            statusRecord[0] = 0x00U;
            statusLen = 1U;
            break;
        }

        case CAC_RID_I2C_WRITE:
        {
            /* params[0] = addr, params[1..N] = data */
            if (pReq->payloadLength < 2U)
            {
                (void)SerializeUnit_BuildNegativeResponse(pReq->sid, SERIALIZE_NRC_INCORRECT_MSG_LENGTH, pResp);
                return CENTRAL_APP_CONTROLLER_STATUS_ERROR;
            }
            uint16_t addr = (uint16_t)pReq->pPayload[0];
            const uint8_t *pData = &pReq->pPayload[1];
            uint16_t len = pReq->payloadLength - 1U;
            I2cService_Status_t iStatus = I2cServiceUnit_Write(addr, pData, len);
            if (iStatus != I2CSERVICE_STATUS_OK)
            {
                (void)SerializeUnit_BuildNegativeResponse(pReq->sid, SERIALIZE_NRC_CONDITIONS_NOT_CORRECT, pResp);
                return CENTRAL_APP_CONTROLLER_STATUS_ERROR;
            }
            statusRecord[0] = 0x00U;
            statusLen = 1U;
            break;
        }

        case CAC_RID_I2C_READ:
        {
            /* params[0] = addr, params[1] = length */
            if (pReq->payloadLength < 2U)
            {
                (void)SerializeUnit_BuildNegativeResponse(pReq->sid, SERIALIZE_NRC_INCORRECT_MSG_LENGTH, pResp);
                return CENTRAL_APP_CONTROLLER_STATUS_ERROR;
            }
            uint16_t addr = (uint16_t)pReq->pPayload[0];
            uint16_t readLen = (uint16_t)pReq->pPayload[1];
            if (readLen > sizeof(statusRecord))
            {
                (void)SerializeUnit_BuildNegativeResponse(pReq->sid, SERIALIZE_NRC_REQUEST_OUT_OF_RANGE, pResp);
                return CENTRAL_APP_CONTROLLER_STATUS_ERROR;
            }
            I2cService_Status_t iStatus = I2cServiceUnit_Read(addr, statusRecord, readLen);
            if (iStatus != I2CSERVICE_STATUS_OK)
            {
                (void)SerializeUnit_BuildNegativeResponse(pReq->sid, SERIALIZE_NRC_CONDITIONS_NOT_CORRECT, pResp);
                return CENTRAL_APP_CONTROLLER_STATUS_ERROR;
            }
            statusLen = readLen;
            break;
        }

        case CAC_RID_SPI_WRITE:
        {
            /* params[0] = dev, params[1..N] = data */
            if (pReq->payloadLength < 2U)
            {
                (void)SerializeUnit_BuildNegativeResponse(pReq->sid, SERIALIZE_NRC_INCORRECT_MSG_LENGTH, pResp);
                return CENTRAL_APP_CONTROLLER_STATUS_ERROR;
            }
            uint8_t dev = pReq->pPayload[0];
            const uint8_t *pData = &pReq->pPayload[1];
            uint16_t len = pReq->payloadLength - 1U;
            SpiService_Status_t sStatus = SpiServiceUnit_Write(dev, pData, len);
            if (sStatus != SPISERVICE_STATUS_OK)
            {
                (void)SerializeUnit_BuildNegativeResponse(pReq->sid, SERIALIZE_NRC_CONDITIONS_NOT_CORRECT, pResp);
                return CENTRAL_APP_CONTROLLER_STATUS_ERROR;
            }
            statusRecord[0] = 0x00U;
            statusLen = 1U;
            break;
        }

        case CAC_RID_SPI_TRANSCEIVE:
        {
            /* params[0] = dev, params[1] = rx_len, params[2..N] = tx_data */
            if (pReq->payloadLength < 3U)
            {
                (void)SerializeUnit_BuildNegativeResponse(pReq->sid, SERIALIZE_NRC_INCORRECT_MSG_LENGTH, pResp);
                return CENTRAL_APP_CONTROLLER_STATUS_ERROR;
            }
            uint8_t dev = pReq->pPayload[0];
            uint16_t rxLen = (uint16_t)pReq->pPayload[1];
            const uint8_t *pTx = &pReq->pPayload[2];
            uint16_t txLen = pReq->payloadLength - 2U;
            if (rxLen > sizeof(statusRecord))
            {
                (void)SerializeUnit_BuildNegativeResponse(pReq->sid, SERIALIZE_NRC_REQUEST_OUT_OF_RANGE, pResp);
                return CENTRAL_APP_CONTROLLER_STATUS_ERROR;
            }
            SpiService_Status_t sStatus = SpiServiceUnit_Transceive(dev, pTx, txLen, statusRecord, rxLen);
            if (sStatus != SPISERVICE_STATUS_OK)
            {
                (void)SerializeUnit_BuildNegativeResponse(pReq->sid, SERIALIZE_NRC_CONDITIONS_NOT_CORRECT, pResp);
                return CENTRAL_APP_CONTROLLER_STATUS_ERROR;
            }
            statusLen = rxLen;
            break;
        }

        default:
            (void)SerializeUnit_BuildNegativeResponse(pReq->sid, SERIALIZE_NRC_REQUEST_OUT_OF_RANGE, pResp);
            return CENTRAL_APP_CONTROLLER_STATUS_ERROR;
    }

    (void)SerializeUnit_BuildRoutineResponse(pReq->routineControlType, pReq->id, statusRecord, statusLen, pResp);
    return CENTRAL_APP_CONTROLLER_STATUS_OK;
}

/*============================================================================
 * Frame Parser - Extracts UDS frames from serial byte stream
 * Frame format: [PREFIX_HIGH][PREFIX_LOW][payload...][POSTFIX_HIGH][POSTFIX_LOW]
 *===========================================================================*/
static void FrameParser_Reset(FrameParser_t *pParser)
{
    pParser->state = FRAME_PARSE_STATE_WAIT_PREFIX_HIGH;
    pParser->frameIndex = 0U;
    pParser->frameReady = false;
}

static void FrameParser_ProcessByte(FrameParser_t *pParser, uint8_t byte)
{
    switch (pParser->state)
    {
        case FRAME_PARSE_STATE_WAIT_PREFIX_HIGH:
            if (byte == CENTRAL_APP_CFG_FRAME_PREFIX_HIGH)
            {
                pParser->state = FRAME_PARSE_STATE_WAIT_PREFIX_LOW;
            }
            break;

        case FRAME_PARSE_STATE_WAIT_PREFIX_LOW:
            if (byte == CENTRAL_APP_CFG_FRAME_PREFIX_LOW)
            {
                /* Full prefix detected, start collecting payload */
                pParser->state = FRAME_PARSE_STATE_RECEIVE_PAYLOAD;
                pParser->frameIndex = 0U;
            }
            else if (byte == CENTRAL_APP_CFG_FRAME_PREFIX_HIGH)
            {
                /* Could be start of a new prefix, stay in this state */
                pParser->state = FRAME_PARSE_STATE_WAIT_PREFIX_LOW;
            }
            else
            {
                /* Not a valid prefix, go back to waiting */
                pParser->state = FRAME_PARSE_STATE_WAIT_PREFIX_HIGH;
            }
            break;

        case FRAME_PARSE_STATE_RECEIVE_PAYLOAD:
            /* Check for postfix pattern */
            if ((pParser->frameIndex >= 1U) &&
                (pParser->frameBuffer[pParser->frameIndex - 1U] == CENTRAL_APP_CFG_FRAME_POSTFIX_HIGH) &&
                (byte == CENTRAL_APP_CFG_FRAME_POSTFIX_LOW))
            {
                /* Postfix detected - remove the postfix high byte from payload */
                pParser->frameIndex -= 1U;
                pParser->frameReady = true;
                pParser->state = FRAME_PARSE_STATE_FRAME_COMPLETE;
            }
            else
            {
                /* Store payload byte */
                if (pParser->frameIndex < CENTRAL_APP_CFG_MAX_FRAME_SIZE)
                {
                    pParser->frameBuffer[pParser->frameIndex] = byte;
                    pParser->frameIndex++;
                }
                else
                {
                    /* Buffer overflow - discard frame and resync */
                    FrameParser_Reset(pParser);
                }
            }
            break;

        case FRAME_PARSE_STATE_FRAME_COMPLETE:
            /* Waiting for caller to process and reset */
            break;

        default:
            FrameParser_Reset(pParser);
            break;
    }
}

/*============================================================================
 * SendFramedResponse - Wraps response with prefix/postfix and sends via ComService
 *===========================================================================*/
static void SendFramedResponse(const uint8_t *pData, uint16_t length)
{
    uint8_t framedBuffer[CENTRAL_APP_CFG_MAX_FRAME_SIZE + (2U * CENTRAL_APP_CFG_FRAME_DELIMITER_SIZE)];
    uint16_t totalLength = length + (2U * CENTRAL_APP_CFG_FRAME_DELIMITER_SIZE);

    if (totalLength > sizeof(framedBuffer))
    {
        return;
    }

    /* Prefix */
    framedBuffer[0] = CENTRAL_APP_CFG_FRAME_PREFIX_HIGH;
    framedBuffer[1] = CENTRAL_APP_CFG_FRAME_PREFIX_LOW;

    /* Payload */
    (void)memcpy(&framedBuffer[CENTRAL_APP_CFG_FRAME_DELIMITER_SIZE], pData, length);

    /* Postfix */
    framedBuffer[CENTRAL_APP_CFG_FRAME_DELIMITER_SIZE + length]      = CENTRAL_APP_CFG_FRAME_POSTFIX_HIGH;
    framedBuffer[CENTRAL_APP_CFG_FRAME_DELIMITER_SIZE + length + 1U] = CENTRAL_APP_CFG_FRAME_POSTFIX_LOW;

    (void)ComServiceUnit_Write(framedBuffer, totalLength);
}