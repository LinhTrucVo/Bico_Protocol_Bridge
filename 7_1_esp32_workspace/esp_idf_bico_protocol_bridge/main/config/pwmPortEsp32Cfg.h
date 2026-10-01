// Hardware configuration of the ESP32 PWM port. Defaults follow esp32c3_test/esp32_pwm_test.

#ifndef PWMPORTESP32CFG_H
#define PWMPORTESP32CFG_H

#include "driver/ledc.h"

// GPIO of every PWM channel; the channel index is the position in the list.
#ifndef BICO_PROTOCOL_BRIDGE_PWM_CHANNEL_PINS
#define BICO_PROTOCOL_BRIDGE_PWM_CHANNEL_PINS   { 8 }
#endif

#ifndef BICO_PROTOCOL_BRIDGE_PWM_SPEED_MODE
#define BICO_PROTOCOL_BRIDGE_PWM_SPEED_MODE     LEDC_LOW_SPEED_MODE
#endif

// Duty resolution in bits. The maximum frequency is 80 MHz / 2^bits.
#ifndef BICO_PROTOCOL_BRIDGE_PWM_DUTY_BITS
#define BICO_PROTOCOL_BRIDGE_PWM_DUTY_BITS      8U
#endif

#endif /* PWMPORTESP32CFG_H */
