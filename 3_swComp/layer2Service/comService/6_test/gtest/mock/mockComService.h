#ifndef MOCKCOMSERVICE_H
#define MOCKCOMSERVICE_H

#include <stdint.h>
#include <stdbool.h>
#include "comServiceUnit.h"

typedef struct
{
    uint32_t initCalled;
    uint32_t deInitCalled;
    uint32_t runCalled;
    uint32_t isRxDataAvailableCalled;
    uint32_t readCalled;
    uint32_t writeCalled;
    bool     rxDataAvailableReturnValue;
    const uint8_t *pReadData;
    uint16_t readDataLength;
    uint8_t  lastWriteData[256];
    uint16_t lastWriteLength;
} MockComService_Calls_t;

void MockComService_Reset(void);
MockComService_Calls_t *MockComService_GetCalls(void);

#endif /* MOCKCOMSERVICE_H */
