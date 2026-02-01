// Serial Driver Unit Implementation

#include "serialDriver.h"
#include "serialDriverCfg.h"
#include "serialDriverUnit.h"

//============================================================================
// Local Types
//============================================================================
typedef struct
{
    uint8_t initialized;
    SerialDriver_Baudrate_t baudrate;
} SerialDriver_Context_t;

//============================================================================
// Variables
//============================================================================
static SerialDriver_Context_t serialContext = {0};

//============================================================================
// Public Function Implementations
//============================================================================

SerialDriver_Status_t SerialDriver_Init(SerialDriver_Baudrate_t baudrate)
{
    // TODO: Add vendor-specific HAL UART initialization here
    
    serialContext.initialized = 1;
    serialContext.baudrate = baudrate;
    
    return SERIAL_STATUS_OK;
}

SerialDriver_Status_t SerialDriver_Send(const uint8_t *pData, uint16_t length)
{
    if (pData == NULL || length == 0)
    {
        return SERIAL_STATUS_ERROR;
    }
    
    if (!serialContext.initialized)
    {
        return SERIAL_STATUS_ERROR;
    }
    
    // TODO: Add vendor-specific HAL UART transmit here
    
    return SERIAL_STATUS_OK;
}

SerialDriver_Status_t SerialDriver_Receive(uint8_t *pData, uint16_t length, uint16_t *pReceivedLength)
{
    if (pData == NULL || pReceivedLength == NULL)
    {
        return SERIAL_STATUS_ERROR;
    }
    
    if (!serialContext.initialized)
    {
        return SERIAL_STATUS_ERROR;
    }
    
    // TODO: Add vendor-specific HAL UART receive here
    
    *pReceivedLength = 0;
    
    return SERIAL_STATUS_OK;
}

SerialDriver_Status_t SerialDriver_DeInit(void)
{
    // TODO: Add vendor-specific HAL deinitialization here
    
    serialContext.initialized = 0;
    
    return SERIAL_STATUS_OK;
}
