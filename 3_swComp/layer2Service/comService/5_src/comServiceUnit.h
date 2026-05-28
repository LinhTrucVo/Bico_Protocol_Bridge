#ifndef COMSERVICEUNIT_H
#define COMSERVICEUNIT_H

#include <stdint.h>
#include <stdbool.h>
#include "comServiceCfg.h"

//============================================================================
// Status Codes
//============================================================================
typedef enum
{
    COMSERVICE_STATUS_OK = 0,
    COMSERVICE_STATUS_ERROR,
    COMSERVICE_STATUS_INVALID_PARAM,
    COMSERVICE_STATUS_BUFFER_FULL,
    COMSERVICE_STATUS_BUFFER_EMPTY,
    COMSERVICE_STATUS_NOT_INITIALIZED
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

#endif /* COMSERVICEUNIT_H */
