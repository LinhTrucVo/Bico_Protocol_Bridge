SPI Slave Driver
################

Layer 1: Driver Layer

This function provides SPI slave mode driver interface, wrapping vendor HAL for SPI communication as a bus slave.

Description
***********
The SPI Slave Driver manages SPI peripheral in slave mode, responding to master transactions. 
It receives data from the master and transmits data when requested.

Key responsibilities:
- Initialize and configure SPI peripheral in slave mode
- Configure SPI parameters (mode, bit order)
- Receive data from SPI master
- Transmit data to SPI master
- Handle SPI slave events and callbacks

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
- Responds to master clock (configured by master)
- Data ready latency: < 100 µs
- CS assertion to data ready: < 50 µs

Resource consumption
********************
- RAM: ~128 bytes for buffers and control
- ROM: ~1.5 KB for driver code
- CPU: Event-driven, interrupt-based
