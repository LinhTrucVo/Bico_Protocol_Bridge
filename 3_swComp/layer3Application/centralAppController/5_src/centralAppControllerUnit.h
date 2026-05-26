#ifndef CENTRAL_APP_CONTROLLERUNIT_H
#define CENTRAL_APP_CONTROLLERUNIT_H
#include <stdint.h>
#include <stdbool.h>
#include "centralAppControllerCfg.h"

//============================================================================
// Configuration Macros
//============================================================================
#define CENTRAL_APP_CFG_MAX_FRAME_SIZE      256U
#define CENTRAL_APP_CFG_RESPONSE_TIMEOUT_MS 10U

//============================================================================
// DID Definitions (Configuration Parameters)
//============================================================================
#define CAC_DID_ADC_SAMPLE_RATE       0x1001U
#define CAC_DID_ADC_RESOLUTION        0x1002U
#define CAC_DID_GPIO_CONFIG           0x2001U
#define CAC_DID_PWM_CONFIG            0x3001U
#define CAC_DID_I2C_CONFIG            0x4001U
#define CAC_DID_SPI_CONFIG            0x5001U
#define CAC_DID_SERIAL_CONFIG         0x6001U

//============================================================================
// RID Definitions (Peripheral Control)
//============================================================================
#define CAC_RID_ADC_READ              0x0100U
#define CAC_RID_GPIO_WRITE            0x0200U
#define CAC_RID_GPIO_READ             0x0201U
#define CAC_RID_PWM_START             0x0300U
#define CAC_RID_PWM_STOP              0x0301U
#define CAC_RID_I2C_WRITE             0x0400U
#define CAC_RID_I2C_READ              0x0401U
#define CAC_RID_SPI_WRITE             0x0500U
#define CAC_RID_SPI_TRANSCEIVE        0x0501U

//============================================================================
// Type Definitions
//============================================================================
typedef enum
{
    CentralAppController_STATE_IDLE = 0,
    CentralAppController_STATE_PROCESSING,
    CentralAppController_STATE_ERROR
} CentralAppController_State_t;

typedef enum
{
    CENTRAL_APP_CONTROLLER_STATUS_OK = 0,
    CENTRAL_APP_CONTROLLER_STATUS_ERROR,
    CENTRAL_APP_CONTROLLER_STATUS_INVALID_PARAM,
    CENTRAL_APP_CONTROLLER_STATUS_TIMEOUT,
    CENTRAL_APP_CONTROLLER_STATUS_NOT_INITIALIZED
} CentralAppController_Status_t;

typedef void (*CentralAppController_ErrorCallback_t)(uint8_t errorCode);

//============================================================================
// Public Functions
//============================================================================
CentralAppController_Status_t CentralAppControllerUnit_Init(void);
CentralAppController_Status_t CentralAppControllerUnit_DeInit(void);
CentralAppController_Status_t CentralAppControllerUnit_Run(void);
CentralAppController_Status_t CentralAppControllerUnit_GetState(CentralAppController_State_t *pState);
CentralAppController_Status_t CentralAppControllerUnit_Dispatch(const uint8_t *pRequestFrame, uint16_t requestLength, uint8_t *pResponseBuffer, uint16_t bufferSize, uint16_t *pResponseLength);
CentralAppController_Status_t CentralAppControllerUnit_RegisterErrorCallback(CentralAppController_ErrorCallback_t callback);

#endif /* CENTRAL_APP_CONTROLLERUNIT_H */