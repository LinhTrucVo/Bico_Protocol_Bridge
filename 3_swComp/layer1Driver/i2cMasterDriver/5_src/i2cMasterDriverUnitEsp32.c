// ESP32 variant implementation for I2cMasterDriver. (i2cMasterDriverUnitEsp32.c)
// This file provides the ESP32-specific implementation of the I2cMasterDriver interface.
// Selected when L1_VARIANT is set to "Esp32" in the CMake build configuration.

//============================================================================
// Dependencies
//============================================================================
#include "i2cMasterDriver.h"
#include "i2cMasterDriverCfg.h"
#include "i2cMasterDriverUnit.h"
#include "driver/i2c_master.h"
#include <string.h>

//============================================================================
// Internal Defines
//============================================================================
#define I2C_ESP32_PORT          I2C_NUM_0
#define I2C_ESP32_PIN_SDA       21
#define I2C_ESP32_PIN_SCL       22
#define I2C_ESP32_GLITCH_MS     7

//============================================================================
// Internal Types
//============================================================================
typedef struct
{
    bool                        initialized;
    i2c_master_bus_handle_t     busHandle;
    i2c_master_dev_handle_t     devHandle;
    I2cMasterDriver_Config_t    config;
    I2cMasterDriver_Callback_t  callback;
    I2cMasterDriver_Address_t   lastAddress;
} I2cMasterDriver_Context_t;

static I2cMasterDriver_Context_t context = {0};

//============================================================================
// Internal Functions
//============================================================================
static esp_err_t AcquireDevice(I2cMasterDriver_Address_t address, uint32_t timeoutMs)
{
    if (context.devHandle != NULL && context.lastAddress == address)
    {
        return ESP_OK;
    }
    if (context.devHandle != NULL)
    {
        (void)i2c_master_bus_rm_device(context.devHandle);
        context.devHandle = NULL;
    }
    i2c_device_config_t devCfg = {
        .dev_addr_length = I2C_ADDR_BIT_LEN_7,
        .device_address  = address,
        .scl_speed_hz    = context.config.speed,
    };
    context.lastAddress = address;
    return i2c_master_bus_add_device(context.busHandle, &devCfg, &context.devHandle);
}

//============================================================================
// Public Functions
//============================================================================
I2cMasterDriver_Status_t I2cMasterDriverUnit_Init(const I2cMasterDriver_Config_t *pConfig)
{
    if (pConfig == NULL) { return I2CMASTERDRIVERSTATUS_INVALID_PARAM; }

    i2c_master_bus_config_t busCfg = {
        .i2c_port            = I2C_ESP32_PORT,
        .sda_io_num          = I2C_ESP32_PIN_SDA,
        .scl_io_num          = I2C_ESP32_PIN_SCL,
        .clk_source          = I2C_CLK_SRC_DEFAULT,
        .glitch_ignore_cnt   = I2C_ESP32_GLITCH_MS,
        .flags.enable_internal_pullup = true,
    };
    if (i2c_new_master_bus(&busCfg, &context.busHandle) != ESP_OK)
    {
        return I2CMASTERDRIVERSTATUS_ERROR;
    }
    (void)memcpy(&context.config, pConfig, sizeof(I2cMasterDriver_Config_t));
    context.initialized = true;
    return I2CMASTERDRIVERSTATUS_OK;
}

I2cMasterDriver_Status_t I2cMasterDriverUnit_SetSpeed(I2cMasterDriver_Speed_t speed)
{
    if (!context.initialized) { return I2CMASTERDRIVERSTATUS_INVALID_PARAM; }
    context.config.speed = speed;
    return I2CMASTERDRIVERSTATUS_OK;
}

I2cMasterDriver_Status_t I2cMasterDriverUnit_Write(I2cMasterDriver_Address_t address,
                                                    const uint8_t *pData, uint16_t length)
{
    if (!context.initialized) { return I2CMASTERDRIVERSTATUS_INVALID_PARAM; }
    if (pData == NULL || length == 0U) { return I2CMASTERDRIVERSTATUS_INVALID_PARAM; }
    if (AcquireDevice(address, context.config.timeoutMs) != ESP_OK) { return I2CMASTERDRIVERSTATUS_ERROR; }

    esp_err_t ret = i2c_master_transmit(context.devHandle, pData, length,
                                        (int)context.config.timeoutMs);
    if (context.callback != NULL)
    {
        context.callback((ret == ESP_OK) ? I2CMASTERDRIVERSTATUS_OK : I2CMASTERDRIVERSTATUS_ERROR);
    }
    return (ret == ESP_OK) ? I2CMASTERDRIVERSTATUS_OK : I2CMASTERDRIVERSTATUS_ERROR;
}

I2cMasterDriver_Status_t I2cMasterDriverUnit_WriteWithTimeout(I2cMasterDriver_Address_t address,
                                                               const uint8_t *pData, uint16_t length,
                                                               uint32_t timeoutMs)
{
    if (!context.initialized) { return I2CMASTERDRIVERSTATUS_INVALID_PARAM; }
    if (pData == NULL || length == 0U) { return I2CMASTERDRIVERSTATUS_INVALID_PARAM; }
    if (AcquireDevice(address, timeoutMs) != ESP_OK) { return I2CMASTERDRIVERSTATUS_ERROR; }

    esp_err_t ret = i2c_master_transmit(context.devHandle, pData, length, (int)timeoutMs);
    if (ret == ESP_ERR_TIMEOUT) { return I2CMASTERDRIVERSTATUS_TIMEOUT; }
    return (ret == ESP_OK) ? I2CMASTERDRIVERSTATUS_OK : I2CMASTERDRIVERSTATUS_ERROR;
}

I2cMasterDriver_Status_t I2cMasterDriverUnit_Read(I2cMasterDriver_Address_t address,
                                                   uint8_t *pData, uint16_t length)
{
    if (!context.initialized) { return I2CMASTERDRIVERSTATUS_INVALID_PARAM; }
    if (pData == NULL || length == 0U) { return I2CMASTERDRIVERSTATUS_INVALID_PARAM; }
    if (AcquireDevice(address, context.config.timeoutMs) != ESP_OK) { return I2CMASTERDRIVERSTATUS_ERROR; }

    esp_err_t ret = i2c_master_receive(context.devHandle, pData, length,
                                       (int)context.config.timeoutMs);
    return (ret == ESP_OK) ? I2CMASTERDRIVERSTATUS_OK : I2CMASTERDRIVERSTATUS_ERROR;
}

I2cMasterDriver_Status_t I2cMasterDriverUnit_ReadWithTimeout(I2cMasterDriver_Address_t address,
                                                              uint8_t *pData, uint16_t length,
                                                              uint32_t timeoutMs)
{
    if (!context.initialized) { return I2CMASTERDRIVERSTATUS_INVALID_PARAM; }
    if (pData == NULL || length == 0U) { return I2CMASTERDRIVERSTATUS_INVALID_PARAM; }
    if (AcquireDevice(address, timeoutMs) != ESP_OK) { return I2CMASTERDRIVERSTATUS_ERROR; }

    esp_err_t ret = i2c_master_receive(context.devHandle, pData, length, (int)timeoutMs);
    if (ret == ESP_ERR_TIMEOUT) { return I2CMASTERDRIVERSTATUS_TIMEOUT; }
    return (ret == ESP_OK) ? I2CMASTERDRIVERSTATUS_OK : I2CMASTERDRIVERSTATUS_ERROR;
}

I2cMasterDriver_Status_t I2cMasterDriverUnit_WriteRead(I2cMasterDriver_Address_t address,
                                                        const uint8_t *pWriteData, uint16_t writeLength,
                                                        uint8_t *pReadData, uint16_t readLength)
{
    if (!context.initialized) { return I2CMASTERDRIVERSTATUS_INVALID_PARAM; }
    if (AcquireDevice(address, context.config.timeoutMs) != ESP_OK) { return I2CMASTERDRIVERSTATUS_ERROR; }

    esp_err_t ret = i2c_master_transmit_receive(context.devHandle, pWriteData, writeLength,
                                                pReadData, readLength,
                                                (int)context.config.timeoutMs);
    return (ret == ESP_OK) ? I2CMASTERDRIVERSTATUS_OK : I2CMASTERDRIVERSTATUS_ERROR;
}

I2cMasterDriver_Status_t I2cMasterDriverUnit_WriteRegister(I2cMasterDriver_Address_t address,
                                                            uint8_t regAddress,
                                                            const uint8_t *pData, uint16_t length)
{
    if (!context.initialized) { return I2CMASTERDRIVERSTATUS_INVALID_PARAM; }
    if (pData == NULL) { return I2CMASTERDRIVERSTATUS_INVALID_PARAM; }

    uint8_t buf[I2C_MASTER_CFG_MAX_TRANSFER + 1U];
    buf[0] = regAddress;
    (void)memcpy(&buf[1], pData, length);
    return I2cMasterDriverUnit_Write(address, buf, (uint16_t)(length + 1U));
}

I2cMasterDriver_Status_t I2cMasterDriverUnit_ReadRegister(I2cMasterDriver_Address_t address,
                                                           uint8_t regAddress,
                                                           uint8_t *pData, uint16_t length)
{
    if (!context.initialized) { return I2CMASTERDRIVERSTATUS_INVALID_PARAM; }
    return I2cMasterDriverUnit_WriteRead(address, &regAddress, 1U, pData, length);
}

I2cMasterDriver_Status_t I2cMasterDriverUnit_ScanBus(I2cMasterDriver_Address_t *pFoundAddresses,
                                                      uint8_t maxAddresses, uint8_t *pNumFound)
{
    if (!context.initialized) { return I2CMASTERDRIVERSTATUS_INVALID_PARAM; }
    if (pFoundAddresses == NULL || pNumFound == NULL) { return I2CMASTERDRIVERSTATUS_INVALID_PARAM; }

    *pNumFound = 0U;
    for (uint16_t addr = 0x08U; addr <= 0x77U && (*pNumFound) < maxAddresses; addr++)
    {
        if (i2c_master_probe(context.busHandle, (uint16_t)addr, 10) == ESP_OK)
        {
            pFoundAddresses[(*pNumFound)++] = (I2cMasterDriver_Address_t)addr;
        }
    }
    return I2CMASTERDRIVERSTATUS_OK;
}

I2cMasterDriver_Status_t I2cMasterDriverUnit_IsBusy(bool *pIsBusy)
{
    if (!context.initialized) { return I2CMASTERDRIVERSTATUS_INVALID_PARAM; }
    if (pIsBusy == NULL) { return I2CMASTERDRIVERSTATUS_INVALID_PARAM; }
    *pIsBusy = (i2c_master_bus_wait_all_done(context.busHandle, 0) != ESP_OK);
    return I2CMASTERDRIVERSTATUS_OK;
}

I2cMasterDriver_Status_t I2cMasterDriverUnit_RegisterCallback(I2cMasterDriver_Callback_t callback)
{
    if (!context.initialized) { return I2CMASTERDRIVERSTATUS_INVALID_PARAM; }
    context.callback = callback;
    return I2CMASTERDRIVERSTATUS_OK;
}

I2cMasterDriver_Status_t I2cMasterDriverUnit_DeInit(void)
{
    if (!context.initialized) { return I2CMASTERDRIVERSTATUS_INVALID_PARAM; }
    if (context.devHandle != NULL)
    {
        (void)i2c_master_bus_rm_device(context.devHandle);
        context.devHandle = NULL;
    }
    (void)i2c_del_master_bus(context.busHandle);
    context.initialized = false;
    return I2CMASTERDRIVERSTATUS_OK;
}
