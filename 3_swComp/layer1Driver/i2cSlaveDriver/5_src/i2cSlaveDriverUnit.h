// This file is used to define the public interface of the component unit.
// It contains public macros, types, variables, and function prototypes that shall be included in component headers file (i2cSlaveDriver.h)

#ifndef I2C_SLAVEDRIVERUNIT_H
#define I2C_SLAVEDRIVERUNIT_H

//============================================================================
// Dependencies
//============================================================================
#include <stdint.h>
#include <stdbool.h>
#include "i2cSlaveDriverCfg.h"

//============================================================================
// Public Macros
//============================================================================
#define I2C_SLAVE_MAX_BUFFER_SIZE    256

//============================================================================
// Public Types
//============================================================================
typedef enum
{
    I2C_SLAVE_STATUS_OK = 0,
    I2C_SLAVE_STATUS_ERROR,
    I2C_SLAVE_STATUS_BUSY,
    I2C_SLAVE_STATUS_BUFFER_OVERFLOW,
    I2C_SLAVE_STATUS_BUS_ERROR,
    I2C_SLAVE_STATUS_NOT_INITIALIZED
} I2cSlaveDriver_Status_t;

typedef enum
{
    I2C_SLAVE_ADDRESS_7BIT = 0,
    I2C_SLAVE_ADDRESS_10BIT
} I2cSlaveDriver_AddressMode_t;

typedef uint16_t I2cSlaveDriver_Address_t;

typedef struct
{
    I2cSlaveDriver_Address_t ownAddress;
    I2cSlaveDriver_AddressMode_t addressMode;
    bool enableGeneralCall;
    bool enableDMA;
    bool enableInterrupt;
} I2cSlaveDriver_Config_t;

typedef void (*I2cSlaveDriver_RxCallback_t)(const uint8_t *pData, uint16_t length);
typedef void (*I2cSlaveDriver_TxCallback_t)(uint8_t *pData, uint16_t *pLength);
typedef void (*I2cSlaveDriver_AddressMatchCallback_t)(I2cSlaveDriver_Address_t address);

//============================================================================
// Public Variables
//============================================================================

//============================================================================
// Public Functions
//============================================================================
I2cSlaveDriver_Status_t I2cSlaveDriverUnit_Init(const I2cSlaveDriver_Config_t *pConfig);
I2cSlaveDriver_Status_t I2cSlaveDriverUnit_SetAddress(I2cSlaveDriver_Address_t address);
I2cSlaveDriver_Status_t I2cSlaveDriverUnit_GetAddress(I2cSlaveDriver_Address_t *pAddress);
I2cSlaveDriver_Status_t I2cSlaveDriverUnit_SetTxBuffer(const uint8_t *pData, uint16_t length);
I2cSlaveDriver_Status_t I2cSlaveDriverUnit_SetRxBuffer(uint8_t *pData, uint16_t maxLength);
I2cSlaveDriver_Status_t I2cSlaveDriverUnit_GetRxLength(uint16_t *pLength);
I2cSlaveDriver_Status_t I2cSlaveDriverUnit_IsAddressed(bool *pIsAddressed);
I2cSlaveDriver_Status_t I2cSlaveDriverUnit_RegisterRxCallback(I2cSlaveDriver_RxCallback_t callback);
I2cSlaveDriver_Status_t I2cSlaveDriverUnit_RegisterTxCallback(I2cSlaveDriver_TxCallback_t callback);
I2cSlaveDriver_Status_t I2cSlaveDriverUnit_RegisterAddressMatchCallback(I2cSlaveDriver_AddressMatchCallback_t callback);
I2cSlaveDriver_Status_t I2cSlaveDriverUnit_DeInit(void);

#endif /* I2C_SLAVEDRIVERUNIT_H */
