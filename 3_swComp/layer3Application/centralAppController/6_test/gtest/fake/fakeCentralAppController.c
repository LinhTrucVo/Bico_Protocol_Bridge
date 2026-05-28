// Fake implementations for CentralAppController testing
// Provides all dependency fakes: Deserialize, Serialize, ConfigService, peripheral services

#include <stddef.h>
#include <string.h>
#include "fakeCentralAppController.h"
#include "deserialize.h"
#include "serialize.h"
#include "configService.h"
#include "analogService.h"
#include "digitalService.h"
#include "i2cService.h"
#include "spiService.h"

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
 * Fake AnalogService
 * ============================================================ */
AnalogService_Status_t AnalogServiceUnit_Init(void) { return ANALOGSERVICE_STATUS_OK; }
AnalogService_Status_t AnalogServiceUnit_ReadAdc(uint8_t channel, uint16_t *pRawValue)
{
    if (pRawValue == NULL || channel >= 8U) return ANALOGSERVICE_STATUS_INVALID_PARAM;
    *pRawValue = 2048U; /* Fake ADC value */
    return ANALOGSERVICE_STATUS_OK;
}

/* ============================================================
 * Fake DigitalService
 * ============================================================ */
static uint8_t fake_pinStates[32] = {0};

DigitalService_Status_t DigitalServiceUnit_Init(void) { return DIGITALSERVICE_STATUS_OK; }
DigitalService_Status_t DigitalServiceUnit_WriteGpio(uint8_t pin, uint8_t state)
{
    if (pin >= 32U) return DIGITALSERVICE_STATUS_INVALID_PARAM;
    fake_pinStates[pin] = state;
    return DIGITALSERVICE_STATUS_OK;
}
DigitalService_Status_t DigitalServiceUnit_ReadGpio(uint8_t pin, uint8_t *pState)
{
    if (pState == NULL || pin >= 32U) return DIGITALSERVICE_STATUS_INVALID_PARAM;
    *pState = fake_pinStates[pin];
    return DIGITALSERVICE_STATUS_OK;
}
DigitalService_Status_t DigitalServiceUnit_StartPwm(uint8_t channel)
{
    if (channel >= 8U) return DIGITALSERVICE_STATUS_INVALID_PARAM;
    return DIGITALSERVICE_STATUS_OK;
}
DigitalService_Status_t DigitalServiceUnit_StopPwm(uint8_t channel)
{
    if (channel >= 8U) return DIGITALSERVICE_STATUS_INVALID_PARAM;
    return DIGITALSERVICE_STATUS_OK;
}

/* ============================================================
 * Fake I2cService
 * ============================================================ */
I2cService_Status_t I2cServiceUnit_Init(void) { return I2CSERVICE_STATUS_OK; }
I2cService_Status_t I2cServiceUnit_Write(uint16_t address, const uint8_t *pData, uint16_t length)
{
    if (pData == NULL || length == 0U) return I2CSERVICE_STATUS_INVALID_PARAM;
    (void)address;
    return I2CSERVICE_STATUS_OK;
}
I2cService_Status_t I2cServiceUnit_Read(uint16_t address, uint8_t *pData, uint16_t length)
{
    if (pData == NULL || length == 0U) return I2CSERVICE_STATUS_INVALID_PARAM;
    (void)address;
    memset(pData, 0xAA, length);
    return I2CSERVICE_STATUS_OK;
}

/* ============================================================
 * Fake SpiService
 * ============================================================ */
SpiService_Status_t SpiServiceUnit_Init(void) { return SPISERVICE_STATUS_OK; }
SpiService_Status_t SpiServiceUnit_Write(uint8_t device, const uint8_t *pData, uint16_t length)
{
    if (pData == NULL || length == 0U) return SPISERVICE_STATUS_INVALID_PARAM;
    (void)device;
    return SPISERVICE_STATUS_OK;
}
SpiService_Status_t SpiServiceUnit_Transceive(uint8_t device, const uint8_t *pTxData, uint16_t txLength, uint8_t *pRxData, uint16_t rxLength)
{
    if (pTxData == NULL || pRxData == NULL || txLength == 0U || rxLength == 0U)
        return SPISERVICE_STATUS_INVALID_PARAM;
    (void)device;
    memset(pRxData, 0xEF, rxLength);
    return SPISERVICE_STATUS_OK;
}