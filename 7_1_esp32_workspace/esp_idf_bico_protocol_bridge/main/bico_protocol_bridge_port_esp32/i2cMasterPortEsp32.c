// ESP32 implementation of the I2C master port (i2cMasterDriverPorting.h).

//============================================================================
// Dependencies
//============================================================================
#include <stddef.h>
#include "i2cMasterDriverPorting.h"
#include "i2cMasterPortEsp32Cfg.h"
#include "driver/i2c_master.h"

//============================================================================
// Variables
//============================================================================
static i2c_master_bus_handle_t busHandle = NULL;
static i2c_master_dev_handle_t devHandle = NULL;
static uint16_t devAddress = 0U;
static uint32_t busSpeedHz = 0U;

//============================================================================
// Local Function Prototypes
//============================================================================
static bool I2cMasterPort_AcquireDevice(uint16_t address);
static void I2cMasterPort_ReleaseDevice(void);
static I2cMasterPort_Result_t I2cMasterPort_ToResult(esp_err_t error);

//============================================================================
// Public Function Implementations
//============================================================================
bool I2cMasterPort_Init(uint32_t speedHz)
{
    if (busHandle != NULL)
    {
        return true;
    }

    const i2c_master_bus_config_t busCfg = {
        .i2c_port = BICO_PROTOCOL_BRIDGE_I2C_MASTER_PORT,
        .sda_io_num = BICO_PROTOCOL_BRIDGE_I2C_MASTER_SDA_PIN,
        .scl_io_num = BICO_PROTOCOL_BRIDGE_I2C_MASTER_SCL_PIN,
        .clk_source = I2C_CLK_SRC_DEFAULT,
        .glitch_ignore_cnt = BICO_PROTOCOL_BRIDGE_I2C_MASTER_GLITCH_IGNORE_CNT,
        .flags.enable_internal_pullup = BICO_PROTOCOL_BRIDGE_I2C_MASTER_INTERNAL_PULLUP,
    };
    if (i2c_new_master_bus(&busCfg, &busHandle) != ESP_OK)
    {
        busHandle = NULL;
        return false;
    }

    busSpeedHz = speedHz;
    return true;
}

void I2cMasterPort_DeInit(void)
{
    I2cMasterPort_ReleaseDevice();
    if (busHandle != NULL)
    {
        (void)i2c_del_master_bus(busHandle);
        busHandle = NULL;
    }
}

bool I2cMasterPort_SetSpeed(uint32_t speedHz)
{
    if (busHandle == NULL)
    {
        return false;
    }

    // The speed is a device property, so the cached device is created again on the next transfer.
    busSpeedHz = speedHz;
    I2cMasterPort_ReleaseDevice();
    return true;
}

I2cMasterPort_Result_t I2cMasterPort_Write(uint16_t address, const uint8_t *pData, uint16_t length, uint32_t timeoutMs)
{
    if ((pData == NULL) || !I2cMasterPort_AcquireDevice(address))
    {
        return I2CMASTERPORT_ERROR;
    }
    return I2cMasterPort_ToResult(i2c_master_transmit(devHandle, pData, length, (int)timeoutMs));
}

I2cMasterPort_Result_t I2cMasterPort_Read(uint16_t address, uint8_t *pData, uint16_t length, uint32_t timeoutMs)
{
    if ((pData == NULL) || !I2cMasterPort_AcquireDevice(address))
    {
        return I2CMASTERPORT_ERROR;
    }
    return I2cMasterPort_ToResult(i2c_master_receive(devHandle, pData, length, (int)timeoutMs));
}

I2cMasterPort_Result_t I2cMasterPort_WriteRead(uint16_t address, const uint8_t *pWriteData, uint16_t writeLength, uint8_t *pReadData, uint16_t readLength, uint32_t timeoutMs)
{
    if ((pWriteData == NULL) || (pReadData == NULL) || !I2cMasterPort_AcquireDevice(address))
    {
        return I2CMASTERPORT_ERROR;
    }
    return I2cMasterPort_ToResult(i2c_master_transmit_receive(devHandle, pWriteData, writeLength, pReadData, readLength, (int)timeoutMs));
}

bool I2cMasterPort_Probe(uint16_t address, uint32_t timeoutMs)
{
    if (busHandle == NULL)
    {
        return false;
    }
    return (i2c_master_probe(busHandle, address, (int)timeoutMs) == ESP_OK);
}

//============================================================================
// Local Function Implementations
//============================================================================
static bool I2cMasterPort_AcquireDevice(uint16_t address)
{
    if (busHandle == NULL)
    {
        return false;
    }
    if ((devHandle != NULL) && (devAddress == address))
    {
        return true;
    }

    I2cMasterPort_ReleaseDevice();
    const i2c_device_config_t devCfg = {
        .dev_addr_length = I2C_ADDR_BIT_LEN_7,
        .device_address = address,
        .scl_speed_hz = busSpeedHz,
        .scl_wait_us = BICO_PROTOCOL_BRIDGE_I2C_MASTER_SCL_WAIT_US,
    };
    if (i2c_master_bus_add_device(busHandle, &devCfg, &devHandle) != ESP_OK)
    {
        devHandle = NULL;
        return false;
    }
    devAddress = address;
    return true;
}

static void I2cMasterPort_ReleaseDevice(void)
{
    if (devHandle != NULL)
    {
        (void)i2c_master_bus_rm_device(devHandle);
        devHandle = NULL;
    }
}

static I2cMasterPort_Result_t I2cMasterPort_ToResult(esp_err_t error)
{
    if (error == ESP_OK)
    {
        return I2CMASTERPORT_OK;
    }
    return (error == ESP_ERR_TIMEOUT) ? I2CMASTERPORT_TIMEOUT : I2CMASTERPORT_ERROR;
}
