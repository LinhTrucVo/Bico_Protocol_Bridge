// Fake implementation for ComService

#include "fakeComService.h"
#include <string.h>

static uint8_t  fakeRxBuffer[512];
static uint16_t fakeRxCount = 0U;
static uint8_t  fakeTxBuffer[512];
static uint16_t fakeTxCount = 0U;
static bool     fakeInitialized = false;

void FakeComService_Reset(void)
{
    fakeRxCount = 0U;
    fakeTxCount = 0U;
    fakeInitialized = false;
}

void FakeComService_InjectRxData(const uint8_t *pData, uint16_t length)
{
    if (fakeRxCount + length <= sizeof(fakeRxBuffer))
    {
        memcpy(&fakeRxBuffer[fakeRxCount], pData, length);
        fakeRxCount += length;
    }
}

uint16_t FakeComService_GetTxData(uint8_t *pData, uint16_t maxLength)
{
    uint16_t len = (fakeTxCount < maxLength) ? fakeTxCount : maxLength;
    memcpy(pData, fakeTxBuffer, len);
    return len;
}

ComService_Status_t ComServiceUnit_Init(void)
{
    FakeComService_Reset();
    fakeInitialized = true;
    return COMSERVICE_STATUS_OK;
}

ComService_Status_t ComServiceUnit_DeInit(void)
{
    fakeInitialized = false;
    return COMSERVICE_STATUS_OK;
}

ComService_Status_t ComServiceUnit_Run(void)
{
    return fakeInitialized ? COMSERVICE_STATUS_OK : COMSERVICE_STATUS_NOT_INITIALIZED;
}

bool ComServiceUnit_IsRxDataAvailable(void)
{
    return (fakeInitialized && fakeRxCount > 0U);
}

ComService_Status_t ComServiceUnit_Read(uint8_t *pData, uint16_t maxLength, uint16_t *pReadLength)
{
    if (!fakeInitialized) return COMSERVICE_STATUS_NOT_INITIALIZED;
    if (pData == NULL || pReadLength == NULL) return COMSERVICE_STATUS_INVALID_PARAM;
    if (fakeRxCount == 0U) { *pReadLength = 0U; return COMSERVICE_STATUS_BUFFER_EMPTY; }

    uint16_t len = (fakeRxCount < maxLength) ? fakeRxCount : maxLength;
    memcpy(pData, fakeRxBuffer, len);
    /* Shift remaining data */
    fakeRxCount -= len;
    memmove(fakeRxBuffer, &fakeRxBuffer[len], fakeRxCount);
    *pReadLength = len;
    return COMSERVICE_STATUS_OK;
}

ComService_Status_t ComServiceUnit_Write(const uint8_t *pData, uint16_t length)
{
    if (!fakeInitialized) return COMSERVICE_STATUS_NOT_INITIALIZED;
    if (pData == NULL || length == 0U) return COMSERVICE_STATUS_INVALID_PARAM;
    if (fakeTxCount + length > sizeof(fakeTxBuffer)) return COMSERVICE_STATUS_BUFFER_FULL;

    memcpy(&fakeTxBuffer[fakeTxCount], pData, length);
    fakeTxCount += length;
    return COMSERVICE_STATUS_OK;
}
