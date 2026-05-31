// ESP32 variant implementation for I2cSlaveDriver. (i2cSlaveDriverUnitEsp32.c)
// This file provides the ESP32-specific implementation of the I2cSlaveDriver interface.
// Selected when L1_VARIANT is set to "Esp32" in the CMake build configuration.

//============================================================================
// Dependencies
//============================================================================
#include "i2cSlaveDriver.h"
#include "i2cSlaveDriverCfg.h"
#include "i2cSlaveDriverUnit.h"
#include "driver/i2c_slave.h"
#include <string.h>

//============================================================================
// Internal Defines
//============================================================================
#define I2C_SLAVE_ESP32_PORT        I2C_NUM_0
#define I2C_SLAVE_ESP32_PIN_SDA     21
#define I2C_SLAVE_ESP32_PIN_SCL     22
#define I2C_SLAVE_ESP32_BUFSIZE     I2C_SLAVE_CFG_BUFFER_SIZE

//============================================================================
// Internal Types
//============================================================================
typedef struct
{
    bool                                initialized;
    i2c_slave_dev_handle_t              devHandle;
    I2cSlaveDriver_Address_t            address;
    bool                                addressed;
    uint8_t                             rxBuffer[I2C_SLAVE_CFG_BUFFER_SIZE];
    uint16_t                            rxLength;
    uint8_t                             txBuffer[I2C_SLAVE_CFG_BUFFER_SIZE];
    uint16_t                            txLength;
    I2cSlaveDriver_RxCallback_t         rxCallback;
    I2cSlaveDriver_TxCallback_t         txCallback;
    I2cSlaveDriver_AddrMatchCallback_t  addrMatchCallback;
} I2cSlaveDriver_Context_t;

static I2cSlaveDriver_Context_t context = {0};

//============================================================================
// Internal ISR Callbacks
//============================================================================
static bool IRAM_ATTR SlaveRxDone(i2c_slave_dev_handle_t handle,
                                   const i2c_slave_rx_done_event_data_t *pEventData,
                                   void *pUserData)
{
    (void)handle;
    (void)pUserData;
    context.rxLength = (uint16_t)pEventData->buffer_size;
    (void)memcpy(context.rxBuffer, pEventData->buffer, context.rxLength);
    if (context.rxCallback != NULL)
    {
        context.rxCallback(context.rxBuffer, context.rxLength);
    }
    context.addressed = false;
    return false; /* no high-priority task woken */
}

//============================================================================
// Public Functions
//============================================================================
I2cSlaveDriver_Status_t I2cSlaveDriverUnit_Init(const I2cSlaveDriver_Config_t *pConfig)
{
    if (pConfig == NULL) { return I2CSLAVEDRIVERSTATUS_INVALID_PARAM; }

    i2c_slave_config_t slaveCfg = {
        .i2c_port              = I2C_SLAVE_ESP32_PORT,
        .sda_io_num            = I2C_SLAVE_ESP32_PIN_SDA,
        .scl_io_num            = I2C_SLAVE_ESP32_PIN_SCL,
        .clk_source            = I2C_CLK_SRC_DEFAULT,
        .send_buf_depth        = I2C_SLAVE_ESP32_BUFSIZE,
        .slave_addr            = pConfig->address,
        .addr_bit_len          = I2C_ADDR_BIT_LEN_7,
        .flags.broadcast_en    = false,
    };
    if (i2c_new_slave_device(&slaveCfg, &context.devHandle) != ESP_OK)
    {
        return I2CSLAVEDRIVERSTATUS_ERROR;
    }

    i2c_slave_event_callbacks_t cbs = {
        .on_recv_done = SlaveRxDone,
    };
    if (i2c_slave_register_event_callbacks(context.devHandle, &cbs, NULL) != ESP_OK)
    {
        (void)i2c_del_slave_device(context.devHandle);
        return I2CSLAVEDRIVERSTATUS_ERROR;
    }

    context.address     = pConfig->address;
    context.initialized = true;
    return I2CSLAVEDRIVERSTATUS_OK;
}

I2cSlaveDriver_Status_t I2cSlaveDriverUnit_SetAddress(I2cSlaveDriver_Address_t address)
{
    if (!context.initialized) { return I2CSLAVEDRIVERSTATUS_INVALID_PARAM; }
    /* Changing address requires reinitialization on ESP32 */
    context.address = address;
    return I2CSLAVEDRIVERSTATUS_OK;
}

I2cSlaveDriver_Status_t I2cSlaveDriverUnit_GetAddress(I2cSlaveDriver_Address_t *pAddress)
{
    if (!context.initialized) { return I2CSLAVEDRIVERSTATUS_INVALID_PARAM; }
    if (pAddress == NULL) { return I2CSLAVEDRIVERSTATUS_INVALID_PARAM; }
    *pAddress = context.address;
    return I2CSLAVEDRIVERSTATUS_OK;
}

I2cSlaveDriver_Status_t I2cSlaveDriverUnit_SetTxBuffer(const uint8_t *pData, uint16_t length)
{
    if (!context.initialized) { return I2CSLAVEDRIVERSTATUS_INVALID_PARAM; }
    if (pData == NULL || length == 0U) { return I2CSLAVEDRIVERSTATUS_INVALID_PARAM; }

    (void)memcpy(context.txBuffer, pData, length);
    context.txLength = length;
    if (i2c_slave_write(context.devHandle, pData, length, 100) != ESP_OK)
    {
        return I2CSLAVEDRIVERSTATUS_ERROR;
    }
    if (context.txCallback != NULL) { context.txCallback(length); }
    return I2CSLAVEDRIVERSTATUS_OK;
}

I2cSlaveDriver_Status_t I2cSlaveDriverUnit_SetRxBuffer(uint8_t *pData, uint16_t maxLength)
{
    if (!context.initialized) { return I2CSLAVEDRIVERSTATUS_INVALID_PARAM; }
    if (pData == NULL || maxLength == 0U) { return I2CSLAVEDRIVERSTATUS_INVALID_PARAM; }
    /* On ESP32 the RX buffer is managed internally; copy last received data out */
    (void)memcpy(pData, context.rxBuffer,
                 (context.rxLength < maxLength) ? context.rxLength : maxLength);
    return I2CSLAVEDRIVERSTATUS_OK;
}

I2cSlaveDriver_Status_t I2cSlaveDriverUnit_GetRxLength(uint16_t *pLength)
{
    if (!context.initialized) { return I2CSLAVEDRIVERSTATUS_INVALID_PARAM; }
    if (pLength == NULL) { return I2CSLAVEDRIVERSTATUS_INVALID_PARAM; }
    *pLength = context.rxLength;
    return I2CSLAVEDRIVERSTATUS_OK;
}

I2cSlaveDriver_Status_t I2cSlaveDriverUnit_IsAddressed(bool *pIsAddressed)
{
    if (!context.initialized) { return I2CSLAVEDRIVERSTATUS_INVALID_PARAM; }
    if (pIsAddressed == NULL) { return I2CSLAVEDRIVERSTATUS_INVALID_PARAM; }
    *pIsAddressed = context.addressed;
    return I2CSLAVEDRIVERSTATUS_OK;
}

I2cSlaveDriver_Status_t I2cSlaveDriverUnit_RegisterRxCallback(I2cSlaveDriver_RxCallback_t callback)
{
    if (!context.initialized) { return I2CSLAVEDRIVERSTATUS_INVALID_PARAM; }
    context.rxCallback = callback;
    return I2CSLAVEDRIVERSTATUS_OK;
}

I2cSlaveDriver_Status_t I2cSlaveDriverUnit_RegisterTxCallback(I2cSlaveDriver_TxCallback_t callback)
{
    if (!context.initialized) { return I2CSLAVEDRIVERSTATUS_INVALID_PARAM; }
    context.txCallback = callback;
    return I2CSLAVEDRIVERSTATUS_OK;
}

I2cSlaveDriver_Status_t I2cSlaveDriverUnit_RegisterAddressMatchCallback(
    I2cSlaveDriver_AddrMatchCallback_t callback)
{
    if (!context.initialized) { return I2CSLAVEDRIVERSTATUS_INVALID_PARAM; }
    context.addrMatchCallback = callback;
    return I2CSLAVEDRIVERSTATUS_OK;
}

I2cSlaveDriver_Status_t I2cSlaveDriverUnit_DeInit(void)
{
    if (!context.initialized) { return I2CSLAVEDRIVERSTATUS_INVALID_PARAM; }
    (void)i2c_del_slave_device(context.devHandle);
    (void)memset(&context, 0, sizeof(context));
    return I2CSLAVEDRIVERSTATUS_OK;
}
