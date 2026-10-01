// Port interface of the I2C master driver. Implemented by the device workspace, called by i2cMasterDriverUnit.c.

#ifndef I2CMASTERDRIVERPORT_H
#define I2CMASTERDRIVERPORT_H

//============================================================================
// Dependencies
//============================================================================
#include <stdint.h>
#include <stdbool.h>

//============================================================================
// Public Types
//============================================================================
typedef enum
{
    I2CMASTERPORT_OK = 0,
    I2CMASTERPORT_ERROR,
    I2CMASTERPORT_TIMEOUT
} I2cMasterPort_Result_t;

//============================================================================
// Public Functions
//============================================================================
// All transfers are blocking and use 7-bit addresses.
bool I2cMasterPort_Init(uint32_t speedHz);
void I2cMasterPort_DeInit(void);
bool I2cMasterPort_SetSpeed(uint32_t speedHz);
I2cMasterPort_Result_t I2cMasterPort_Write(uint16_t address, const uint8_t *pData, uint16_t length, uint32_t timeoutMs);
I2cMasterPort_Result_t I2cMasterPort_Read(uint16_t address, uint8_t *pData, uint16_t length, uint32_t timeoutMs);
I2cMasterPort_Result_t I2cMasterPort_WriteRead(uint16_t address, const uint8_t *pWriteData, uint16_t writeLength, uint8_t *pReadData, uint16_t readLength, uint32_t timeoutMs);
bool I2cMasterPort_Probe(uint16_t address, uint32_t timeoutMs);

#endif /* I2CMASTERDRIVERPORT_H */
