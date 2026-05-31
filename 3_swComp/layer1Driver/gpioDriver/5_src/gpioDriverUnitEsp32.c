// ESP32 variant implementation for GpioDriver. (gpioDriverUnitEsp32.c)
// This file provides the ESP32-specific implementation of the GpioDriver interface.
// Selected when L1_VARIANT is set to "Esp32" in the CMake build configuration.

//============================================================================
// Dependencies
//============================================================================
#include "gpioDriver.h"
#include "gpioDriverCfg.h"
#include "gpioDriverUnit.h"
#include "driver/gpio.h"

//============================================================================
// Internal Types
//============================================================================
typedef struct
{
    GpioDriver_InterruptCallback_t callbacks[GPIO_CFG_MAX_PINS];
    bool initialized;
} GpioDriver_Context_t;

static GpioDriver_Context_t context = {0};

//============================================================================
// Internal Functions
//============================================================================
static void IRAM_ATTR GpioIsrHandler(void *arg)
{
    uint32_t pin = (uint32_t)(uintptr_t)arg;
    if (pin < GPIO_CFG_MAX_PINS && context.callbacks[pin] != NULL)
    {
        context.callbacks[pin]((GpioDriver_Pin_t)pin);
    }
}

//============================================================================
// Public Functions
//============================================================================
GpioDriver_Status_t GpioDriverUnit_Init(const GpioDriver_Config_t *pConfig)
{
    if (pConfig == NULL) { return GPIO_STATUS_ERROR; }
    gpio_install_isr_service(0);
    context.initialized = true;
    return GPIO_STATUS_OK;
}

GpioDriver_Status_t GpioDriverUnit_ConfigurePin(GpioDriver_Pin_t pin, const GpioDriver_PinConfig_t *pConfig)
{
    if (!context.initialized) { return GPIO_STATUS_NOT_INITIALIZED; }
    if (pConfig == NULL || pin >= GPIO_CFG_MAX_PINS) { return GPIO_STATUS_INVALID_PIN; }

    gpio_config_t cfg = {0};
    cfg.pin_bit_mask = (1ULL << pin);
    cfg.intr_type    = GPIO_INTR_DISABLE;

    switch (pConfig->mode)
    {
        case GPIO_MODE_OUTPUT:   cfg.mode = GPIO_MODE_OUTPUT;  break;
        case GPIO_MODE_INPUT:    cfg.mode = GPIO_MODE_INPUT;   break;
        default:                 cfg.mode = GPIO_MODE_DISABLE; break;
    }
    switch (pConfig->pull)
    {
        case GPIO_PULL_UP:   cfg.pull_up_en = 1; cfg.pull_down_en = 0; break;
        case GPIO_PULL_DOWN: cfg.pull_up_en = 0; cfg.pull_down_en = 1; break;
        default:             cfg.pull_up_en = 0; cfg.pull_down_en = 0; break;
    }
    if (gpio_config(&cfg) != ESP_OK) { return GPIO_STATUS_ERROR; }
    gpio_set_drive_capability((gpio_num_t)pin, (gpio_drive_cap_t)pConfig->ioCapability);
    if (pConfig->mode == GPIO_MODE_OUTPUT)
    {
        gpio_set_level((gpio_num_t)pin, (uint32_t)pConfig->initialState);
    }
    return GPIO_STATUS_OK;
}

GpioDriver_Status_t GpioDriverUnit_SetMode(GpioDriver_Pin_t pin, GpioDriver_Mode_t mode)
{
    if (!context.initialized) { return GPIO_STATUS_NOT_INITIALIZED; }
    gpio_mode_t espMode = (mode == GPIO_MODE_OUTPUT) ? GPIO_MODE_OUTPUT : GPIO_MODE_INPUT;
    return (gpio_set_direction((gpio_num_t)pin, espMode) == ESP_OK) ? GPIO_STATUS_OK : GPIO_STATUS_ERROR;
}

GpioDriver_Status_t GpioDriverUnit_SetPull(GpioDriver_Pin_t pin, GpioDriver_Pull_t pull)
{
    if (!context.initialized) { return GPIO_STATUS_NOT_INITIALIZED; }
    gpio_pull_mode_t espPull;
    switch (pull)
    {
        case GPIO_PULL_UP:   espPull = GPIO_PULLUP_ONLY;   break;
        case GPIO_PULL_DOWN: espPull = GPIO_PULLDOWN_ONLY; break;
        default:             espPull = GPIO_FLOATING;      break;
    }
    return (gpio_set_pull_mode((gpio_num_t)pin, espPull) == ESP_OK) ? GPIO_STATUS_OK : GPIO_STATUS_ERROR;
}

GpioDriver_Status_t GpioDriverUnit_SetSpeed(GpioDriver_Pin_t pin, GpioDriver_Speed_t speed)
{
    (void)pin; (void)speed;
    return GPIO_STATUS_OK; /* Not configurable on ESP32 */
}

GpioDriver_Status_t GpioDriverUnit_SetIOCapability(GpioDriver_Pin_t pin, GpioDriver_IOCapability_t capability)
{
    if (!context.initialized) { return GPIO_STATUS_NOT_INITIALIZED; }
    return (gpio_set_drive_capability((gpio_num_t)pin, (gpio_drive_cap_t)capability) == ESP_OK)
        ? GPIO_STATUS_OK : GPIO_STATUS_ERROR;
}

GpioDriver_Status_t GpioDriverUnit_WritePin(GpioDriver_Pin_t pin, GpioDriver_State_t state)
{
    if (!context.initialized) { return GPIO_STATUS_NOT_INITIALIZED; }
    return (gpio_set_level((gpio_num_t)pin, (uint32_t)state) == ESP_OK) ? GPIO_STATUS_OK : GPIO_STATUS_ERROR;
}

GpioDriver_Status_t GpioDriverUnit_ReadPin(GpioDriver_Pin_t pin, GpioDriver_State_t *pState)
{
    if (!context.initialized) { return GPIO_STATUS_NOT_INITIALIZED; }
    if (pState == NULL) { return GPIO_STATUS_ERROR; }
    *pState = (GpioDriver_State_t)gpio_get_level((gpio_num_t)pin);
    return GPIO_STATUS_OK;
}

GpioDriver_Status_t GpioDriverUnit_TogglePin(GpioDriver_Pin_t pin)
{
    if (!context.initialized) { return GPIO_STATUS_NOT_INITIALIZED; }
    int level = gpio_get_level((gpio_num_t)pin);
    return (gpio_set_level((gpio_num_t)pin, (uint32_t)(level ^ 1)) == ESP_OK)
        ? GPIO_STATUS_OK : GPIO_STATUS_ERROR;
}

GpioDriver_Status_t GpioDriverUnit_EnableInterrupt(GpioDriver_Pin_t pin, GpioDriver_InterruptEdge_t edge,
                                                    GpioDriver_InterruptCallback_t callback)
{
    if (!context.initialized) { return GPIO_STATUS_NOT_INITIALIZED; }
    if (pin >= GPIO_CFG_MAX_PINS || callback == NULL) { return GPIO_STATUS_INVALID_PIN; }

    gpio_int_type_t espEdge;
    switch (edge)
    {
        case GPIO_INTERRUPT_RISING:  espEdge = GPIO_INTR_POSEDGE; break;
        case GPIO_INTERRUPT_FALLING: espEdge = GPIO_INTR_NEGEDGE; break;
        default:                     espEdge = GPIO_INTR_ANYEDGE; break;
    }
    context.callbacks[pin] = callback;
    gpio_set_intr_type((gpio_num_t)pin, espEdge);
    gpio_isr_handler_add((gpio_num_t)pin, GpioIsrHandler, (void *)(uintptr_t)pin);
    gpio_intr_enable((gpio_num_t)pin);
    return GPIO_STATUS_OK;
}

GpioDriver_Status_t GpioDriverUnit_DisableInterrupt(GpioDriver_Pin_t pin)
{
    if (!context.initialized) { return GPIO_STATUS_NOT_INITIALIZED; }
    if (pin >= GPIO_CFG_MAX_PINS) { return GPIO_STATUS_INVALID_PIN; }
    gpio_intr_disable((gpio_num_t)pin);
    gpio_isr_handler_remove((gpio_num_t)pin);
    context.callbacks[pin] = NULL;
    return GPIO_STATUS_OK;
}

GpioDriver_Status_t GpioDriverUnit_DeInit(void)
{
    for (uint8_t i = 0U; i < GPIO_CFG_MAX_PINS; i++)
    {
        if (context.callbacks[i] != NULL)
        {
            gpio_isr_handler_remove((gpio_num_t)i);
            context.callbacks[i] = NULL;
        }
    }
    gpio_uninstall_isr_service();
    context.initialized = false;
    return GPIO_STATUS_OK;
}
