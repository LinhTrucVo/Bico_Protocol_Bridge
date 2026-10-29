// This file defines the FFF for functions and MOCK functions for NvmService testing

//============================================================================
// Dependencies
//============================================================================
#include "mockNvmService.h"

// Include the .c file to get access to static variables and functions
#include "nvmServiceUnit.c"

//============================================================================
// Mock function definitions
//============================================================================

// Required for FFF
DEFINE_FFF_GLOBALS;

// DEFINE_FAKE_VALUE_FUNC(int, ExternalFunction, int);

//============================================================================
// Static function wrapper definitions
//============================================================================

NvmService_Status_t call_NvmServiceUnit_Init(void)
{
    return NvmServiceUnit_Init();
}

NvmService_Status_t call_NvmServiceUnit_DeInit(void)
{
    return NvmServiceUnit_DeInit();
}

NvmService_Status_t call_NvmServiceUnit_Save(const NvmService_Blob_t *pBlob)
{
    return NvmServiceUnit_Save(pBlob);
}

NvmService_Status_t call_NvmServiceUnit_Load(NvmService_Key_t key, uint8_t *pData, uint16_t maxLength, uint16_t *pOutLength)
{
    return NvmServiceUnit_Load(key, pData, maxLength, pOutLength);
}

NvmService_Status_t call_NvmServiceUnit_Erase(NvmService_Key_t key)
{
    return NvmServiceUnit_Erase(key);
}

NvmService_Status_t call_NvmServiceUnit_EraseAll(void)
{
    return NvmServiceUnit_EraseAll();
}

NvmService_Status_t call_NvmServiceUnit_Exists(NvmService_Key_t key, bool *pExists)
{
    return NvmServiceUnit_Exists(key, pExists);
}

NvmService_Status_t call_NvmServiceUnit_ComputeCrc(const uint8_t *pData, uint16_t length, uint32_t *pCrc)
{
    return NvmServiceUnit_ComputeCrc(pData, length, pCrc);
}
