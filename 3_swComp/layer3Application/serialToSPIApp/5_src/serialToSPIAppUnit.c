// SerialToSPIApp Implementation

#include <stddef.h>
#include "serialToSPIApp.h"
#include "serialToSPIAppCfg.h"

typedef struct
{
    bool initialized;
    SerialToSPIApp_State_t currentState;
    SerialToSPIApp_Config_t config;
} SerialToSPIApp_Context_t;

static SerialToSPIApp_Context_t context = {0};

SerialToSPIApp_Status_t SerialToSPIApp_Init(void)
{
    context.initialized = true;
    context.currentState = SerialToSPIApp_STATE_IDLE;
    context.config.clockSpeed = SERIAL_TO_SPI_CFG_DEFAULT_SPEED;
    context.config.mode = SERIAL_TO_SPI_MODE_0;
    context.config.bitOrder = SERIAL_TO_SPI_BITORDER_MSB_FIRST;
    return SERIAL_TO_SPI_APP_STATUS_OK;
}

SerialToSPIApp_Status_t SerialToSPIApp_DeInit(void)
{
    context.initialized = false;
    context.currentState = SerialToSPIApp_STATE_IDLE;
    return SERIAL_TO_SPI_APP_STATUS_OK;
}

SerialToSPIApp_Status_t SerialToSPIApp_Run(void)
{
    if (!context.initialized)
    {
        return SERIAL_TO_SPI_APP_STATUS_NOT_INITIALIZED;
    }
    return SERIAL_TO_SPI_APP_STATUS_OK;
}

SerialToSPIApp_Status_t SerialToSPIApp_GetState(SerialToSPIApp_State_t *pState)
{
    if (pState == NULL)
    {
        return SERIAL_TO_SPI_APP_STATUS_INVALID_PARAM;
    }
    *pState = context.currentState;
    return SERIAL_TO_SPI_APP_STATUS_OK;
}

SerialToSPIApp_Status_t SerialToSPIApp_Configure(const SerialToSPIApp_Config_t *pConfig)
{
    if (pConfig == NULL)
    {
        return SERIAL_TO_SPI_APP_STATUS_INVALID_PARAM;
    }
    context.config = *pConfig;
    return SERIAL_TO_SPI_APP_STATUS_OK;
}

SerialToSPIApp_Status_t SerialToSPIApp_GetConfig(SerialToSPIApp_Config_t *pConfig)
{
    if (pConfig == NULL)
    {
        return SERIAL_TO_SPI_APP_STATUS_INVALID_PARAM;
    }
    *pConfig = context.config;
    return SERIAL_TO_SPI_APP_STATUS_OK;
}

SerialToSPIApp_Status_t SerialToSPIApp_Transfer(const SerialToSPIApp_Transfer_t *pTransfer)
{
    if (pTransfer == NULL || pTransfer->length == 0 || pTransfer->length > SERIAL_TO_SPI_CFG_MAX_TRANSFER)
    {
        return SERIAL_TO_SPI_APP_STATUS_INVALID_PARAM;
    }
    if (pTransfer->pRxData != NULL)
    {
        for (uint16_t i = 0; i < pTransfer->length; i++)
        {
            pTransfer->pRxData[i] = 0;
        }
    }
    return SERIAL_TO_SPI_APP_STATUS_OK;
}

SerialToSPIApp_Status_t SerialToSPIApp_SaveConfig(void)
{
    // TODO: Persist configuration using NvmService
    return SERIAL_TO_SPI_APP_STATUS_OK;
}

SerialToSPIApp_Status_t SerialToSPIApp_LoadConfig(void)
{
    // TODO: Load configuration using NvmService
    return SERIAL_TO_SPI_APP_STATUS_OK;
}

SerialToSPIApp_Status_t SerialToSPIApp_ProcessFrame(const uint8_t *pFrame, uint16_t frameLength, uint8_t *pResponse, uint16_t *pResponseLength)
{
    (void)pFrame;
    (void)frameLength;
    (void)pResponse;
    (void)pResponseLength;
    return SERIAL_TO_SPI_APP_STATUS_OK;
}
