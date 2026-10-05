// Port interface of the serial driver. Implemented by the device workspace, called by serialDriverUnit.c.

#ifndef SERIALDRIVERPORT_H
#define SERIALDRIVERPORT_H

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
    SERIALPORT_PARITY_NONE = 0,
    SERIALPORT_PARITY_EVEN,
    SERIALPORT_PARITY_ODD
} SerialPort_Parity_t;

typedef enum
{
    SERIALPORT_STOPBITS_1 = 0,
    SERIALPORT_STOPBITS_2
} SerialPort_StopBits_t;

//============================================================================
// Public Functions
//============================================================================
bool SerialPort_Init(uint32_t baudrate, SerialPort_Parity_t parity, SerialPort_StopBits_t stopBits, uint8_t dataBits);
void SerialPort_DeInit(void);
bool SerialPort_Configure(uint32_t baudrate, SerialPort_Parity_t parity, SerialPort_StopBits_t stopBits, uint8_t dataBits);
bool SerialPort_Write(const uint8_t *pData, uint16_t length);
bool SerialPort_WaitTxDone(uint32_t timeoutMs);
bool SerialPort_Read(uint8_t *pData, uint16_t maxLength, uint16_t *pReadLength, uint32_t timeoutMs);
bool SerialPort_GetAvailable(uint16_t *pAvailable);
void SerialPort_FlushRx(void);

#endif /* SERIALDRIVERPORT_H */
