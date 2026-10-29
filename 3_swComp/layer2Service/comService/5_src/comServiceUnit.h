#ifndef BPB_COMSERVICEUNIT_H
#define BPB_COMSERVICEUNIT_H

#include <stdint.h>
#include <stdbool.h>
#include "comServiceCfg.h"

//============================================================================
// Status Codes
//============================================================================
typedef enum
{
    BPB_COMSERVICE_STATUS_OK = 0,
    BPB_COMSERVICE_STATUS_ERROR,
    BPB_COMSERVICE_STATUS_INVALID_PARAM,
    BPB_COMSERVICE_STATUS_BUFFER_FULL,
    BPB_COMSERVICE_STATUS_BUFFER_EMPTY,
    BPB_COMSERVICE_STATUS_NOT_INITIALIZED
} ComService_Status_t;

//============================================================================
// Function Declarations
//============================================================================
ComService_Status_t ComServiceUnit_Init(void);
ComService_Status_t ComServiceUnit_DeInit(void);
ComService_Status_t ComServiceUnit_Run(void);
bool                ComServiceUnit_IsRxDataAvailable(void);
ComService_Status_t ComServiceUnit_Read(uint8_t *pData, uint16_t maxLength, uint16_t *pReadLength);
ComService_Status_t ComServiceUnit_Write(const uint8_t *pData, uint16_t length);

#endif /* BPB_COMSERVICEUNIT_H */
