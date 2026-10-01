// ESP32 implementation of the GPIO port (gpioDriverPorting.h).

//============================================================================
// Dependencies
//============================================================================
#include <stddef.h>
#include <stdint.h>
#include "gpioDriverPorting.h"
#include "gpioPortEsp32Cfg.h"
#include "driver/gpio.h"
#include "esp_attr.h"
#include "soc/soc_caps.h"

//============================================================================
// Variables
//============================================================================
static GpioPort_InterruptHandler_t interruptHandler = NULL;
static bool isrServiceInstalledByPort = false;

//============================================================================
// Local Function Prototypes
//============================================================================
static void GpioPort_OnIsr(void *pArg);
static uint8_t GpioPort_LimitDriveStrength(uint8_t driveStrength);
static bool GpioPort_IsValidPin(uint8_t pin);
static bool GpioPort_IsValidOutputPin(uint8_t pin);

//============================================================================
// Public Function Implementations
//============================================================================
bool GpioPort_Init(void)
{
    const esp_err_t result = gpio_install_isr_service(BICO_PROTOCOL_BRIDGE_GPIO_ISR_FLAGS);
    if (result == ESP_OK)
    {
        isrServiceInstalledByPort = true;
    }
    // ESP_ERR_INVALID_STATE: the service is already installed by another component.
    return ((result == ESP_OK) || (result == ESP_ERR_INVALID_STATE));
}

void GpioPort_DeInit(void)
{
    if (isrServiceInstalledByPort)
    {
        gpio_uninstall_isr_service();
        isrServiceInstalledByPort = false;
    }
    interruptHandler = NULL;
}

bool GpioPort_ConfigurePin(uint8_t pin, GpioPort_Mode_t mode, GpioPort_Pull_t pull, uint8_t driveStrength, bool initialHigh)
{
    if (!GpioPort_IsValidPin(pin))
    {
        return false;
    }

    gpio_config_t cfg = {0};
    cfg.pin_bit_mask = (1ULL << pin);
    cfg.intr_type = GPIO_INTR_DISABLE;
    cfg.pull_up_en = (pull == GPIOPORT_PULL_UP) ? GPIO_PULLUP_ENABLE : GPIO_PULLUP_DISABLE;
    cfg.pull_down_en = (pull == GPIOPORT_PULL_DOWN) ? GPIO_PULLDOWN_ENABLE : GPIO_PULLDOWN_DISABLE;

    switch (mode)
    {
        case GPIOPORT_MODE_OUTPUT:
            cfg.mode = GPIO_MODE_INPUT_OUTPUT; // input stays enabled so the level can be read back
            break;
        case GPIOPORT_MODE_INPUT:
            cfg.mode = GPIO_MODE_INPUT;
            break;
        default:
            cfg.mode = GPIO_MODE_DISABLE;
            break;
    }

    if (mode == GPIOPORT_MODE_OUTPUT)
    {
        (void)gpio_set_level((gpio_num_t)pin, initialHigh ? 1U : 0U);
    }
    if (gpio_config(&cfg) != ESP_OK)
    {
        return false;
    }
    if (mode == GPIOPORT_MODE_OUTPUT)
    {
        (void)gpio_set_drive_capability((gpio_num_t)pin, (gpio_drive_cap_t)GpioPort_LimitDriveStrength(driveStrength));
    }
    return true;
}

bool GpioPort_SetDriveStrength(uint8_t pin, uint8_t driveStrength)
{
    if (!GpioPort_IsValidOutputPin(pin))
    {
        return false;
    }
    return (gpio_set_drive_capability((gpio_num_t)pin, (gpio_drive_cap_t)GpioPort_LimitDriveStrength(driveStrength)) == ESP_OK);
}

bool GpioPort_Write(uint8_t pin, bool high)
{
    if (!GpioPort_IsValidOutputPin(pin))
    {
        return false;
    }
    return (gpio_set_level((gpio_num_t)pin, high ? 1U : 0U) == ESP_OK);
}

bool GpioPort_Read(uint8_t pin, bool *pHigh)
{
    if ((pHigh == NULL) || !GpioPort_IsValidPin(pin))
    {
        return false;
    }
    *pHigh = (gpio_get_level((gpio_num_t)pin) != 0);
    return true;
}

bool GpioPort_EnableInterrupt(uint8_t pin, GpioPort_Edge_t edge)
{
    if (!GpioPort_IsValidPin(pin))
    {
        return false;
    }

    gpio_int_type_t espEdge = GPIO_INTR_ANYEDGE;
    if (edge == GPIOPORT_EDGE_RISING)
    {
        espEdge = GPIO_INTR_POSEDGE;
    }
    else if (edge == GPIOPORT_EDGE_FALLING)
    {
        espEdge = GPIO_INTR_NEGEDGE;
    }

    if ((gpio_set_intr_type((gpio_num_t)pin, espEdge) != ESP_OK) ||
        (gpio_isr_handler_add((gpio_num_t)pin, GpioPort_OnIsr, (void *)(uintptr_t)pin) != ESP_OK))
    {
        return false;
    }
    return (gpio_intr_enable((gpio_num_t)pin) == ESP_OK);
}

void GpioPort_DisableInterrupt(uint8_t pin)
{
    if (!GpioPort_IsValidPin(pin))
    {
        return;
    }
    (void)gpio_intr_disable((gpio_num_t)pin);
    (void)gpio_isr_handler_remove((gpio_num_t)pin);
}

void GpioPort_SetInterruptHandler(GpioPort_InterruptHandler_t handler)
{
    interruptHandler = handler;
}

//============================================================================
// Local Function Implementations
//============================================================================
static void IRAM_ATTR GpioPort_OnIsr(void *pArg)
{
    if (interruptHandler != NULL)
    {
        interruptHandler((uint8_t)(uintptr_t)pArg);
    }
}

static uint8_t GpioPort_LimitDriveStrength(uint8_t driveStrength)
{
    return (driveStrength > BICO_PROTOCOL_BRIDGE_GPIO_MAX_DRIVE_LEVEL) ? (uint8_t)BICO_PROTOCOL_BRIDGE_GPIO_MAX_DRIVE_LEVEL : driveStrength;
}

static bool GpioPort_IsValidPin(uint8_t pin)
{
    return (pin < GPIO_PIN_COUNT) && (((1ULL << pin) & SOC_GPIO_VALID_GPIO_MASK) != 0ULL);
}

static bool GpioPort_IsValidOutputPin(uint8_t pin)
{
    return (pin < GPIO_PIN_COUNT) && (((1ULL << pin) & SOC_GPIO_VALID_OUTPUT_GPIO_MASK) != 0ULL);
}
