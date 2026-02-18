// This file declares the FFF for functions and MOCK functions for I2cSlaveDriver testing

#ifndef MOCKI2CSLAVEDRIVER_H
#define MOCKI2CSLAVEDRIVER_H

//============================================================================
// Dependencies
//============================================================================
#include "fff.h"

#include "i2cSlaveDriver.h"
#include "i2cSlaveDriverUnit.h"

//============================================================================
// Mock function declarations
//============================================================================
// Declare fake functions for external dependencies if any
// DECLARE_FAKE_VALUE_FUNC(int, ExternalFunction, int);

//============================================================================
// Static function wrapper declarations
//============================================================================

I2cSlaveDriver_Status_t call_I2cSlaveDriverUnit_Init(const I2cSlaveDriver_Config_t *pConfig);
I2cSlaveDriver_Status_t call_I2cSlaveDriverUnit_SetAddress(I2cSlaveDriver_Address_t address);
I2cSlaveDriver_Status_t call_I2cSlaveDriverUnit_GetAddress(I2cSlaveDriver_Address_t *pAddress);
I2cSlaveDriver_Status_t call_I2cSlaveDriverUnit_SetTxBuffer(const uint8_t *pData, uint16_t length);
I2cSlaveDriver_Status_t call_I2cSlaveDriverUnit_SetRxBuffer(uint8_t *pData, uint16_t maxLength);
I2cSlaveDriver_Status_t call_I2cSlaveDriverUnit_GetRxLength(uint16_t *pLength);
I2cSlaveDriver_Status_t call_I2cSlaveDriverUnit_IsAddressed(bool *pIsAddressed);
I2cSlaveDriver_Status_t call_I2cSlaveDriverUnit_RegisterRxCallback(I2cSlaveDriver_RxCallback_t callback);
I2cSlaveDriver_Status_t call_I2cSlaveDriverUnit_RegisterTxCallback(I2cSlaveDriver_TxCallback_t callback);
I2cSlaveDriver_Status_t call_I2cSlaveDriverUnit_RegisterAddressMatchCallback(I2cSlaveDriver_AddressMatchCallback_t callback);
I2cSlaveDriver_Status_t call_I2cSlaveDriverUnit_DeInit(void);

#endif /* MOCKI2CSLAVEDRIVER_H */

