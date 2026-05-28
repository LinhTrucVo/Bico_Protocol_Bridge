SPI Service
###############

Layer 2: Service Layer

This application implements the Serial to SPI bridge functionality, managing SPI communication in both master and slave modes.

Description
***********
The SPI Service provides complete SPI communication functionality including 
master and slave mode operations, device management, and data transfer. 
It implements the requirements from the SPI feature specification.

Key responsibilities:
- Manage SPI master mode operations (transmit, receive, transceive)
- Manage SPI slave mode operations (respond to master)
- Only 1 mode (master/slave) active at a time
- Handle SPI configuration (clock, mode, bit order)
- Manage chip select (CS) lines for multiple devices
- Implement SPI error handling
- Persist SPI configuration in NVM

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
- Command response: < 10 ms
- SPI transaction: 100 µs - 10 ms (depends on data size and clock)
- CS switching: < 10 µs
- Configuration save: < 100 ms

Resource consumption
********************
- RAM: ~512 bytes for SPI buffers
- ROM: ~3 KB for application code
- NVM: ~256 bytes for configuration
