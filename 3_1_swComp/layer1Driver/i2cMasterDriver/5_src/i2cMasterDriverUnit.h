// This file is used to define the public interface of the component unit.
// It contains public macros, types, variables, and function prototypes that shall be included in component headers file (i2cMasterDriver.h)

#ifndef BPB_I2CMASTERDRIVERUNIT_H
#define BPB_I2CMASTERDRIVERUNIT_H

//============================================================================
// Dependencies
//============================================================================
#include <stdint.h>
#include <stdbool.h>
#include "i2cMasterDriverCfg.h"

//============================================================================
// Configuration Macros
//============================================================================
#define BPB_I2C_MASTER_CFG_CLOCK_SPEED    100000  // 100kHz
#define BPB_I2C_MASTER_CFG_ADDRESS_MODE   0       // 0=7bit
#define BPB_I2C_MASTER_CFG_TIMEOUT_MS     1000
#define BPB_I2C_MASTER_CFG_MAX_TRANSFER   256
#define BPB_I2C_MAX_TRANSFER_SIZE         256
#define BPB_I2C_7BIT_ADDRESS_MAX          0x7F
#define BPB_I2C_10BIT_ADDRESS_MAX         0x3FF

//============================================================================
// Status Enums
//============================================================================
#define BPB_I2C_MASTER_STATUS_OK             BPB_I2CMASTERDRIVERSTATUS_OK
#define BPB_I2C_MASTER_STATUS_ERROR          BPB_I2CMASTERDRIVERSTATUS_ERROR
#define BPB_I2C_MASTER_STATUS_BUSY           BPB_I2CMASTERDRIVERSTATUS_BUSY
#define BPB_I2C_MASTER_STATUS_TIMEOUT        BPB_I2CMASTERDRIVERSTATUS_TIMEOUT
#define BPB_I2C_MASTER_STATUS_NACK           BPB_I2CMASTERDRIVERSTATUS_NACK
#define BPB_I2C_MASTER_STATUS_ARBITRATION_LOST BPB_I2CMASTERDRIVERSTATUS_ARBITRATION_LOST
#define BPB_I2C_MASTER_STATUS_BUS_ERROR      BPB_I2CMASTERDRIVERSTATUS_BUS_ERROR
#define BPB_I2C_MASTER_STATUS_INVALID_PARAM  BPB_I2CMASTERDRIVERSTATUS_INVALID_PARAM

//============================================================================
// Public Macros
//============================================================================

//============================================================================
// Public Types
//============================================================================
typedef enum
{
    BPB_I2CMASTERDRIVERSTATUS_OK = 0,
    BPB_I2CMASTERDRIVERSTATUS_ERROR,
    BPB_I2CMASTERDRIVERSTATUS_BUSY,
    BPB_I2CMASTERDRIVERSTATUS_TIMEOUT,
    BPB_I2CMASTERDRIVERSTATUS_NACK,
    BPB_I2CMASTERDRIVERSTATUS_ARBITRATION_LOST,
    BPB_I2CMASTERDRIVERSTATUS_BUS_ERROR,
    BPB_I2CMASTERDRIVERSTATUS_INVALID_PARAM
} I2cMasterDriver_Status_t;

typedef enum
{
    BPB_I2C_SPEED_STANDARD = 100000,
    BPB_I2C_SPEED_FAST = 400000,
    BPB_I2C_SPEED_FAST_PLUS = 1000000,
    BPB_I2C_SPEED_HIGH_SPEED = 3400000
} I2cMasterDriver_Speed_t;

typedef enum
{
    BPB_I2C_ADDRESS_7BIT = 0,
    BPB_I2C_ADDRESS_10BIT
} I2cMasterDriver_AddressMode_t;

typedef uint16_t I2cMasterDriver_Address_t;

typedef struct
{
    I2cMasterDriver_Speed_t speed;
    I2cMasterDriver_AddressMode_t addressMode;
    bool enableDMA;
    bool enableInterrupt;
    uint32_t timeoutMs;
} I2cMasterDriver_Config_t;

typedef void (*I2cMasterDriver_TxCallback_t)(I2cMasterDriver_Status_t status);
typedef void (*I2cMasterDriver_RxCallback_t)(I2cMasterDriver_Status_t status, const uint8_t *pData, uint16_t length);
typedef void (*I2cMasterDriver_Callback_t)(I2cMasterDriver_Status_t status);

//============================================================================
// Public Functions
//============================================================================
I2cMasterDriver_Status_t I2cMasterDriverUnit_Init(const I2cMasterDriver_Config_t *pConfig);
I2cMasterDriver_Status_t I2cMasterDriverUnit_SetSpeed(I2cMasterDriver_Speed_t speed);
I2cMasterDriver_Status_t I2cMasterDriverUnit_Write(I2cMasterDriver_Address_t address, const uint8_t *pData, uint16_t length);
I2cMasterDriver_Status_t I2cMasterDriverUnit_WriteWithTimeout(I2cMasterDriver_Address_t address, const uint8_t *pData, uint16_t length, uint32_t timeoutMs);
I2cMasterDriver_Status_t I2cMasterDriverUnit_Read(I2cMasterDriver_Address_t address, uint8_t *pData, uint16_t length);
I2cMasterDriver_Status_t I2cMasterDriverUnit_ReadWithTimeout(I2cMasterDriver_Address_t address, uint8_t *pData, uint16_t length, uint32_t timeoutMs);
I2cMasterDriver_Status_t I2cMasterDriverUnit_WriteRead(I2cMasterDriver_Address_t address, const uint8_t *pWriteData, uint16_t writeLength, uint8_t *pReadData, uint16_t readLength);
I2cMasterDriver_Status_t I2cMasterDriverUnit_WriteRegister(I2cMasterDriver_Address_t address, uint8_t regAddress, const uint8_t *pData, uint16_t length);
I2cMasterDriver_Status_t I2cMasterDriverUnit_ReadRegister(I2cMasterDriver_Address_t address, uint8_t regAddress, uint8_t *pData, uint16_t length);
I2cMasterDriver_Status_t I2cMasterDriverUnit_ScanBus(I2cMasterDriver_Address_t *pFoundAddresses, uint8_t maxAddresses, uint8_t *pNumFound);
I2cMasterDriver_Status_t I2cMasterDriverUnit_IsBusy(bool *pIsBusy);
I2cMasterDriver_Status_t I2cMasterDriverUnit_RegisterCallback(I2cMasterDriver_Callback_t callback);
I2cMasterDriver_Status_t I2cMasterDriverUnit_DeInit(void);

#endif /* BPB_I2CMASTERDRIVERUNIT_H */
