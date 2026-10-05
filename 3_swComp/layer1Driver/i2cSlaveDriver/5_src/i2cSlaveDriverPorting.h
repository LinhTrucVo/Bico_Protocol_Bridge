// Port interface of the I2C slave driver. Implemented by the device workspace, called by i2cSlaveDriverUnit.c.

#ifndef I2CSLAVEDRIVERPORT_H
#define I2CSLAVEDRIVERPORT_H

//============================================================================
// Dependencies
//============================================================================
#include <stdint.h>
#include <stdbool.h>

//============================================================================
// Public Types
//============================================================================
// Called by the port, possibly from interrupt context, when the master wrote data.
typedef void (*I2cSlavePort_ReceiveHandler_t)(const uint8_t *pData, uint16_t length);

// Called by the port from task context when the master requests data. The handler answers with I2cSlavePort_Write().
typedef void (*I2cSlavePort_RequestHandler_t)(void);

//============================================================================
// Public Functions
//============================================================================
// The address is a 7-bit address.
bool I2cSlavePort_Init(uint16_t address);
void I2cSlavePort_DeInit(void);
bool I2cSlavePort_Write(const uint8_t *pData, uint16_t length, uint32_t timeoutMs);
void I2cSlavePort_SetReceiveHandler(I2cSlavePort_ReceiveHandler_t handler);
void I2cSlavePort_SetRequestHandler(I2cSlavePort_RequestHandler_t handler);

#endif /* I2CSLAVEDRIVERPORT_H */
