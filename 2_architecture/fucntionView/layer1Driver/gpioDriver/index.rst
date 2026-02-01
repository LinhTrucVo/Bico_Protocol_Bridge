GPIO Driver
###########

Layer 1: Driver Layer

This function provides GPIO (General Purpose Input/Output) driver interface, wrapping vendor HAL for digital I/O operations.

Description
***********
The GPIO Driver manages GPIO pin initialization, configuration, and digital signal operations. 
It supports input/output modes, pull-up/pull-down resistors, and interrupt-based input detection.

Key responsibilities:
- Initialize and configure GPIO pins
- Set pin modes (input, output)
- Configure pull-up/pull-down resistors
- Read digital input states
- Write digital output states
- Handle GPIO interrupt callbacks

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
- Pin state change latency: < 10 µs
- Interrupt detection: < 5 µs (hardware dependent)
- Debouncing: software configurable

Resource consumption
********************
- RAM: ~64 bytes for control structures
- ROM: ~1 KB for driver code
- CPU: Minimal, event-driven
