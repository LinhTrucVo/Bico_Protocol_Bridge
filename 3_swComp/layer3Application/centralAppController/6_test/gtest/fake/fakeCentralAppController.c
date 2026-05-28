// Fake implementations for CentralAppController testing
// Provides all dependency fakes: Deserialize, Serialize, ConfigService, peripheral apps

#include <stddef.h>
#include <string.h>
#include "fakeCentralAppController.h"
#include "deserialize.h"
#include "serialize.h"
#include "configService.h"
#include "ANALOGAPP.h"
#include "DIGITALAPP.h"
#include "I2CAPP.h"
#include "SPIAPP.h"

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
 * Fake ANALOGAPP
 * ============================================================ */
ANALOGAPP_Status_t ANALOGAPP_Init(void) { return ANALOG_APP_STATUS_OK; }
ANALOGAPP_Status_t ANALOGAPP_ReadAdc(uint8_t channel, uint16_t *pRawValue)
{
    if (pRawValue == NULL || channel >= 8U) return ANALOG_APP_STATUS_INVALID_PARAM;
    *pRawValue = 2048U; /* Fake ADC value */
    return ANALOG_APP_STATUS_OK;
}

/* ============================================================
 * Fake DIGITALAPP
 * ============================================================ */
static uint8_t fake_pinStates[32] = {0};

DIGITALAPP_Status_t DIGITALAPP_Init(void) { return DIGITAL_APP_STATUS_OK; }
DIGITALAPP_Status_t DIGITALAPP_WriteGpio(uint8_t pin, uint8_t state)
{
    if (pin >= 32U) return DIGITAL_APP_STATUS_INVALID_PARAM;
    fake_pinStates[pin] = state;
    return DIGITAL_APP_STATUS_OK;
}
DIGITALAPP_Status_t DIGITALAPP_ReadGpio(uint8_t pin, uint8_t *pState)
{
    if (pState == NULL || pin >= 32U) return DIGITAL_APP_STATUS_INVALID_PARAM;
    *pState = fake_pinStates[pin];
    return DIGITAL_APP_STATUS_OK;
}
DIGITALAPP_Status_t DIGITALAPP_StartPwm(uint8_t channel)
{
    if (channel >= 8U) return DIGITAL_APP_STATUS_INVALID_PARAM;
    return DIGITAL_APP_STATUS_OK;
}
DIGITALAPP_Status_t DIGITALAPP_StopPwm(uint8_t channel)
{
    if (channel >= 8U) return DIGITAL_APP_STATUS_INVALID_PARAM;
    return DIGITAL_APP_STATUS_OK;
}

/* ============================================================
 * Fake I2CAPP
 * ============================================================ */
I2CAPP_Status_t I2CAPP_Init(void) { return I2C_APP_STATUS_OK; }
I2CAPP_Status_t I2CAPP_Write(uint16_t address, const uint8_t *pData, uint16_t length)
{
    if (pData == NULL || length == 0U) return I2C_APP_STATUS_INVALID_PARAM;
    (void)address;
    return I2C_APP_STATUS_OK;
}
I2CAPP_Status_t I2CAPP_Read(uint16_t address, uint8_t *pData, uint16_t length)
{
    if (pData == NULL || length == 0U) return I2C_APP_STATUS_INVALID_PARAM;
    (void)address;
    memset(pData, 0xAA, length);
    return I2C_APP_STATUS_OK;
}

/* ============================================================
 * Fake SPIAPP
 * ============================================================ */
SPIAPP_Status_t SPIAPP_Init(void) { return SPI_APP_STATUS_OK; }
SPIAPP_Status_t SPIAPP_Write(uint8_t device, const uint8_t *pData, uint16_t length)
{
    if (pData == NULL || length == 0U) return SPI_APP_STATUS_INVALID_PARAM;
    (void)device;
    return SPI_APP_STATUS_OK;
}
SPIAPP_Status_t SPIAPP_Transceive(uint8_t device, const uint8_t *pTxData, uint16_t txLength, uint8_t *pRxData, uint16_t rxLength)
{
    if (pTxData == NULL || pRxData == NULL || txLength == 0U || rxLength == 0U)
        return SPI_APP_STATUS_INVALID_PARAM;
    (void)device;
    memset(pRxData, 0xEF, rxLength);
    return SPI_APP_STATUS_OK;
}