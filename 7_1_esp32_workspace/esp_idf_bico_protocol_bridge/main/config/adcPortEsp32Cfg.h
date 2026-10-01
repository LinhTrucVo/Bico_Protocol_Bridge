// Hardware configuration of the ESP32 ADC port. Defaults follow esp32c3_test/esp32_analog_test.

#ifndef ADCPORTESP32CFG_H
#define ADCPORTESP32CFG_H

#include "esp_adc/adc_oneshot.h"

// ADC1 channels 0..2 are on GPIO0..GPIO2 (ESP32-C3).
#ifndef BICO_PROTOCOL_BRIDGE_ADC_UNIT
#define BICO_PROTOCOL_BRIDGE_ADC_UNIT           ADC_UNIT_1
#endif

#ifndef BICO_PROTOCOL_BRIDGE_ADC_NUM_CHANNELS
#define BICO_PROTOCOL_BRIDGE_ADC_NUM_CHANNELS   3U
#endif

#ifndef BICO_PROTOCOL_BRIDGE_ADC_ATTEN
#define BICO_PROTOCOL_BRIDGE_ADC_ATTEN          ADC_ATTEN_DB_12
#endif

#ifndef BICO_PROTOCOL_BRIDGE_ADC_BITWIDTH
#define BICO_PROTOCOL_BRIDGE_ADC_BITWIDTH       ADC_BITWIDTH_12
#endif

#endif /* ADCPORTESP32CFG_H */
