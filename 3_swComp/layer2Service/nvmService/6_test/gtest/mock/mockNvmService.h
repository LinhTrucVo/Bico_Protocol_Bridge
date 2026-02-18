// This file declares the FFF for functions and MOCK functions for NvmService testing

#ifndef MOCKNVMSERVICE_H
#define MOCKNVMSERVICE_H

//============================================================================
// Dependencies
//============================================================================
#include "fff.h"

#include "nvmService.h"
#include "nvmServiceUnit.h"

//============================================================================
// Mock function declarations
//============================================================================
// Declare fake functions for external dependencies if any
// DECLARE_FAKE_VALUE_FUNC(int, ExternalFunction, int);

//============================================================================
// Static function wrapper declarations
//============================================================================

NvmService_Status_t call_NvmServiceUnit_Init(void);
NvmService_Status_t call_NvmServiceUnit_DeInit(void);
NvmService_Status_t call_NvmServiceUnit_Save(const NvmService_Blob_t *pBlob);
NvmService_Status_t call_NvmServiceUnit_Load(NvmService_Key_t key, uint8_t *pData, uint16_t maxLength, uint16_t *pOutLength);
NvmService_Status_t call_NvmServiceUnit_Erase(NvmService_Key_t key);
NvmService_Status_t call_NvmServiceUnit_EraseAll(void);
NvmService_Status_t call_NvmServiceUnit_Exists(NvmService_Key_t key, bool *pExists);
NvmService_Status_t call_NvmServiceUnit_ComputeCrc(const uint8_t *pData, uint16_t length, uint32_t *pCrc);

#endif /* MOCKNVMSERVICE_H */
