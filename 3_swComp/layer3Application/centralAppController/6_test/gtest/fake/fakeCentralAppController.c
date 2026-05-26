// Fake implementations for CentralAppController testing
// Provides all dependency fakes: Deserialize, Serialize, ConfigService, peripheral apps

#include <stddef.h>
#include <string.h>
#include "fakeCentralAppController.h"
#include "deserialize.h"
#include "serialize.h"
#include "configService.h"
#include "serialToAnalogApp.h"
#include "serialToDigitalApp.h"
#include "serialToI2CApp.h"
#include "serialToSPIApp.h"

/* ============================================================
 * Fake Deserialize - include actual implementation
 * ============================================================ */
#include "deserializeUnit.c"

/* ============================================================
 * Fake Serialize - include actual implementation
 * ============================================================ */
#include "serializeUnit.c"

/* ============================================================
 * Fake ConfigService
 * ============================================================ */
static uint32_t fake_adcSampleRate = 1000U;
static uint8_t fake_adcResolution = 12U;

ConfigService_Status_t ConfigServiceUnit_Init(void) { return CONFIG_SERVICE_STATUS_OK; }
ConfigService_Status_t ConfigServiceUnit_GetAnalogSampleRate(uint32_t *pRate)
{
    if (pRate == NULL) return CONFIG_SERVICE_STATUS_INVALID_PARAM;
    *pRate = fake_adcSampleRate;
    return CONFIG_SERVICE_STATUS_OK;
}
ConfigService_Status_t ConfigServiceUnit_SetAnalogSampleRate(uint32_t rate)
{
    if (rate < 1U || rate > 10000U) return CONFIG_SERVICE_STATUS_INVALID_PARAM;
    fake_adcSampleRate = rate;
    return CONFIG_SERVICE_STATUS_OK;
}
ConfigService_Status_t ConfigServiceUnit_GetAnalogResolution(uint8_t *pRes)
{
    if (pRes == NULL) return CONFIG_SERVICE_STATUS_INVALID_PARAM;
    *pRes = fake_adcResolution;
    return CONFIG_SERVICE_STATUS_OK;
}
ConfigService_Status_t ConfigServiceUnit_SetAnalogResolution(uint8_t res)
{
    if (res != 8U && res != 10U && res != 12U && res != 16U) return CONFIG_SERVICE_STATUS_INVALID_PARAM;
    fake_adcResolution = res;
    return CONFIG_SERVICE_STATUS_OK;
}

/* ============================================================
 * Fake SerialToAnalogApp
 * ============================================================ */
SerialToAnalogApp_Status_t SerialToAnalogApp_Init(void) { return SERIAL_TO_ANALOG_APP_STATUS_OK; }
SerialToAnalogApp_Status_t SerialToAnalogApp_ReadAdc(uint8_t channel, uint16_t *pRawValue)
{
    if (pRawValue == NULL || channel >= 8U) return SERIAL_TO_ANALOG_APP_STATUS_INVALID_PARAM;
    *pRawValue = 2048U; /* Fake ADC value */
    return SERIAL_TO_ANALOG_APP_STATUS_OK;
}

/* ============================================================
 * Fake SerialToDigitalApp
 * ============================================================ */
static uint8_t fake_pinStates[32] = {0};

SerialToDigitalApp_Status_t SerialToDigitalApp_Init(void) { return SERIAL_TO_DIGITAL_APP_STATUS_OK; }
SerialToDigitalApp_Status_t SerialToDigitalApp_WriteGpio(uint8_t pin, uint8_t state)
{
    if (pin >= 32U) return SERIAL_TO_DIGITAL_APP_STATUS_INVALID_PARAM;
    fake_pinStates[pin] = state;
    return SERIAL_TO_DIGITAL_APP_STATUS_OK;
}
SerialToDigitalApp_Status_t SerialToDigitalApp_ReadGpio(uint8_t pin, uint8_t *pState)
{
    if (pState == NULL || pin >= 32U) return SERIAL_TO_DIGITAL_APP_STATUS_INVALID_PARAM;
    *pState = fake_pinStates[pin];
    return SERIAL_TO_DIGITAL_APP_STATUS_OK;
}
SerialToDigitalApp_Status_t SerialToDigitalApp_StartPwm(uint8_t channel)
{
    if (channel >= 8U) return SERIAL_TO_DIGITAL_APP_STATUS_INVALID_PARAM;
    return SERIAL_TO_DIGITAL_APP_STATUS_OK;
}
SerialToDigitalApp_Status_t SerialToDigitalApp_StopPwm(uint8_t channel)
{
    if (channel >= 8U) return SERIAL_TO_DIGITAL_APP_STATUS_INVALID_PARAM;
    return SERIAL_TO_DIGITAL_APP_STATUS_OK;
}

/* ============================================================
 * Fake SerialToI2CApp
 * ============================================================ */
SerialToI2CApp_Status_t SerialToI2CApp_Init(void) { return SERIAL_TO_I2C_APP_STATUS_OK; }
SerialToI2CApp_Status_t SerialToI2CApp_Write(uint16_t address, const uint8_t *pData, uint16_t length)
{
    if (pData == NULL || length == 0U) return SERIAL_TO_I2C_APP_STATUS_INVALID_PARAM;
    (void)address;
    return SERIAL_TO_I2C_APP_STATUS_OK;
}
SerialToI2CApp_Status_t SerialToI2CApp_Read(uint16_t address, uint8_t *pData, uint16_t length)
{
    if (pData == NULL || length == 0U) return SERIAL_TO_I2C_APP_STATUS_INVALID_PARAM;
    (void)address;
    memset(pData, 0xAA, length);
    return SERIAL_TO_I2C_APP_STATUS_OK;
}

/* ============================================================
 * Fake SerialToSPIApp
 * ============================================================ */
SerialToSPIApp_Status_t SerialToSPIApp_Init(void) { return SERIAL_TO_SPI_APP_STATUS_OK; }
SerialToSPIApp_Status_t SerialToSPIApp_Write(uint8_t device, const uint8_t *pData, uint16_t length)
{
    if (pData == NULL || length == 0U) return SERIAL_TO_SPI_APP_STATUS_INVALID_PARAM;
    (void)device;
    return SERIAL_TO_SPI_APP_STATUS_OK;
}
SerialToSPIApp_Status_t SerialToSPIApp_Transceive(uint8_t device, const uint8_t *pTxData, uint16_t txLength, uint8_t *pRxData, uint16_t rxLength)
{
    if (pTxData == NULL || pRxData == NULL || txLength == 0U || rxLength == 0U)
        return SERIAL_TO_SPI_APP_STATUS_INVALID_PARAM;
    (void)device;
    memset(pRxData, 0xEF, rxLength);
    return SERIAL_TO_SPI_APP_STATUS_OK;
}