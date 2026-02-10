// This file is used to define the public interface of the component unit.
// It contains public macros, types, variables, and function prototypes that shall be included in component headers file (serialDriver.h)

#ifndef SERIALDRIVERUNIT_H
#define SERIALDRIVERUNIT_H

//============================================================================
// Dependencies
//============================================================================
#include <stdint.h>
#include <stdbool.h>
#include "serialDriverCfg.h"

//============================================================================
// Public Macros
//============================================================================
#define SERIAL_MAX_BUFFER_SIZE    256

//============================================================================
// Public Types
//============================================================================
typedef enum
{
    SERIAL_STATUS_OK = 0,
    SERIAL_STATUS_ERROR,
    SERIAL_STATUS_BUSY,
    SERIAL_STATUS_TIMEOUT,
    SERIAL_STATUS_PARITY_ERROR,
    SERIAL_STATUS_FRAMING_ERROR,
    SERIAL_STATUS_OVERRUN_ERROR,
    SERIAL_STATUS_BUFFER_FULL
} SerialDriver_Status_t;

typedef enum
{
    SERIAL_BAUDRATE_9600 = 9600,
    SERIAL_BAUDRATE_19200 = 19200,
    SERIAL_BAUDRATE_38400 = 38400,
    SERIAL_BAUDRATE_57600 = 57600,
    SERIAL_BAUDRATE_115200 = 115200,
    SERIAL_BAUDRATE_230400 = 230400,
    SERIAL_BAUDRATE_460800 = 460800,
    SERIAL_BAUDRATE_921600 = 921600
} SerialDriver_Baudrate_t;

typedef enum
{
    SERIAL_PARITY_NONE = 0,
    SERIAL_PARITY_EVEN,
    SERIAL_PARITY_ODD
} SerialDriver_Parity_t;

typedef enum
{
    SERIAL_STOPBITS_1 = 0,
    SERIAL_STOPBITS_2
} SerialDriver_StopBits_t;

typedef enum
{
    SERIAL_DATABITS_7 = 7,
    SERIAL_DATABITS_8 = 8,
    SERIAL_DATABITS_9 = 9
} SerialDriver_DataBits_t;

typedef enum
{
    SERIAL_FLOWCONTROL_NONE = 0,
    SERIAL_FLOWCONTROL_RTS_CTS,
    SERIAL_FLOWCONTROL_XON_XOFF
} SerialDriver_FlowControl_t;

typedef struct
{
    SerialDriver_Baudrate_t baudrate;
    SerialDriver_Parity_t parity;
    SerialDriver_StopBits_t stopBits;
    SerialDriver_DataBits_t dataBits;
    SerialDriver_FlowControl_t flowControl;
    bool enableDMA;
    bool enableInterrupt;
} SerialDriver_Config_t;

typedef void (*SerialDriver_RxCallback_t)(const uint8_t *pData, uint16_t length);
typedef void (*SerialDriver_TxCallback_t)(void);

//============================================================================
// Public Variables
//============================================================================

//============================================================================
// Public Functions
//============================================================================
SerialDriver_Status_t SerialDriverUnit_Init(const SerialDriver_Config_t *pConfig);
SerialDriver_Status_t SerialDriverUnit_Configure(SerialDriver_Baudrate_t baudrate, SerialDriver_Parity_t parity, SerialDriver_StopBits_t stopBits, SerialDriver_DataBits_t dataBits);
SerialDriver_Status_t SerialDriverUnit_Send(const uint8_t *pData, uint16_t length);
SerialDriver_Status_t SerialDriverUnit_SendWithTimeout(const uint8_t *pData, uint16_t length, uint32_t timeoutMs);
SerialDriver_Status_t SerialDriverUnit_Receive(uint8_t *pData, uint16_t maxLength, uint16_t *pReceivedLength);
SerialDriver_Status_t SerialDriverUnit_ReceiveWithTimeout(uint8_t *pData, uint16_t maxLength, uint16_t *pReceivedLength, uint32_t timeoutMs);
SerialDriver_Status_t SerialDriverUnit_GetAvailable(uint16_t *pAvailable);
SerialDriver_Status_t SerialDriverUnit_FlushRx(void);
SerialDriver_Status_t SerialDriverUnit_FlushTx(void);
SerialDriver_Status_t SerialDriverUnit_RegisterRxCallback(SerialDriver_RxCallback_t callback);
SerialDriver_Status_t SerialDriverUnit_RegisterTxCallback(SerialDriver_TxCallback_t callback);
SerialDriver_Status_t SerialDriverUnit_GetStatus(SerialDriver_Status_t *pStatus);
SerialDriver_Status_t SerialDriverUnit_DeInit(void);

#endif /* SERIALDRIVERUNIT_H */
