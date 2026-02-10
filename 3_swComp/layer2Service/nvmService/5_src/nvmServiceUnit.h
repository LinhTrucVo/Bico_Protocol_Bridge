#ifndef NVM_SERVICEUNIT_H
#define NVM_SERVICEUNIT_H
#include <stdint.h>
#include <stdbool.h>
#include "nvmServiceCfg.h"
typedef enum NvmService_Status_t NvmService_Status_t;
typedef enum NvmService_Key_t NvmService_Key_t;
typedef struct NvmService_Blob_t NvmService_Blob_t;
NvmService_Status_t NvmServiceUnit_Init(void);
NvmService_Status_t NvmServiceUnit_DeInit(void);
NvmService_Status_t NvmServiceUnit_Save(const NvmService_Blob_t *pBlob);
NvmService_Status_t NvmServiceUnit_Load(NvmService_Key_t key, uint8_t *pData, uint16_t maxLength, uint16_t *pOutLength);
NvmService_Status_t NvmServiceUnit_Erase(NvmService_Key_t key);
NvmService_Status_t NvmServiceUnit_EraseAll(void);
NvmService_Status_t NvmServiceUnit_Exists(NvmService_Key_t key, bool *pExists);
NvmService_Status_t NvmServiceUnit_ComputeCrc(const uint8_t *pData, uint16_t length, uint32_t *pCrc);
#endif
