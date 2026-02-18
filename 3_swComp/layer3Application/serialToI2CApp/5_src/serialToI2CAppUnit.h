#ifndef SERIAL_TO_I2C_APPUNIT_H
#define SERIAL_TO_I2C_APPUNIT_H
#include <stdint.h>
#include <stdbool.h>
#include "serialToI2CAppCfg.h"

//============================================================================
// Configuration Macros
//============================================================================
#define SERIAL_TO_I2C_CFG_DEFAULT_SPEED    100000
#define SERIAL_TO_I2C_CFG_DEFAULT_TIMEOUT  100
#define SERIAL_TO_I2C_CFG_MAX_TRANSFER     256

//============================================================================
// Type Definitions
//============================================================================
typedef enum
{
    SERIAL_TO_I2C_APP_STATUS_OK = 0,
    SERIAL_TO_I2C_APP_STATUS_ERROR,
    SERIAL_TO_I2C_APP_STATUS_INVALID_PARAM,
    SERIAL_TO_I2C_APP_STATUS_NOT_INITIALIZED
} SerialToI2CApp_Status_t;

typedef enum
{
    SerialToI2CApp_STATE_IDLE = 0,
    SerialToI2CApp_STATE_BUSY,
    SerialToI2CApp_STATE_ERROR
} SerialToI2CApp_State_t;

typedef enum
{
    SERIAL_TO_I2C_ADDR_7BIT  = 0,
    SERIAL_TO_I2C_ADDR_10BIT = 1
} SerialToI2CApp_AddressMode_t;

typedef struct
{
    uint32_t speed;
    SerialToI2CApp_AddressMode_t addressMode;
    uint32_t timeoutMs;
} SerialToI2CApp_Config_t;

typedef struct
{
    uint16_t       address;
    const uint8_t *pWriteData;
    uint16_t       writeLength;
    uint8_t       *pReadData;
    uint16_t       readLength;
} SerialToI2CApp_Transfer_t;

//============================================================================
// Public Functions
//============================================================================
SerialToI2CApp_Status_t SerialToI2CAppUnit_Init(void);
SerialToI2CApp_Status_t SerialToI2CAppUnit_DeInit(void);
SerialToI2CApp_Status_t SerialToI2CAppUnit_Run(void);
SerialToI2CApp_Status_t SerialToI2CAppUnit_ProcessFrame(const uint8_t *pFrame, uint16_t frameLength, uint8_t *pResponse, uint16_t *pResponseLength);

//============================================================================
// Backward Compatibility Macros
//============================================================================
#define SerialToI2CAppUnit_Init           SerialToI2CApp_Init
#define SerialToI2CAppUnit_DeInit         SerialToI2CApp_DeInit
#define SerialToI2CAppUnit_Run            SerialToI2CApp_Run
#define SerialToI2CAppUnit_ProcessFrame   SerialToI2CApp_ProcessFrame

#endif /* SERIAL_TO_I2C_APPUNIT_H */
