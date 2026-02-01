SPI Master Driver
#################

Layer 1: Driver Layer

This function provides SPI master mode driver interface, wrapping vendor HAL for SPI communication as a bus master.

Description
***********
The SPI Master Driver manages SPI bus initialization, configuration, and master-mode transactions. 
It controls chip select lines and performs full-duplex data transfers with SPI slave devices.

Key responsibilities:
- Initialize and configure SPI peripheral in master mode
- Configure SPI parameters (clock speed, mode, bit order)
- Perform SPI transmit, receive, and transmit-receive operations
- Manage chip select (CS) lines for multiple slaves
- Handle SPI transfer completion events

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
- SPI clock speed: 100 kHz - 20 MHz (configurable)
- Full-duplex transaction time: depends on data size and clock speed
- CS setup/hold time: configurable

Resource consumption
********************
- RAM: ~128 bytes for control structures
- ROM: ~1.5 KB for driver code
- CPU: Event-driven, DMA-capable
