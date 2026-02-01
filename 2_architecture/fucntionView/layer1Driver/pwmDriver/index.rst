PWM Driver
###########

Layer 1: Driver Layer

This function provides PWM (Pulse Width Modulation) driver interface, wrapping vendor HAL for PWM signal generation.

Description
***********
The PWM Driver manages timer/PWM peripheral initialization, configuration, and PWM signal generation. 
It supports configurable frequency and duty cycle for multiple PWM channels.

Key responsibilities:
- Initialize and configure PWM/timer hardware
- Configure PWM frequency and duty cycle
- Start/stop PWM signal generation
- Update PWM parameters dynamically
- Manage multiple PWM channels independently

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
- PWM frequency range: 1 Hz - 100 kHz (typical)
- Duty cycle resolution: 0-100% (8-16 bit resolution)
- Update rate: Real-time, < 1 ms latency

Resource consumption
********************
- RAM: ~128 bytes for control structures
- ROM: ~1.5 KB for driver code
- CPU: Hardware-based, minimal overhead
