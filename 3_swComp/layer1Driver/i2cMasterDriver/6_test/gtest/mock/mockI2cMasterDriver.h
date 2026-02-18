// This file declares the FFF for functions and MOCK functions for I2cMasterDriver testing

#ifndef MOCKI2CMASTERDRIVER_H
#define MOCKI2CMASTERDRIVER_H

//============================================================================
// Dependencies
//============================================================================
#include "fff.h"

#include "i2cMasterDriver.h"
#include "i2cMasterDriverUnit.h"

//============================================================================
// Mock function declarations
//============================================================================
// Declare fake functions for external dependencies if any
// DECLARE_FAKE_VALUE_FUNC(int, ExternalFunction, int);

//============================================================================
// Static function wrapper declarations
//============================================================================

I2cMasterDriver_Status_t call_I2cMasterDriverUnit_Init(const I2cMasterDriver_Config_t *pConfig);
I2cMasterDriver_Status_t call_I2cMasterDriverUnit_SetSpeed(I2cMasterDriver_Speed_t speed);
I2cMasterDriver_Status_t call_I2cMasterDriverUnit_Write(I2cMasterDriver_Address_t address, const uint8_t *pData, uint16_t length);
I2cMasterDriver_Status_t call_I2cMasterDriverUnit_WriteWithTimeout(I2cMasterDriver_Address_t address, const uint8_t *pData, uint16_t length, uint32_t timeoutMs);
I2cMasterDriver_Status_t call_I2cMasterDriverUnit_Read(I2cMasterDriver_Address_t address, uint8_t *pData, uint16_t length);
I2cMasterDriver_Status_t call_I2cMasterDriverUnit_ReadWithTimeout(I2cMasterDriver_Address_t address, uint8_t *pData, uint16_t length, uint32_t timeoutMs);
I2cMasterDriver_Status_t call_I2cMasterDriverUnit_WriteRead(I2cMasterDriver_Address_t address, const uint8_t *pWriteData, uint16_t writeLength, uint8_t *pReadData, uint16_t readLength);
I2cMasterDriver_Status_t call_I2cMasterDriverUnit_WriteRegister(I2cMasterDriver_Address_t address, uint8_t regAddress, const uint8_t *pData, uint16_t length);
I2cMasterDriver_Status_t call_I2cMasterDriverUnit_ReadRegister(I2cMasterDriver_Address_t address, uint8_t regAddress, uint8_t *pData, uint16_t length);
I2cMasterDriver_Status_t call_I2cMasterDriverUnit_ScanBus(I2cMasterDriver_Address_t *pFoundAddresses, uint8_t maxAddresses, uint8_t *pNumFound);
I2cMasterDriver_Status_t call_I2cMasterDriverUnit_IsBusy(bool *pIsBusy);
I2cMasterDriver_Status_t call_I2cMasterDriverUnit_RegisterCallback(I2cMasterDriver_Callback_t callback);
I2cMasterDriver_Status_t call_I2cMasterDriverUnit_DeInit(void);

#endif /* MOCKI2CMASTERDRIVER_H */
