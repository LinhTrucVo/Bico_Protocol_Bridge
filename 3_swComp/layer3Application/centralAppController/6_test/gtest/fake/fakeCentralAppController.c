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
 * Fake ConfigService - include actual implementation
 * (In-memory store, no HW dependencies, suitable for testing)
 * ============================================================ */
#include "configServiceUnit.c"

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