// Mock implementation for ComService

#include "mockComService.h"
#include <string.h>

static MockComService_Calls_t mockCalls = {0};

void MockComService_Reset(void)
{
    memset(&mockCalls, 0, sizeof(mockCalls));
}

MockComService_Calls_t *MockComService_GetCalls(void)
{
    return &mockCalls;
}

ComService_Status_t ComServiceUnit_Init(void)
{
    mockCalls.initCalled++;
    return COMSERVICE_STATUS_OK;
}

ComService_Status_t ComServiceUnit_DeInit(void)
{
    mockCalls.deInitCalled++;
    return COMSERVICE_STATUS_OK;
}

ComService_Status_t ComServiceUnit_Run(void)
{
    mockCalls.runCalled++;
    return COMSERVICE_STATUS_OK;
}

bool ComServiceUnit_IsRxDataAvailable(void)
{
    mockCalls.isRxDataAvailableCalled++;
    return mockCalls.rxDataAvailableReturnValue;
}

ComService_Status_t ComServiceUnit_Read(uint8_t *pData, uint16_t maxLength, uint16_t *pReadLength)
{
    mockCalls.readCalled++;
    if (mockCalls.pReadData != NULL && mockCalls.readDataLength > 0U)
    {
        uint16_t len = (mockCalls.readDataLength < maxLength) ? mockCalls.readDataLength : maxLength;
        memcpy(pData, mockCalls.pReadData, len);
        *pReadLength = len;
        return COMSERVICE_STATUS_OK;
    }
    *pReadLength = 0U;
    return COMSERVICE_STATUS_BUFFER_EMPTY;
}

ComService_Status_t ComServiceUnit_Write(const uint8_t *pData, uint16_t length)
{
    mockCalls.writeCalled++;
    mockCalls.lastWriteLength = length;
    if (length <= sizeof(mockCalls.lastWriteData))
    {
        memcpy(mockCalls.lastWriteData, pData, length);
    }
    return COMSERVICE_STATUS_OK;
}
