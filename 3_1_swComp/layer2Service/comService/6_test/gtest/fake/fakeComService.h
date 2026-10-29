#ifndef BPB_FAKECOMSERVICE_H
#define BPB_FAKECOMSERVICE_H

#include <stdint.h>
#include <stdbool.h>
#include "comServiceUnit.h"

void FakeComService_Reset(void);
void FakeComService_InjectRxData(const uint8_t *pData, uint16_t length);
uint16_t FakeComService_GetTxData(uint8_t *pData, uint16_t maxLength);

#endif /* BPB_FAKECOMSERVICE_H */
