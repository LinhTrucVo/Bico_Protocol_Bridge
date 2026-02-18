#ifndef NVM_SERVICEUNIT_H
#define NVM_SERVICEUNIT_H
#include <stdint.h>
#include <stdbool.h>
#include "nvmServiceCfg.h"

//============================================================================
// Configuration Macros
//============================================================================
#define NVM_SERVICE_CFG_MAX_BLOB_SIZE      512
#define NVM_SERVICE_CFG_MAX_KEYS           6

//============================================================================
// NVM Service Keys
//============================================================================
#define NVM_SERVICE_KEY_SYSTEM_CONFIG      0x00000001U
#define NVM_SERVICE_KEY_USER_DATA         0x00000002U
#define NVM_SERVICE_KEY_CALIBRATION       0x00000003U
#define NVM_SERVICE_KEY_STATE              0x00000004U
#define NVM_SERVICE_KEY_SETTINGS           0x00000005U
#define NVM_SERVICE_KEY_RESERVED           0x00000006U

//============================================================================
// Type Definitions
//============================================================================
typedef uint32_t NvmService_Key_t;

typedef struct
{
    NvmService_Key_t key;
    uint16_t dataLength;
    const uint8_t *pData;
} NvmService_Blob_t;

typedef enum
{
    NVM_SERVICE_STATUS_OK = 0,
    NVM_SERVICE_STATUS_ERROR,
    NVM_SERVICE_STATUS_NOT_FOUND,
    NVM_SERVICE_STATUS_FULL,
    NVM_SERVICE_STATUS_INVALID_PARAM,
    NVM_SERVICE_STATUS_NOT_INITIALIZED,
    NVM_SERVICE_STATUS_CRC_ERROR
} NvmService_Status_t;

//============================================================================
// Function declarations
//============================================================================
NvmService_Status_t NvmServiceUnit_Init(void);
NvmService_Status_t NvmServiceUnit_DeInit(void);
NvmService_Status_t NvmServiceUnit_Save(const NvmService_Blob_t *pBlob);
NvmService_Status_t NvmServiceUnit_Load(NvmService_Key_t key, uint8_t *pData, uint16_t maxLength, uint16_t *pOutLength);
NvmService_Status_t NvmServiceUnit_Erase(NvmService_Key_t key);
NvmService_Status_t NvmServiceUnit_EraseAll(void);
NvmService_Status_t NvmServiceUnit_Exists(NvmService_Key_t key, bool *pExists);
NvmService_Status_t NvmServiceUnit_ComputeCrc(const uint8_t *pData, uint16_t length, uint32_t *pCrc);

#endif
