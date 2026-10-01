// ESP32 implementation of the I2C slave port (i2cSlaveDriverPorting.h).
// Requires CONFIG_I2C_ENABLE_SLAVE_DRIVER_VERSION_2 (request/receive events).

//============================================================================
// Dependencies
//============================================================================
#include <stddef.h>
#include "i2cSlaveDriverPorting.h"
#include "i2cSlavePortEsp32Cfg.h"
#include "driver/i2c_slave.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

//============================================================================
// Variables
//============================================================================
static i2c_slave_dev_handle_t slaveHandle = NULL;
static TaskHandle_t requestTask = NULL;
static I2cSlavePort_ReceiveHandler_t receiveHandler = NULL;
static I2cSlavePort_RequestHandler_t requestHandler = NULL;

//============================================================================
// Local Function Prototypes
//============================================================================
static bool I2cSlavePort_OnReceive(i2c_slave_dev_handle_t handle, const i2c_slave_rx_done_event_data_t *pEvent, void *pArg);
static bool I2cSlavePort_OnRequest(i2c_slave_dev_handle_t handle, const i2c_slave_request_event_data_t *pEvent, void *pArg);
static void I2cSlavePort_RequestTask(void *pArg);

//============================================================================
// Public Function Implementations
//============================================================================
bool I2cSlavePort_Init(uint16_t address)
{
    if (slaveHandle != NULL)
    {
        return true;
    }

    const i2c_slave_config_t slaveCfg = {
        .i2c_port = BICO_PROTOCOL_BRIDGE_I2C_SLAVE_PORT,
        .sda_io_num = BICO_PROTOCOL_BRIDGE_I2C_SLAVE_SDA_PIN,
        .scl_io_num = BICO_PROTOCOL_BRIDGE_I2C_SLAVE_SCL_PIN,
        .clk_source = I2C_CLK_SRC_DEFAULT,
        .send_buf_depth = BICO_PROTOCOL_BRIDGE_I2C_SLAVE_TX_BUFFER_DEPTH,
        .receive_buf_depth = BICO_PROTOCOL_BRIDGE_I2C_SLAVE_RX_BUFFER_DEPTH,
        .slave_addr = address,
        .addr_bit_len = I2C_ADDR_BIT_LEN_7,
        .flags.enable_internal_pullup = BICO_PROTOCOL_BRIDGE_I2C_SLAVE_INTERNAL_PULLUP,
    };
    if (i2c_new_slave_device(&slaveCfg, &slaveHandle) != ESP_OK)
    {
        slaveHandle = NULL;
        return false;
    }

    if (xTaskCreate(I2cSlavePort_RequestTask, "i2cSlaveReq", BICO_PROTOCOL_BRIDGE_I2C_SLAVE_TASK_STACK_SIZE, NULL,
                    BICO_PROTOCOL_BRIDGE_I2C_SLAVE_TASK_PRIORITY, &requestTask) != pdPASS)
    {
        requestTask = NULL;
        I2cSlavePort_DeInit();
        return false;
    }

    const i2c_slave_event_callbacks_t callbacks = {
        .on_receive = I2cSlavePort_OnReceive,
        .on_request = I2cSlavePort_OnRequest,
    };
    if (i2c_slave_register_event_callbacks(slaveHandle, &callbacks, NULL) != ESP_OK)
    {
        I2cSlavePort_DeInit();
        return false;
    }
    return true;
}

void I2cSlavePort_DeInit(void)
{
    if (requestTask != NULL)
    {
        vTaskDelete(requestTask);
        requestTask = NULL;
    }
    if (slaveHandle != NULL)
    {
        (void)i2c_del_slave_device(slaveHandle);
        slaveHandle = NULL;
    }
    receiveHandler = NULL;
    requestHandler = NULL;
}

bool I2cSlavePort_Write(const uint8_t *pData, uint16_t length, uint32_t timeoutMs)
{
    if ((slaveHandle == NULL) || (pData == NULL))
    {
        return false;
    }

    uint32_t written = 0U;
    return (i2c_slave_write(slaveHandle, pData, length, &written, (int)timeoutMs) == ESP_OK) && (written > 0U);
}

void I2cSlavePort_SetReceiveHandler(I2cSlavePort_ReceiveHandler_t handler)
{
    receiveHandler = handler;
}

void I2cSlavePort_SetRequestHandler(I2cSlavePort_RequestHandler_t handler)
{
    requestHandler = handler;
}

//============================================================================
// Local Function Implementations
//============================================================================
static bool IRAM_ATTR I2cSlavePort_OnReceive(i2c_slave_dev_handle_t handle, const i2c_slave_rx_done_event_data_t *pEvent, void *pArg)
{
    (void)handle;
    (void)pArg;

    if (receiveHandler != NULL)
    {
        receiveHandler(pEvent->buffer, (uint16_t)pEvent->length);
    }
    return false;
}

static bool IRAM_ATTR I2cSlavePort_OnRequest(i2c_slave_dev_handle_t handle, const i2c_slave_request_event_data_t *pEvent, void *pArg)
{
    (void)handle;
    (void)pEvent;
    (void)pArg;

    BaseType_t higherPriorityTaskWoken = pdFALSE;
    if (requestTask != NULL)
    {
        vTaskNotifyGiveFromISR(requestTask, &higherPriorityTaskWoken);
    }
    return (higherPriorityTaskWoken == pdTRUE);
}

static void I2cSlavePort_RequestTask(void *pArg)
{
    (void)pArg;

    for (;;)
    {
        (void)ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
        if (requestHandler != NULL)
        {
            requestHandler();
        }
    }
}
