I2C Slave Driver
################

Layer 1: Driver Layer

This function provides I2C slave mode driver interface, wrapping vendor HAL for I2C communication as a bus slave.

Description
***********
The I2C Slave Driver manages I2C peripheral in slave mode, responding to master requests. 
It handles address matching, data reception from master, and data transmission to master.

Key responsibilities:
- Initialize and configure I2C peripheral in slave mode
- Set slave address (7-bit or 10-bit)
- Respond to master read requests
- Receive data from master write requests
- Handle I2C slave events and callbacks

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
- Responds to master clock (100 kHz - 1 MHz)
- Address match detection: < 10 µs
- Data response latency: < 100 µs

Resource consumption
********************
- RAM: ~128 bytes for buffers and control
- ROM: ~1.5 KB for driver code
- CPU: Event-driven, interrupt-based
