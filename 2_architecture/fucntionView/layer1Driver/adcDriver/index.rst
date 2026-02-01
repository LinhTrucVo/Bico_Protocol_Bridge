ADC Driver
###########

Layer 1: Driver Layer

This function provides ADC (Analog-to-Digital Converter) driver interface, 
wrapping vendor HAL for analog signal acquisition.

Description
***********
The ADC Driver manages ADC hardware initialization, configuration, and analog signal conversion. 
It supports multiple channels, various sampling rates, and different resolution modes.

Key responsibilities:
- Initialize and configure ADC hardware
- Configure ADC channels, sampling rates, and resolution
- Trigger single or continuous conversions
- Read converted digital values
- Handle ADC conversion complete callbacks
- Manage DMA transfers for continuous sampling

Static view
***********
..  uml:: staticView.puml

Information flow
****************
..  uml:: informationFlow.puml

Dynamic behaviour
*****************
..  uml:: dynamicBehaviour.puml

Timing behaviour
****************
- Sampling rate: 1 Hz - 10 kHz per channel (configurable)
- Resolution: 8-bit, 10-bit, 12-bit, 16-bit (hardware dependent)
- Conversion time: 1-100 µs per sample (depends on resolution and clock)

Resource consumption
********************
- RAM: ~256 bytes for buffers and control
- ROM: ~1.5 KB for driver code
- CPU: DMA-capable, minimal overhead for continuous mode
